#pragma once

#ifndef COMMON_SERIALIZATION_PROTOBUF_ENTITY_TYPE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_PROTOBUF_ENTITY_TYPE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "Serialization/IEntityTypeSerializer.hpp"
#include "EntityType.hpp"
#include "EntityTypeBuilder.hpp"

namespace Common { namespace Serialization
{
	class ProtobufEntityTypeSerializer : public IEntityTypeSerializer
	{
	public:
		virtual std::shared_ptr<EntityType> Deserialize(
			EntityTypeBuilder& builder, std::istream& in) override;
		
		virtual void Serialize(
			std::shared_ptr<EntityType> object, std::ostream& out) override;
	};
} }


#endif // COMMON_SERIALIZATION_PROTOBUF_ENTITY_TYPE_SERIALIZER_HPP_
