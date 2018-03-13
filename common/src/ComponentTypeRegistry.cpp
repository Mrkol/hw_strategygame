#include "ComponentTypeRegistry.hpp"

int ComponentTypeRegistry::GetKey(const std::string& id)
{
	return idToKey_[id];
}

std::string ComponentTypeRegistry::GetId(int key)
{
	return keyToId_[key];
}

const ComponentTypeRegistry& ComponentTypeRegistry::GetInstance()
{
	if (self_ == nullptr)
	{
		self_ = new ComponentTypeRegistry();
	}
	return *self_;
}

std::shared_ptr<IComponentType> ComponentTypeRegistry::GetComponentTypeByKey(int key)
{
	return registry_[key];
}

std::shared_ptr<IComponentType> ComponentTypeRegistry::GetComponentTypeById(const std::string& id)
{
	return registry_[GetKey(id)];
}

void ComponentTypeRegistry::Initialize()
{
	if (self_ == nullptr)
	{
		self_ = new ComponentTypeRegistry();
	}
}

void ComponentTypeRegistry::Finalize()
{
	if (self_ != nullptr)
	{
		delete self_;
		self_ = nullptr;
	}
}

ComponentTypeRegistry* ComponentTypeRegistry::self_;
