#pragma once

#ifndef STRATEGY_GAME_COMPONENT_TYPE_REGISTRY_HPP_
#define STRATEGY_GAME_COMPONENT_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include "ComponentType.hpp"

class ComponentTypeRegistry
{
public:
	static ComponentTypeRegistry* GetInstance();
	static bool DeleteInstance();
	int GetId(const std::string&);
	std::string GetString(int);
	std::shared_ptr<IComponentType> GetComponentTypeInstanceById(int);
	std::shared_ptr<IComponentType> GetComponentTypeInstanceByKey(const std::string&);
private:
	static ComponentTypeRegistry* self;
	static std::unordered_map<std::string, int> string_to_id;
	static std::vector<std::string> id_to_string;
	static std::vector<std::shared_ptr<IComponentType>> Registry;
	ComponentTypeRegistry();
	~ComponentTypeRegistry();
	ComponentTypeRegistry(const ComponentTypeRegistry & object) = delete;
	ComponentTypeRegistry & operator=(const ComponentTypeRegistry & object) = delete;
};

#endif //STRATEGY_GAME_COMPONENT_TYPE_REGISTRY_HPP_