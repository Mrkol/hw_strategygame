#include "Serialization/ProtobufEntityInstanceSerializer.hpp"
#include "entity.pb.h"
#include "IComponentType.hpp"
#include "Components/health.hpp"
#include "Components/mana.hpp"
#include "Components/position.hpp"
#include "Components/team.hpp"
#include "CommonHelper.hpp"
#include <memory>

namespace Common { namespace Serialization
{
	std::shared_ptr<EntityInstance> 
		ProtobufEntityInstanceSerializer::Deserialize(
			const EntityTypeRegistry& registry, std::istream& in)
	{
		Entities::EntityInstance instance;
		if (!in)
		{
			//TODO: proper error handling
			std::cerr << "Invalid stream." << std::endl;
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		if (!instance.ParseFromIstream(&in))
		{
			std::cerr << "Invalid entity file." << std::endl;
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		auto typeIter = registry.find(instance.type_id());
		if (typeIter == registry.end())
		{
			std::cerr << "Entity type with id \"";
			std::cerr << instance.type_id() << "\" not found.";
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		std::shared_ptr<EntityType> type = typeIter->second;

		std::shared_ptr<EntityInstance> result(type->Instantiate());


		using namespace Common::Components;

		if (instance.has_position())
		{
			auto positionType = PositionComponent::Access(type);
			positionType->Set(result, { instance.position().x(), instance.position().y() });
		}

		if (instance.has_health())
		{
			auto healthType = HealthComponent::Access(type);
			healthType->SetCurrent(result, instance.health().current());
			healthType->SetMaximum(result, instance.health().maximum());
			healthType->SetRegenDelay(result, TimeIntervalType(instance.health().regen_delay()));
			healthType->SetCurrentRegenDelay(result, TimeIntervalType(instance.health().current_regen_delay()));
		}

		if (instance.has_mana())
		{
			auto manaType = ManaComponent::Access(type);
			manaType->SetCurrent(result, instance.mana().current());
			manaType->SetMaximum(result, instance.mana().maximum());
			manaType->SetRegenDelay(result, TimeIntervalType(instance.mana().regen_delay()));
			manaType->SetCurrentRegenDelay(result, TimeIntervalType(instance.mana().current_regen_delay()));
		}

		if (instance.has_team())
		{
			auto teamType = TeamComponent::Access(type);
			teamType->SetTeamId(result, instance.team().team_id());
		}

		return result;
	}

	bool ProtobufEntityInstanceSerializer::EmplaceDeserialize(
			const EntityTypeRegistry& registry, std::istream& in,
		std::shared_ptr<Common::EntityInstance> instance)
	{
		Entities::EntityInstance proto_instance;
		if (!in)
		{
			//TODO: proper error handling
			std::cerr << "Invalid stream." << std::endl;
			return false;
		}

		if (!proto_instance.ParseFromIstream(&in))
		{
			std::cerr << "Invalid entity file." << std::endl;
			return false;
		}

		auto typeIter = registry.find(proto_instance.type_id());
		if (typeIter == registry.end())
		{
			std::cerr << "Entity type with id \"";
			std::cerr << proto_instance.type_id() << "\" not found.";
			return false;
		}

		std::shared_ptr<EntityType> type = typeIter->second;

		using namespace Common::Components;

		if (proto_instance.has_position())
		{
			auto positionType = PositionComponent::Access(type);
			auto res = positionType->Instantiate();
			

			positionType->Set(instance, { proto_instance.position().x(), proto_instance.position().y() });
		}

		if (proto_instance.has_health())
		{
			auto healthType = HealthComponent::Access(type);
			healthType->SetCurrent(instance, proto_instance.health().current());
			healthType->SetMaximum(instance, proto_instance.health().maximum());
			healthType->SetRegenDelay(instance, TimeIntervalType(proto_instance.health().regen_delay()));
			healthType->SetCurrentRegenDelay(instance, TimeIntervalType(proto_instance.health().current_regen_delay()));
		}

		if (proto_instance.has_mana())
		{
			auto manaType = ManaComponent::Access(type);
			manaType->SetCurrent(instance, proto_instance.mana().current());
			manaType->SetMaximum(instance, proto_instance.mana().maximum());
			manaType->SetRegenDelay(instance, TimeIntervalType(proto_instance.mana().regen_delay()));
			manaType->SetCurrentRegenDelay(instance, TimeIntervalType(proto_instance.mana().current_regen_delay()));
		}

		if (proto_instance.has_team())
		{
			auto teamType = TeamComponent::Access(type);
			teamType->SetTeamId(instance, proto_instance.team().team_id());
		}

		return true;
	}

	void ProtobufEntityInstanceSerializer::Serialize(
		std::shared_ptr<EntityInstance> object, std::ostream& out)
	{
		if (!out)
		{
			std::cerr << "Invalid stream." << std::endl;
			return;
		}

		Entities::EntityInstance instance;

		auto type = object->GetType();

		instance.set_type_id(type->GetId());
		using namespace Common::Components;

		if (auto positionType = PositionComponent::Access(type))
		{
			Entities::Components::PositionComponent* position = instance.mutable_position();
			MapPosition pos = positionType->Get(object);
			position->set_x(pos.x);
			position->set_y(pos.y);
		}

		if (auto healthType = HealthComponent::Access(type))
		{
			Entities::Components::HealthComponent* health = instance.mutable_health();
			health->set_maximum(healthType->GetMaximum(object));
			health->set_current(healthType->GetCurrent(object));
			health->set_regen_delay(healthType->GetRegenDelay(object).count());
			health->set_current_regen_delay(healthType->GetCurrentRegenDelay(object).count());
		}

		if (auto manaType = ManaComponent::Access(type))
		{
			Entities::Components::ManaComponent* mana = instance.mutable_mana();
			mana->set_maximum(manaType->GetMaximum(object));
			mana->set_current(manaType->GetCurrent(object));
			mana->set_regen_delay(manaType->GetRegenDelay(object).count());
			mana->set_current_regen_delay(manaType->GetCurrentRegenDelay(object).count());
		}

		if (auto teamType = TeamComponent::Access(type))
		{
			Entities::Components::TeamComponent* team = instance.mutable_team();
			team->set_team_id(teamType->GetTeamId(object));
		}

		instance.SerializeToOstream(&out);
	}
} }
