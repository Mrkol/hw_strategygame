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
	std::unordered_map<std::string, int> string_to_id;
	std::vector<std::string> id_to_string;
	std::vector<EntityType> Registry;
	EntityTypeRegistry();
	~EntityTypeRegistry();
	EntityTypeRegistry(const EntityTypeRegistry & object) = delete;
	EntityTypeRegistry & operator=(const EntityTypeRegistry & object) = delete;
};

#endif //STRATEGY_GAME_ENTITY_TYPE_REGISTRY_HPP_