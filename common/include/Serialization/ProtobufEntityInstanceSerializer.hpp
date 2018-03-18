#pragma once

#ifndef COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "Serialization/IEntityInstanceSerializer.hpp"
#include "EntityType.hpp"

namespace Common { namespace Serialization
{
	void InitComponentWith(std::shared_ptr<IComponentType>, Entities::Entity,
		std::shared_ptr<EntityInstance> instance);
	class ProtobufEntityInstanceSerializer : public IEntityInstanceSerializer
	{
	public:
		virtual std::shared_ptr<EntityInstance> Deserialize(
			const EntityTypeRegistry& registry, std::istream& in) override;
		
		virtual void Serialize(
			std::shared_ptr<EntityInstance> object, std::ostream& out) override;
	};
} }

#endif // COMMON_SERIALIZATION_PROTOBUF_ENTITY_INSTANCE_SERIALIZER_HPP_
