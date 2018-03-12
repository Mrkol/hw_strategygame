#include "EntityType.hpp"

EntityType::EntityType()
{

}

EntityType::~EntityType()
{

}

std::shared_ptr<EntityInstance> EntityType::Create() const
{
	std::shared_ptr<EntityInstance> instance(new EntityInstance());
	instance->component_instances_.resize(component_types_.size());
	for (unsigned int i = 0; i < component_types_.size(); ++i)
	{
		instance->component_instances_[i] = component_types_[i]->CreateInstance();
	}
	return instance;
}
