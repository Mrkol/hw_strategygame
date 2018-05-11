#include <sstream>
#include "gtest/gtest.h"
#include "UniversalException.hpp"

using namespace Common;


TEST(UniversalExceptionTests, ConstructionTest)
{
	UniversalException e;
	e << "test_string";
	ASSERT_STREQ(e.what(), "test_string");

	UniversalException copy(e);
	ASSERT_STREQ(e.what(), copy.what());
	ASSERT_STREQ(copy.what(), "test_string");
}

TEST(UniversalExceptionTests, TryCatchTest)
{
	try
	{
		throw UniversalException() << "test_string";
	}
	catch(UniversalException& e)
	{
		ASSERT_STREQ(e.what(), "test_string");
	}
	try
	{
		throw UniversalException() << "line1" << std::endl << "line2";
	}
	catch(UniversalException& e)
	{
		std::stringstream s;
		s << "line1" << std::endl << "line2";
		ASSERT_STREQ(e.what(), s.str().c_str());
	}
}
