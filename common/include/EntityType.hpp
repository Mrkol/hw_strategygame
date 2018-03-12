#pragma once

#ifndef COMMON_ENTITY_TYPE_HPP_
#define COMMON_ENTITY_TYPE_HPP_

#include <vector>
#include <memory>
#include "ComponentType.hpp"
#include "EntityInstance.hpp"

class EntityType
{
public:
	EntityType();
	~EntityType();
	std::shared_ptr<EntityInstance> Create() const;
private:
	std::vector<std::shared_ptr<IComponentType>> componentTypes_;
	EntityType(const EntityType&) = delete;
	EntityType& operator=(const EntityType&) = delete;
};

#endif // STRATEGYGAME_ENTITYTYPE_HPP_
