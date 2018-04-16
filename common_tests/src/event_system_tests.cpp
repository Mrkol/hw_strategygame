#include "gtest/gtest.h"
#include "Events\CDefaultEvent.hpp"
#include "Events\IEvent.hpp"
#include "MatchManager.hpp"

using namespace Common;

TEST(EventSystemTests, TestManagerInitialize)
{
	Common::MatchManager manager;
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
