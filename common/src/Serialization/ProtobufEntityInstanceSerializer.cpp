#include "Serialization/ProtobufEntityInstanceSerializer.hpp"
#include "entity.pb.h"


namespace Common { namespace Serialization
{
	std::shared_ptr<EntityInstance> 
		ProtobufEntityInstanceSerializer::Deserialize(
			const EntityTypeRegistry& registry, std::istream& in)
	{
		Entities::Entity instance;

		if (!in)
		{
			//TODO: proper error handling
			std::cerr << "Invalid stream." << std::endl;
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		if (!instance.ParseFromIstream(&in))
		{
			std::cerr << "Invalid entity file." << std::endl;
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		auto typeIter = registry.find(instance.type_id());
		if (typeIter == registry.end())
		{
			std::cerr << "Entity type with id \"";
			std::cerr << instance.type_id() << "\" not found.";
			return std::shared_ptr<EntityInstance>(nullptr);
		}

		std::shared_ptr<EntityType> type = typeIter->second;

		std::shared_ptr<EntityInstance> result(type->Instantiate());


		//TODO: implement component reading

		return result;
	}

	void ProtobufEntityInstanceSerializer::Serialize(
		std::shared_ptr<EntityInstance> object, std::ostream& out)
	{
		Entities::Entity instance;
		
	}
} }
