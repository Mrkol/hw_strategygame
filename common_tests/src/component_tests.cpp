#include <memory>
#include "gtest/gtest.h"
#include "CommonHelper.hpp"
#include "EntityTypeBuilder.hpp"
#include "Components/health.hpp"
#include "Components/mana.hpp"
#include "Components/position.hpp"
#include "Components/team.hpp"

using namespace Common::Components;

TEST(ComponentTests, HealthTest)
{
	Common::EntityTypeRegistry registry;
	Common::EntityTypeBuilder builder(registry);

	auto health = std::make_shared<HealthComponent>(100, 10);
	ASSERT_EQ(100, health->GetDefaultMaximum());
	ASSERT_EQ(10, health->GetDefaultRegenDelay());

	builder.StartBuilding("test");
	builder.AddComponent(health);
	auto instance = builder.FinishBuilding()->Instantiate();

	ASSERT_TRUE(!!instance->GetComponent("health"));

	ASSERT_EQ(100, health->GetMaximum(instance));
	ASSERT_EQ(10, health->GetRegenDelay(instance));

	health->SetCurrent(instance, 50);
	health->SetCurrentRegenDelay(instance, 5);

	ASSERT_EQ(50, health->GetCurrent(instance));
	ASSERT_EQ(5, health->GetCurrentRegenDelay(instance));
}

TEST(ComponentTests, ManaTest)
{
	Common::EntityTypeRegistry registry;
	Common::EntityTypeBuilder builder(registry);

	auto mana = std::make_shared<ManaComponent>(100, 10);
	ASSERT_EQ(100, mana->GetDefaultMaximum());
	ASSERT_EQ(10, mana->GetDefaultRegenDelay());

	builder.StartBuilding("test");
	builder.AddComponent(mana);
	auto instance = builder.FinishBuilding()->Instantiate();

	ASSERT_TRUE(!!instance->GetComponent("mana"));

	ASSERT_EQ(100, mana->GetMaximum(instance));
	ASSERT_EQ(10, mana->GetRegenDelay(instance));

	mana->SetCurrent(instance, 50);
	mana->SetCurrentRegenDelay(instance, 5);

	ASSERT_EQ(50, mana->GetCurrent(instance));
	ASSERT_EQ(5, mana->GetCurrentRegenDelay(instance));
}

TEST(ComponentTests, PositionTest)
{
	Common::EntityTypeRegistry registry;
	Common::EntityTypeBuilder builder(registry);

	auto position = std::make_shared<PositionComponent>();

	builder.StartBuilding("test");
	builder.AddComponent(position);
	auto instance = builder.FinishBuilding()->Instantiate();

	ASSERT_TRUE(!!instance->GetComponent("position"));

	ASSERT_EQ(0, position->Get(instance).x);
	ASSERT_EQ(0, position->Get(instance).y);

	position->Set(instance, {5, 10});

	ASSERT_EQ(5, position->Get(instance).x);
	ASSERT_EQ(10, position->Get(instance).y);
}

TEST(ComponentTests, TeamTest)
{
	Common::EntityTypeRegistry registry;
	Common::EntityTypeBuilder builder(registry);

	auto team = std::make_shared<TeamComponent>();

	builder.StartBuilding("test");
	builder.AddComponent(team);
	auto instance = builder.FinishBuilding()->Instantiate();

	ASSERT_TRUE(!!instance->GetComponent("team"));

	ASSERT_EQ(0, team->GetTeamId(instance));

	team->SetTeamId(instance, 12);

	ASSERT_EQ(12, team->GetTeamId(instance));
}
