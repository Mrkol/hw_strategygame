#pragma once

#ifndef COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
#define COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_

#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>

namespace Common
{
	class EntityType;

	using EntityTypeRegistry = 
		std::unordered_map<std::string, std::shared_ptr<EntityType>>;

	using HealthType = unsigned int;
	using ManaType = unsigned int;
	using TimeUnitType = int;
	using TimeIntervalType = std::chrono::milliseconds;
	using TimePointType = std::chrono::system_clock::time_point;
	using MovementType = double;
	enum MovementStyleType
	{
		none = 0, ground, air
	};

	using TeamIdType = unsigned int;
}

#endif // COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
