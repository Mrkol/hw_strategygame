#pragma once

#ifndef COMMON_ENTITY_TYPE_BUILDER_HPP_
#define COMMON_ENTITY_TYPE_BUILDER_HPP_

#include <string>
#include <memory>
#include "EntityType.hpp"
#include "IComponentType.hpp"

class EntityTypeBuilder
{
public:
	EntityTypeBuilder();

	EntityTypeBuilder(const EntityTypeBuilder& other) = delete;

	EntityTypeBuilder& operator=(const EntityTypeBuilder&) = delete;

	void StartBuilding(std::string id);

	void AddComponent(std::shared_ptr<IComponentType> component);

	std::shared_ptr<EntityType> FinishBuilding();

private:
	std::shared_ptr<EntityType> current_;
};

#endif // COMMON_ENTITY_TYPE_BUILDER_HPP_
