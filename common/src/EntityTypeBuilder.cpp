#include "EntityTypeBuilder.hpp"
#include "ComponentTypeRegistry.hpp"

void EntityTypeBuilder::StartBuilding(std::string id)
{
	current_ = std::make_shared<EntityType>(id);
}

void EntityTypeBuilder::AddComponent(
	std::shared_ptr<IComponentType> component)
{
	//TODO: component dependency graphs (maybe)
	std::size_t compKey = 
		ComponentTypeRegistry::GetInstance().
			GetKey(component->GetId());

	if (current_->componentTypes_.size() <= compKey)
		current_->componentTypes_.resize(compKey + 1);

	current_->componentTypes_[compKey] = component;
}

std::shared_ptr<EntityType> EntityTypeBuilder::FinishBuilding()
{
	std::shared_ptr<EntityType> tmp = current_;
	current_.reset();
	return tmp;
}
