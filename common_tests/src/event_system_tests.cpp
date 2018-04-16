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
