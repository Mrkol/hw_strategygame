#include "gtest/gtest.h"
#include "Events\CDefaultEvent.hpp"
#include "Events\IEvent.hpp"
#include "MatchManager.hpp"

using namespace Common;

TEST(EventSystemTests, TestManagerInitialize)
{
	MatchManager manager;
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::init);
}

bool SampleFuncFalse(EventArg& args)
{
	return false;
}

bool SampleFuncTrue(EventArg& args)
{
	return true;
}

TEST(EventSystemTests, EventTryHappen)
{
	IEvent* event_ = new CDefaultEvent;
	event_->Subscribe(SampleFuncTrue);
	event_->Subscribe(SampleFuncFalse);
	EXPECT_EQ(event_->TryHappen(EventArg()), false);
	delete event_;

	event_ = new CDefaultEvent;
	event_->Subscribe(SampleFuncTrue);
	event_->Subscribe(SampleFuncTrue);
	EXPECT_EQ(event_->TryHappen(EventArg()), true);
	delete event_;
}

TEST(EventSystemTests, EventTrySubscribe_Unsubscribe)
{
	IEvent* event_ = new CDefaultEvent;
	event_->Subscribe(SampleFuncTrue);
	event_->Subscribe(SampleFuncFalse);
	EXPECT_EQ(event_->TryHappen(EventArg()), false);

	EXPECT_EQ(event_->Unsubscribe(SampleFuncFalse), true);
	
	EXPECT_EQ(event_->TryHappen(EventArg()), true);

	event_->Subscribe(SampleFuncFalse);
	event_->Subscribe(SampleFuncFalse);
	EXPECT_EQ(event_->Unsubscribe(SampleFuncFalse), true);

	EXPECT_EQ(event_->TryHappen(EventArg()), false);
	EXPECT_EQ(event_->Unsubscribe(SampleFuncFalse), true);
	EXPECT_EQ(event_->Unsubscribe(SampleFuncFalse), false);

	delete event_;
}

TEST(EventSystemTests, ManagerChangeState)
{
	MatchManager manager;
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::init);
	manager.Start();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::normal);
	manager.Start();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::normal);
	manager.Pause();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::pause);
	manager.Start();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::normal);
	manager.Stop();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::end);
	manager.Start();
	ASSERT_EQ(manager.GetMode(), Common::EMatchMode::end);
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
	while (manager.GetMode() != end)
	{
		if (std::chrono::system_clock::now() > finish)
		{
			manager.Stop();
		}
		manager.GenerateTickTest();
	}
	ASSERT_EQ(manager.GetTickCounter(), 7);
}
