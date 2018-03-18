#include "Serialization/ProtobufEntityInstanceSerializer.hpp"
#include "entity.pb.h"
#include "IComponentType.hpp"
#include "Components/AllComponents.hpp"

namespace Common { namespace Serialization
{
	void InitComponentWith(std::shared_ptr<IComponentType> component, 
		const Entities::Entity &entity, std::shared_ptr<EntityInstance> instance)
	{
		std::string componentId = component->GetId();
		if (componentId == "health")
		{
		
			Common::Components::Health* castedComponent = static_cast<Common::Components::Health*>(&(*component));
			castedComponent->SetCurrentHealth(instance, entity.health.amount);
			castedComponent->SetMaximumHealth(instance, entity.health.maxAmount);
			castedComponent->SetRegenDelay(instance, entity.health.regenDelay);
		}
		else if (componentId == "mana")
		{
			Common::Components::Mana* castedComponent = static_cast<Common::Components::Mana*>(&(*component));
			castedComponent->SetCurrentMana(instance, entity.mana.amount);
			castedComponent->SetMaximumMana(instance, entity.mana.maxAmount);
			castedComponent->SetRegenDelay(instance, entity.mana.regenDelay);
		}
		else if (componentId == "team")
		{
			Common::Components::Team* castedComponent = static_cast<Common::Components::Team*>(&(*component));
			castedComponent->SetTeam(instance, entity.teamalignment.team_id);
		}
		else if (componentId == "coordinate")
		{
			Common::Components::Coords* castedComponent = static_cast<Common::Components::Coords*>(&(*component));
			castedComponent->SetX(instance, entity.coordinate.x);
			castedComponent->SetY(instance, entity.coordinate.y);
		}
		else
		{
			std::cerr << "Invalid componentType." << std::endl;
		}
	}
	std::shared_ptr<EntityInstance> 
		ProtobufEntityInstanceSerializer::Deserialize(
			const EntityTypeRegistry& registry, std::istream& in)
	{
		Entities::Entity instance;
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
		std::vector<std::string> componentId = type->GetComponentIdList();
		for (int i = 0; i < componentId.size(); ++i)
		{
			std::shared_ptr<IComponentType> componentType = type->GetComponent(componentId[i]);
		}
		std::shared_ptr<EntityInstance> result(type->Instantiate());
		//TODO: implement component reading

		return result;
	}

	void ProtobufEntityInstanceSerializer::Serialize(
		std::shared_ptr<EntityInstance> object, std::ostream& out)
	{
		Entities::Entity instance;
		
	}
} }
