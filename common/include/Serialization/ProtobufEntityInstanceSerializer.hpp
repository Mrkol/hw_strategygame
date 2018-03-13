#pragma once

#ifndef COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "IEntityInstanceSerializer.hpp"
#include "EntityType.hpp"

namespace Serialization
{
	class ProtobufEntityInstanceSerializer : IEntityInstanceSerializer
	{
	public:
		virtual std::shared_ptr<EntityInstance> Deserialize(
			EntityType& type, std::istream& in) override;
		virtual void Serialize(
			const EntityInstance& object, std::ostream& out) override;
	};
}

#endif // COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_
