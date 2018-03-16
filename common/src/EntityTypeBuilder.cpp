#include "EntityTypeBuilder.hpp"
#include "entity_system_registries.hpp"

namespace Common
{
	EntityTypeBuilder::EntityTypeBuilder(
		EntityTypeRegistry& entityRegistry)
		: entityTypeRegistry_(entityRegistry)
	{

	}

	void EntityTypeBuilder::StartBuilding(std::string id)
	{
		current_ = std::make_shared<EntityType>(id);
	}

	void EntityTypeBuilder::AddComponent(
		std::shared_ptr<IComponentType> component)
	{
		current_.componentTypes_.insert(component);
	}

	std::shared_ptr<EntityType> EntityTypeBuilder::FinishBuilding()
	{
		std::shared_ptr<EntityType> tmp = current_;
		entityTypeRegistry_.insert(current_);
		current_.reset();
		return tmp;
	}
}
