#pragma once

#ifndef COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "EntityType.hpp"
#include "EntityTypeBuilder.hpp"

namespace Serialization
{
	class IEntityTypeSerializer
	{
	public:
		//Using references to guarantee no nullptrs
		virtual std::shared_ptr<EntityType> Deserialize(
			EntityTypeBuilder& builder, std::istream& in) = 0;
		virtual void Serialize(
			const EntityType& object, std::ostream& out) = 0;
	};
}


#endif // COMMON_SERIALIZATION_I_ENTITY_TYPE_SERIALIZER_HPP_
