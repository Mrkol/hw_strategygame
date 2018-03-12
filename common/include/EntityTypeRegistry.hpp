#pragma once

#ifndef STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_
#define STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_

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
	std::unordered_map<std::string, int> id_to_key_;
	std::vector<std::string> key_to_id_;
	std::vector<std::shared_ptr<EntityType>> registry_;
	EntityTypeRegistry(const EntityTypeRegistry&) = delete;
	EntityTypeRegistry& operator=(const EntityTypeRegistry&) = delete;
};

#endif //STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_