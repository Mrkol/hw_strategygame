#pragma once

#ifndef COMMON_ENTITY_TYPE_HPP_
#define COMMON_ENTITY_TYPE_HPP_

#include <vector>
#include <memory>
#include "IComponentType.hpp"
#include "EntityInstance.hpp"

namespace Common
{
	class EntityType
	{
		friend class EntityTypeBuilder;
	public:

		std::shared_ptr<EntityInstance> Instantiate();
		std::string GetId() const;
		std::shared_ptr<IComponentType> GetComponent(std::string id);

	private:
		explicit EntityType(std::string id);

		std::unordered_map<std::string, std::shared_ptr<IComponentType>>
			componentTypes_;

		std::string id_;
	};
}

#endif // COMMON_ENTITY_TYPE_HPP_
