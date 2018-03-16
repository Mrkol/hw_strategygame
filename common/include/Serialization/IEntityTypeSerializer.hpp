#pragma once

#ifndef COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "EntityType.hpp"
#include "EntityTypeBuilder.hpp"
#include "entity_system_registries.hpp"

namespace Common { namespace Serialization
{
	class IEntityTypeSerializer
	{
	public:
		virtual std::shared_ptr<EntityType> Deserialize(
			EntityTypeBuilder& builder, std::istream& in) = 0;
		
		virtual void Serialize(
			std::shared_ptr<EntityType> object, std::ostream& out) = 0;
	};
} }


#endif // COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_
