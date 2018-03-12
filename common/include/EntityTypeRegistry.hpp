#pragma once

#ifndef STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_
#define STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include "EntityType.hpp"

class EntityTypeRegistry
{
public:
	static EntityTypeRegistry* GetInstance();
	static bool DeleteInstance();
	int GetId(const std::string&);
	std::string GetString(int);
	std::shared_ptr<EntityType> GetEntityTypeInstanceById(int);
	std::shared_ptr<EntityType> GetEntityTypeInstanceByKey(const std::string&);
private:
	static EntityTypeRegistry* self;
	static std::unordered_map<std::string, int> string_to_id;
	static std::vector<std::string> id_to_string;
	static std::vector<std::shared_ptr<EntityType>> Registry;
	EntityTypeRegistry();
	~EntityTypeRegistry();
	EntityTypeRegistry(const EntityTypeRegistry&) = delete;
	EntityTypeRegistry & operator=(const EntityTypeRegistry&) = delete;
};

#endif //STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_