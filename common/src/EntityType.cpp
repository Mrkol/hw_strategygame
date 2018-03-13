#include "EntityType.hpp"

EntityType::EntityType(std::string id)
	: id_(id)
{
	
}

EntityType::~EntityType()
{

}

std::shared_ptr<EntityInstance> EntityType::Create() const
{
	//TODO: implement this properly
	std::shared_ptr<EntityInstance> instance(new EntityInstance());
	instance->componentInstances_.resize(componentTypes_.size());
	for (unsigned int i = 0; i < componentTypes_.size(); ++i)
	{
		instance->componentInstances_[i] = componentTypes_[i]->Create();
	}
	return instance;
}
