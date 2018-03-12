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
	instance->componentInstances_.resize(componentTypes_.size());
	for (unsigned int i = 0; i < componentTypes_.size(); ++i)
	{
		instance->componentInstances_[i] = componentTypes_[i]->CreateInstance();
	}
	return instance;
}
