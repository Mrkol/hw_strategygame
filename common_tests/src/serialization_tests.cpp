#include <sstream>
#include <memory>
#include "gtest/gtest.h"
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "Components/health.hpp"
#include "Components/mana.hpp"
#include "Components/position.hpp"
#include "Components/team.hpp"
#include "Serialization/ProtobufEntityInstanceSerializer.hpp"
#include "Serialization/ProtobufEntityTypeSerializer.hpp"

TEST(SerializationTests, WriteReadTest)
{
	Common::EntityTypeRegistry registry;
	Common::EntityTypeBuilder builder(registry);

	builder.StartBuilding("mage");

	using namespace Common::Components;
	using namespace Common::Serialization;

	builder.AddComponent(
		std::make_shared<PositionComponent>());
	builder.AddComponent(
		std::make_shared<HealthComponent>(400, 10));
	builder.AddComponent(
		std::make_shared<ManaComponent>(200, 10));
	builder.AddComponent(
		std::make_shared<TeamComponent>());

	std::shared_ptr<Common::EntityType> mage = builder.FinishBuilding();


	{
		std::stringstream stream;

		std::shared_ptr<IEntityTypeSerializer> serializer
			= std::make_shared<ProtobufEntityTypeSerializer>();

		serializer->Serialize(mage, stream);
		
		stream.seekg(0, std::ios::beg);
		
		std::shared_ptr<Common::EntityType> mage_copy
			= serializer->Deserialize(builder, stream);

		auto health = HealthComponent::Access(mage);
		ASSERT_EQ(health->GetDefaultMaximum(), health->GetDefaultMaximum());
		ASSERT_EQ(health->GetDefaultRegenDelay(), health->GetDefaultRegenDelay());

		auto mana = ManaComponent::Access(mage);
		ASSERT_EQ(mana->GetDefaultMaximum(), mana->GetDefaultMaximum());
		ASSERT_EQ(mana->GetDefaultRegenDelay(), mana->GetDefaultRegenDelay());
	}

	{
		std::shared_ptr<Common::EntityInstance> unit = mage->Instantiate();

		PositionComponent::Access(mage)->Set(unit, {5, 10});
		HealthComponent::Access(mage)->SetMaximum(unit, 322);
		ManaComponent::Access(mage)->SetMaximum(unit, 150);
		TeamComponent::Access(mage)->SetTeamId(unit, 11);

		std::stringstream stream;

		std::shared_ptr<IEntityInstanceSerializer> serializer
			= std::make_shared<ProtobufEntityInstanceSerializer>();

		serializer->Serialize(unit, stream);
		
		stream.seekg(0, std::ios::beg);
		
		std::shared_ptr<Common::EntityInstance> unit_copy
			= serializer->Deserialize(registry, stream);

		auto health = HealthComponent::Access(mage);
		ASSERT_EQ(health->GetMaximum(unit), 
			health->GetMaximum(unit_copy));
		ASSERT_EQ(health->GetCurrent(unit), 
			health->GetCurrent(unit_copy));
		ASSERT_EQ(health->GetRegenDelay(unit), 
			health->GetRegenDelay(unit_copy));
		ASSERT_EQ(health->GetCurrentRegenDelay(unit), 
			health->GetCurrentRegenDelay(unit_copy));

		auto mana = ManaComponent::Access(mage);
		ASSERT_EQ(mana->GetMaximum(unit),
			mana->GetMaximum(unit_copy));
		ASSERT_EQ(mana->GetCurrent(unit),
			mana->GetCurrent(unit_copy));
		ASSERT_EQ(mana->GetRegenDelay(unit),
			mana->GetRegenDelay(unit_copy));
		ASSERT_EQ(mana->GetCurrentRegenDelay(unit),
			mana->GetCurrentRegenDelay(unit_copy));

		auto position = PositionComponent::Access(mage);
		ASSERT_EQ(position->Get(unit), position->Get(unit_copy));

		auto team = TeamComponent::Access(mage);
		ASSERT_EQ(team->GetTeamId(unit), team->GetTeamId(unit_copy));
	}

}
