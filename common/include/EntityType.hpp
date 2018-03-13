#pragma once

#ifndef COMMON_ENTITY_TYPE_HPP_
#define COMMON_ENTITY_TYPE_HPP_

#include <vector>
#include <memory>
#include "IComponentType.hpp"
#include "EntityInstance.hpp"

class EntityType
{
public:
	EntityType(std::string id);
	EntityType(const EntityType&) = delete;
	EntityType& operator=(const EntityType&) = delete;
	~EntityType();

	std::shared_ptr<EntityInstance> Create() const;

private:
	std::vector<std::shared_ptr<IComponentType>> componentTypes_;
	std::string id_;
};

#endif // COMMON_ENTITY_TYPE_HPP_
