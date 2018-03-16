#pragma once

#ifndef COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
#define COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_

#include <memory>
#include <string>
#include "EntityType.hpp"
#include "IComponentType.hpp"

namespace Common
{
	using EntityTypeRegistry = 
		std::unordered_map<std::string, std::shared_ptr<EntityType>>;
}

#endif // COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
