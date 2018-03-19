#pragma once

#ifndef COMMON_ENTITY_TYPE_BUILDER_HPP_
#define COMMON_ENTITY_TYPE_BUILDER_HPP_

#include <string>
#include <memory>
#include "EntityType.hpp"
#include "IComponentType.hpp"
#include "CommonHelper.hpp"

namespace Common
{
	class EntityTypeBuilder
	{
	public:
		EntityTypeBuilder(
			EntityTypeRegistry& entityRegistry);

		void StartBuilding(std::string id);

		void AddComponent(std::shared_ptr<IComponentType> component);

		std::shared_ptr<EntityType> FinishBuilding();

	private:
		EntityTypeRegistry& entityTypeRegistry_;
		std::shared_ptr<EntityType> current_;
	};
}

#endif // COMMON_ENTITY_TYPE_BUILDER_HPP_
