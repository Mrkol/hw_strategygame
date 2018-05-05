#include "common_tests_main.hpp"
#include <iostream>
#include "gtest/gtest.h"
#include "MatchManager.hpp"

int main(int argc, char* argv[])
{
	Network::test();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
