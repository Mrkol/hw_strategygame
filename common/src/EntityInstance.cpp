#include "EntityInstance.hpp"

namespace Common
{
	EntityInstance::EntityInstance(std::shared_ptr<EntityType> type)
		: type_(type), emitEvents_(false)
	{

	}
	std::shared_ptr<EntityType> EntityInstance::GetType() const
	{
		return type_;
	}

	bool EntityInstance::IsEmitting()
	{
		return emitEvents_;
	}

	std::shared_ptr<IComponentInstance> 
		EntityInstance::GetComponent(std::string id)
	{
		if (!componentInstances_.count(id)) //return null basically
			return std::shared_ptr<IComponentInstance>();

		return componentInstances_[id];
	}
}
