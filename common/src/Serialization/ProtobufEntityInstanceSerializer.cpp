#include "Serialization/ProtobufEntityInstanceSerializer.hpp"
#include "entity.pb.h"
#include "IComponentType.hpp"
#include "Components/health.hpp"
#include "Components/mana.hpp"
#include "Components/position.hpp"
#include "Components/team.hpp"

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
			healthType->SetRegenDelay(result, instance.health().regen_delay());
			healthType->SetCurrentRegenDelay(result, instance.health().current_regen_delay());
		}

		if (instance.has_mana())
		{
			auto manaType = ManaComponent::Access(type);
			manaType->SetCurrent(result, instance.mana().current());
			manaType->SetMaximum(result, instance.mana().maximum());
			manaType->SetRegenDelay(result, instance.mana().regen_delay());
			manaType->SetCurrentRegenDelay(result, instance.mana().current_regen_delay());
		}

		if (instance.has_team())
		{
			auto teamType = TeamComponent::Access(type);
			teamType->SetTeamId(result, instance.team().team_id());
		}

		return result;
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
			Position pos = positionType->Get(object);
			position->set_x(pos.x);
			position->set_y(pos.y);
		}

		if (auto healthType = HealthComponent::Access(type))
		{
			Entities::Components::HealthComponent* health = instance.mutable_health();
			health->set_maximum(healthType->GetMaximum(object));
			health->set_current(healthType->GetCurrent(object));
			health->set_regen_delay(healthType->GetRegenDelay(object));
			health->set_current_regen_delay(healthType->GetCurrentRegenDelay(object));
		}

		if (auto manaType = ManaComponent::Access(type))
		{
			Entities::Components::ManaComponent* mana = instance.mutable_mana();
			mana->set_maximum(manaType->GetMaximum(object));
			mana->set_current(manaType->GetCurrent(object));
			mana->set_regen_delay(manaType->GetRegenDelay(object));
			mana->set_current_regen_delay(manaType->GetCurrentRegenDelay(object));
		}

		if (auto teamType = TeamComponent::Access(type))
		{
			Entities::Components::TeamComponent* team = instance.mutable_team();
			team->set_team_id(teamType->GetTeamId(object));
		}

		instance.SerializeToOstream(&out);
	}
} }
