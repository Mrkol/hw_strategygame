#include "EntityTypeBuilder.hpp"
#include "CommonHelper.hpp"

namespace Common
{
	EntityTypeBuilder::EntityTypeBuilder(
		EntityTypeRegistry& entityRegistry)
		: entityTypeRegistry_(entityRegistry)
	{

	}

	void EntityTypeBuilder::StartBuilding(std::string id)
	{
		current_ = std::shared_ptr<EntityType>(new EntityType(id));
	}

	void EntityTypeBuilder::AddComponent(
		std::shared_ptr<IComponentType> component)
	{
		current_->componentTypes_[component->GetId()] = component;
	}

	std::shared_ptr<EntityType> EntityTypeBuilder::FinishBuilding()
	{
		std::shared_ptr<EntityType> tmp = current_;
		entityTypeRegistry_[current_->GetId()] = current_;
		current_.reset();
		return tmp;
	}
}
