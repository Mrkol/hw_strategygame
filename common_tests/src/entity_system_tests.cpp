#include <memory>
#include "gtest/gtest.h"
#include "CommonHelper.hpp"
#include "EntityInstance.hpp"
#include "EntityType.hpp"
#include "EntityTypeBuilder.hpp"

using namespace Common;

TEST(EntitySystemTests, TestBuilder)
{
	EntityTypeRegistry registry;
	EntityTypeBuilder builder(registry);

	builder.StartBuilding("test");
	builder.FinishBuilding();

	ASSERT_EQ("test", registry["test"]->GetId());
}

TEST(EntitySystemTests, TestInstance)
{
	EntityTypeRegistry registry;
	EntityTypeBuilder builder(registry);

	builder.StartBuilding("test");
	auto type = builder.FinishBuilding();
	auto instance = type->Instantiate();

	ASSERT_FALSE(instance->IsEmitting());
	ASSERT_EQ(type, instance->GetType());
}
