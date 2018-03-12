#include "ComponentTypeRegistry.hpp"
ComponentTypeRegistry::ComponentTypeRegistry()
{
	self = nullptr;
}

ComponentTypeRegistry::~ComponentTypeRegistry()
{
	DeleteInstance();
}

bool ComponentTypeRegistry::DeleteInstance()
{
	if (self != nullptr)
	{
		delete self;
		self = nullptr;
		return true;
	}
	return false;
}

int ComponentTypeRegistry::GetId(const std::string& key)
{
	return string_to_id[key];
}

std::string ComponentTypeRegistry::GetString(int id)
{
	return id_to_string[id];
}

ComponentTypeRegistry* ComponentTypeRegistry::GetInstance()
{
	if (self == nullptr)
	{
		self = new ComponentTypeRegistry();
	}
	return self;
}

std::shared_ptr<IComponentType> ComponentTypeRegistry::GetComponentTypeInstanceById(int id)
{
	return Registry[id];
}

std::shared_ptr<IComponentType> ComponentTypeRegistry::GetComponentTypeInstanceByKey(const std::string& key)
{
	return Registry[GetId(key)];
}

ComponentTypeRegistry* ComponentTypeRegistry::self;
std::unordered_map<std::string, int> ComponentTypeRegistry::string_to_id;
std::vector<std::string>  ComponentTypeRegistry::id_to_string;
std::vector<std::shared_ptr<IComponentType>>  ComponentTypeRegistry::Registry;