#include "Serialization/ProtobufEntityTypeSerializer.hpp"
#include "entity.pb.h"
#include "Components/health.hpp"
#include "Components/mana.hpp"
#include "Components/position.hpp"
#include "Components/team.hpp"

namespace Common { namespace Serialization
{
	std::shared_ptr<EntityType> ProtobufEntityTypeSerializer::Deserialize(
		EntityTypeBuilder& builder, std::istream& in)
	{
		Entities::EntityType type;
		if (!in)
		{
			//TODO: proper error handling
			std::cerr << "Invalid stream." << std::endl;
			return std::shared_ptr<EntityType>(nullptr);
		}

		if (!type.ParseFromIstream(&in))
		{
			std::cerr << "Invalid entity file." << std::endl;
			return std::shared_ptr<EntityType>(nullptr);
		}

		builder.StartBuilding(type.type_id());

		using namespace Common::Components;

		if (type.has_position())
		{
			std::shared_ptr<PositionComponent> component =
				std::make_shared<PositionComponent>();
			builder.AddComponent(component);
		}

		if (type.has_health())
		{
			std::shared_ptr<HealthComponent> component =
				std::make_shared<HealthComponent>(
					type.health().maximum(), type.health().regen_delay());
			builder.AddComponent(component);
		}

		if (type.has_mana())
		{
			std::shared_ptr<ManaComponent> component =
				std::make_shared<ManaComponent>(
					type.mana().maximum(), type.mana().regen_delay());
			builder.AddComponent(component);
		}

		if (type.has_team())
		{
			std::shared_ptr<TeamComponent> component =
				std::make_shared<TeamComponent>();
			builder.AddComponent(component);
		}

		return builder.FinishBuilding();
	}
	
	void ProtobufEntityTypeSerializer::Serialize(
		std::shared_ptr<EntityType> object, std::ostream& out)
	{
		if (!out)
		{
			std::cerr << "Invalid stream." << std::endl;
			return;
		}

		Entities::EntityType type;

		type.set_type_id(object->GetId());
		using namespace Common::Components;

		if (auto positionType = PositionComponent::Access(object))
		{
			type.mutable_position();
		}

		if (auto healthType = HealthComponent::Access(object))
		{
			Entities::Components::HealthComponentType* health 
				= type.mutable_health();
			health->set_maximum(healthType->GetDefaultMaximum());
			health->set_regen_delay(healthType->GetDefaultRegenDelay());
		}

		if (auto manaType = ManaComponent::Access(object))
		{
			Entities::Components::ManaComponentType* mana 
				= type.mutable_mana();
			mana->set_maximum(manaType->GetDefaultMaximum());
			mana->set_regen_delay(manaType->GetDefaultRegenDelay());
		}

		if (auto teamType = TeamComponent::Access(object))
		{
			type.mutable_team();
		}

		type.SerializeToOstream(&out);
	}
} }
