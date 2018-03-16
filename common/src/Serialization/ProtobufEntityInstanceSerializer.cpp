#include "ProtobufEntityInstanceSerializer.hpp"
#include "entity.pb.h"


std::shared_ptr<EntityInstance> 
	ProtobufEntityInstanceSerializer::Deserialize(
		std::istream& in) override
{
	Entities::Entity instance;

	if (!in)
	{
		//TODO: proper error handling
		std::cerr << "Invalid stream." << std::endl;
		return nullptr;
	}

	if (!instane.ParseFromIstream(&in))
	{
		std::cerr << "Invalid entity file." << std::endl;
		return nullptr;
	}

	EntityType& type = 
		EntityTypeRegistry::GetInstance().GetEntityType(instance.id);

	std::shared_ptr<EntityInstance> result(type.Create());


	//TODO: implement component reading

	return result;
}

void ProtobufEntityInstanceSerializer::Serialize(
	const EntityInstance& object, std::ostream& out) override
{
	Entities::Entity instance;
	
}
