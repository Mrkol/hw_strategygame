#include "gtest/gtest.h"
#include "Events/event.hpp"
#include "MatchManager.hpp"
#include "UniversalException.hpp"

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

	std::shared_ptr<IEvent> testEvent(new Event);

	testEvent->Subscribe("sample", sampleHandler);
	testEvent->Trigger(EventArgs());
	EXPECT_TRUE(happened);
	happened = false;

	EXPECT_EQ(testEvent->Unsubscribe("sample"), true);
	EXPECT_EQ(testEvent->Unsubscribe("sample"), false);

	testEvent->Trigger(EventArgs());
	EXPECT_FALSE(happened);
}

TEST(EventSystemTests, EventAccessProxyTrySubscribe_Unsubscribe)
{
	bool happened = false;

	auto sampleHandler =
		[&happened](EventArgs& args)
	{
		happened = true;
	};

	std::shared_ptr<IEvent> testEvent(new Event);
	EventAccessProxy testProxy(*testEvent);
	testProxy.Subscribe("sample", sampleHandler);

	EXPECT_EQ(testProxy.Unsubscribe("sample"), true);
	EXPECT_EQ(testProxy.Unsubscribe("sample"), false);
	bool catched = false;
	try
	{
		testProxy.Trigger(EventArgs());
	}
	catch (const std::exception& exc)
	{
		exc.what();
		catched = true;
	}
	EXPECT_TRUE(catched);
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
	TimePointType finish = std::chrono::system_clock::now() + TimeIntervalType(690);
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

TEST(EventSystemTests, ManagerWithProxy)
{
	TestMatchManager manager;
	manager.Start();
	manager.SetTickRate(TimeIntervalType(100));

	short int happened = 0;
	short int anotherHappened = 0;
	manager.GameTickEvent.Subscribe("sample", [&happened](EventArgs& args)
	{
		++happened;
	});
	manager.GameTickEvent.Subscribe("second_sample", [&anotherHappened](EventArgs& args)
	{
		++anotherHappened;
	});

	TimePointType finish = std::chrono::system_clock::now() + TimeIntervalType(690);
	while (manager.GetCurrentState() != MatchState::Ended)
	{
		if (std::chrono::system_clock::now() > finish)
		{
			manager.Stop();
		}
		manager.GenerateTickTest();
	}
	ASSERT_EQ(manager.GetTickCounter(), 7);
	ASSERT_EQ(manager.GetTickCounter(), happened);
	ASSERT_EQ(happened, anotherHappened);
}
