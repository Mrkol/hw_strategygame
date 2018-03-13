#include "EntityTypeRegistry.hpp"

EntityTypeRegistry& EntityTypeRegistry::GetInstance()
{
	return *self_;
}

EntityTypeRegistry::KeyType EntityTypeRegistry::GetKey(const std::string& id)
{
	return idToKey_[id];
}

std::string EntityTypeRegistry::GetId(KeyType key)
{
	return keyToId_[key];
}

std::shared_ptr<EntityType> 
	EntityTypeRegistry::GetEntityType(KeyType key)
{
	return registry_[key];
}

std::shared_ptr<EntityType> 
	EntityTypeRegistry::GetEntityType(const std::string& id)
{
	return registry_[GetKey(id)];
}

void EntityTypeRegistry::Initialize()
{
	if (self_ == nullptr)
	{
		self_ = new EntityTypeRegistry();
	}
}

void EntityTypeRegistry::Finalize()
{
	if (self_ != nullptr)
	{
		delete self_;
		self_ = nullptr;
	}
}

EntityTypeRegistry* EntityTypeRegistry::self_(nullptr);
