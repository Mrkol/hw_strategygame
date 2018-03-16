#pragma once

#ifndef COMMON_SERIALIZATION_I_ENTITY_INSTANCE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_I_ENTITY_INSTANCE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "EntityType.hpp"
#include "entity_system_registries.hpp"

namespace Common { namespace Serialization
{
	class IEntityInstanceSerializer
	{
	public:
		virtual std::shared_ptr<EntityInstance> Deserialize(
			const EntityTypeRegistry& registry, std::istream& in) = 0;

		virtual void Serialize(
			std::shared_ptr<EntityInstance> object, std::ostream& out) = 0;
	};
} }

#endif // COMMON_SERIALIZATION_I_ENTITY_INSTANCE_SERIALIZER_HPP_
