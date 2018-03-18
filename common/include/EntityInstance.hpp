#pragma once

#ifndef COMMON_ENTITY_INSTANCE_HPP_
#define COMMON_ENTITY_INSTANCE_HPP_

#include <memory>
#include <unordered_map>
#include "IComponentInstance.hpp"

namespace Common
{
	//Forward declaration to avoid circular dependencies.
	class EntityType;

	class EntityInstance
	{
		friend class EntityType;
	public:
		std::shared_ptr<EntityType> GetType() const;
		bool IsEmitting();
		std::shared_ptr<IComponentInstance> GetComponent(std::string);
	private:
		EntityInstance(std::shared_ptr<EntityType> type);

		std::unordered_map<std::string, std::shared_ptr<IComponentInstance>> 
			componentInstances_;
		std::shared_ptr<EntityType> type_;

		bool emitEvents_; 
	};
}

#endif // COMMON_ENTITY_INSTANCE_HPP_
