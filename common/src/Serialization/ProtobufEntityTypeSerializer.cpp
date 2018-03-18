#include "Serialization/ProtobufEntityTypeSerializer.hpp"
#include "entity.pb.h"

namespace Common { namespace Serialization
{
	std::shared_ptr<EntityType> ProtobufEntityTypeSerializer::Deserialize(
		EntityTypeBuilder& builder, std::istream& in)
	{
		Entities::EntityType instance;
		
		//TODO: implement
		return std::shared_ptr<EntityType>(nullptr);
	}
	
	void ProtobufEntityTypeSerializer::Serialize(
		std::shared_ptr<EntityType> object, std::ostream& out)
	{
		
	}
} }
