#pragma once

#ifndef COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
#define COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_

#include <memory>
#include <unordered_map>
#include <string>

namespace Common
{
	class EntityType;

	using EntityTypeRegistry = 
		std::unordered_map<std::string, std::shared_ptr<EntityType>>;

	using HealthType = unsigned int;
	using ManaType = unsigned int;
	using TeamType = unsigned int;
	using TimeType = unsigned int;
}

#endif // COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
