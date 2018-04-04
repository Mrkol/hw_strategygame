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
		EntityInstance::GetComponent(const std::string& id)
	{
		auto iterator = componentInstances_.find(id);
		if (iterator == componentInstances_.end())
			return std::shared_ptr<IComponentInstance>(nullptr);

		return iterator->second;
	}
}
