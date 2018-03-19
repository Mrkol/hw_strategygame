#include "EntityType.hpp"

namespace Common
{
	EntityType::EntityType(std::string id)
		: id_(id)
	{
		
	}

	std::shared_ptr<EntityInstance> EntityType::Instantiate()
	{
		std::shared_ptr<EntityInstance> instance(
			new EntityInstance(shared_from_this()));
		
		for (auto componentType : componentTypes_)
		{
			instance->componentInstances_[componentType.second->GetId()] 
				= componentType.second->Instantiate();
		}

		return instance;
	}

	std::string EntityType::GetId() const
	{
		return id_;
	}

	std::shared_ptr<IComponentType> EntityType::GetComponent(std::string id)
	{
		auto iterator = componentTypes_.find(id);

		if (iterator == componentTypes_.end())
			return std::shared_ptr<IComponentType>(nullptr);

		return iterator->second;
	}
}
