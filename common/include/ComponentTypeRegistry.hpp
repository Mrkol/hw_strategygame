#pragma once

#ifndef COMMON_COMPONENT_TYPE_REGISTRY_HPP_
#define COMMON_COMPONENT_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <string>
#include "ComponentType.hpp"

class ComponentTypeRegistry
{
public:
	ComponentTypeRegistry() = default;
	~ComponentTypeRegistry() = default;
	static void Initialize();
	static void Finalize();
	static const ComponentTypeRegistry& GetInstance();
	int GetKey(const std::string&);
	std::string GetId(int);
	std::shared_ptr<IComponentType> GetComponentTypeByKey(int);
	std::shared_ptr<IComponentType> GetComponentTypeById(const std::string&);
private:
	static ComponentTypeRegistry* self_;
	std::unordered_map<std::string, int> idToKey_;
	std::vector<std::string> keyToId_;
	std::vector<std::shared_ptr<IComponentType>> registry_;
	ComponentTypeRegistry(const ComponentTypeRegistry&) = delete;
	ComponentTypeRegistry& operator=(const ComponentTypeRegistry&) = delete;
};

#endif //COMMON_COMPONENT_TYPE_REGISTRY_HPP_
