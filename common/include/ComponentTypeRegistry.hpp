#pragma once

#ifndef COMMON_COMPONENT_TYPE_REGISTRY_HPP_
#define COMMON_COMPONENT_TYPE_REGISTRY_HPP_

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include "IComponentType.hpp"

class ComponentTypeRegistry
{
public:
	using KeyType = std::size_t;

	ComponentTypeRegistry();
	ComponentTypeRegistry(const ComponentTypeRegistry&) = delete;
	ComponentTypeRegistry& operator=(const ComponentTypeRegistry&) = delete;

	static void Initialize();
	static void Finalize();

	static ComponentTypeRegistry& GetInstance();

	//TODO: implement
	KeyType Register(std::string id, 
		std::shared_ptr<IComponentType> component);

	KeyType GetKey(const std::string& id);
	std::string GetId(KeyType key);
	std::shared_ptr<IComponentType> GetComponentType(KeyType key);
	std::shared_ptr<IComponentType> GetComponentType(const std::string& id);
private:
	static ComponentTypeRegistry* self_;

	KeyType nextKey_;
	std::unordered_map<std::string, KeyType> idToKey_;
	std::vector<std::string> keyToId_;
	std::vector<std::shared_ptr<IComponentType>> registry_;
};

#endif //COMMON_COMPONENT_TYPE_REGISTRY_HPP_
