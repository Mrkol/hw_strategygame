#pragma once

#ifndef COMMON_ENTITY_TYPE_REGISTRY_HPP_
#define COMMON_ENTITY_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include "EntityType.hpp"

class EntityTypeRegistry
{
public:
	EntityTypeRegistry() = default;
	~EntityTypeRegistry() = default;
	static void Initialize();
	static void Finalize();
	static const EntityTypeRegistry& GetInstance();
	int GetKey(const std::string&);
	std::string GetId(int);
	std::shared_ptr<EntityType> GetEntityTypeInstanceByKey(int);
	std::shared_ptr<EntityType> GetEntityTypeInstanceById(const std::string&);
private:
	static EntityTypeRegistry* self_;
	std::unordered_map<std::string, int> idToKey_;
	std::vector<std::string> keyToId_;
	std::vector<std::shared_ptr<EntityType>> registry_;
	EntityTypeRegistry(const EntityTypeRegistry&) = delete;
	EntityTypeRegistry& operator=(const EntityTypeRegistry&) = delete;
};

#endif // COMMON_ENTITY_TYPE_REGISTRY_HPP_
