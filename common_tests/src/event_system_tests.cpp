#include "gtest/gtest.h"
#include "Events/event.hpp"
#include "MatchManager.hpp"

using namespace Common;

TEST(EventSystemTests, TestManagerInitialization)
{
	MatchManager manager;
	ASSERT_EQ(manager.GetCurrentState(), MatchState::Initialization);
	//more tests will be here when more content is done
}

TEST(EventSystemTests, EventTrySubscribe_Unsubscribe)
{
	bool happened = false;

	auto sampleHandler = 
		[&happened](EventArgs& args) 
		{
			happened = true;
		};

	std::shared_ptr<IEvent> event(new Event);

	event->Subscribe("sample", sampleHandler);
	event->Trigger(EventArgs());
	EXPECT_TRUE(happened);
	happened = false;

	EXPECT_EQ(event->Unsubscribe("sample"), true);
	EXPECT_EQ(event->Unsubscribe("sample"), false);

	event->Trigger(EventArgs());
	EXPECT_FALSE(happened);
}

TEST(EventSystemTests, ManagerChangeState)
{
	MatchManager manager;
	ASSERT_EQ(manager.GetCurrentState(), MatchState::Initialization);
	manager.Start();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::InProgress);
	manager.Start();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::InProgress);
	manager.Pause();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::Paused);
	manager.Start();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::InProgress);
	manager.Stop();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::Ended);
	manager.Start();
	ASSERT_EQ(manager.GetCurrentState(), MatchState::Ended);
}

class TestMatchManager : public MatchManager
{
public:
	TestMatchManager()
	{
		tickCounter_ = 0;
	}
	virtual bool GenerateTickTest()
	{
		if (GenerateTick())
		{
			++tickCounter_;
			return true;
		}
		return false;
	}
	long unsigned int GetTickCounter()
	{
		return tickCounter_;
	}
	void SetTickRate(TimeIntervalType dur)
	{
		tickRate_ = dur;
	}
private:
	long unsigned int tickCounter_;
};

TEST(EventSystemTests, EventsAndChrono)
{
	TestMatchManager manager;
	manager.Start();
	manager.SetTickRate(TimeIntervalType(100));
	TimePointType finish = std::chrono::system_clock::now() + TimeIntervalType(720);
	while (manager.GetCurrentState() != MatchState::Ended)
	{
		if (std::chrono::system_clock::now() > finish)
		{
			manager.Stop();
		}
		manager.GenerateTickTest();
	}
	ASSERT_EQ(manager.GetTickCounter(), 7);
}
