#pragma once

#ifndef COMMON_ENTITY_TYPE_BUILDER_HPP_
#define COMMON_ENTITY_TYPE_BUILDER_HPP_

#include <string>
#include <memory>
#include "EntityType.hpp"
#include "ComponentInstance.hpp"

class EntityTypeBuilder
{
public:
	void StartBuilding(std::string id);

	void AddComponent(std::shared_ptr<IComponentInstance> component);

	std::shared_ptr<EntityType> FinishBuilding();
};

#endif // COMMON_ENTITY_TYPE_BUILDER_HPP_
