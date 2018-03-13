#pragma once

#ifndef COMMON_ENTITY_TYPE_REGISTRY_HPP_
#define COMMON_ENTITY_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include "EntityType.hpp"

class EntityTypeRegistry
{
public:
	using KeyType = std::size_t;

	EntityTypeRegistry();
	EntityTypeRegistry(const EntityTypeRegistry&) = delete;
	EntityTypeRegistry& operator=(const EntityTypeRegistry&) = delete;

	static void Initialize();
	static void Finalize();

	static EntityTypeRegistry& GetInstance();
	
	//TODO: implement
	KeyType Register(std::string id, 
		std::shared_ptr<EntityType> component);

	KeyType GetKey(const std::string& id);
	std::string GetId(KeyType key);
	std::shared_ptr<EntityType> GetEntityType(KeyType key);
	std::shared_ptr<EntityType> GetEntityType(const std::string& id);
private:
	static EntityTypeRegistry* self_;
	
	KeyType nextKey_;
	std::unordered_map<std::string, KeyType> idToKey_;
	std::vector<std::string> keyToId_;
	std::vector<std::shared_ptr<EntityType>> registry_;
};

#endif // COMMON_ENTITY_TYPE_REGISTRY_HPP_
