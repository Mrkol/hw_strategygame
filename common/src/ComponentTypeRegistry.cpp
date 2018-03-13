#include "ComponentTypeRegistry.hpp"


ComponentTypeRegistry::ComponentTypeRegistry()
	: nextKey_(0)
{

}

ComponentTypeRegistry::KeyType ComponentTypeRegistry::GetKey(const std::string& id)
{
	return idToKey_[id];
}

std::string ComponentTypeRegistry::GetId(KeyType key)
{
	return keyToId_[key];
}

ComponentTypeRegistry& ComponentTypeRegistry::GetInstance()
{
	return *self_;
}

std::shared_ptr<IComponentType> 
	ComponentTypeRegistry::GetComponentType(KeyType key)
{
	return registry_[key];
}

std::shared_ptr<IComponentType> 
	ComponentTypeRegistry::GetComponentType(const std::string& id)
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

ComponentTypeRegistry* ComponentTypeRegistry::self_(nullptr);
