#include "EntityTypeRegistry.hpp"

const EntityTypeRegistry& EntityTypeRegistry::GetInstance()
{
	if (self_ == nullptr)
	{
		self_ = new EntityTypeRegistry();
	}
	return *self_;
}

int EntityTypeRegistry::GetKey(const std::string& id)
{
	return id_to_key_[id];
}

std::string EntityTypeRegistry::GetId(const int key)
{
	return key_to_id_[key];
}

std::shared_ptr<EntityType> EntityTypeRegistry::GetEntityTypeInstanceByKey(int key)
{
	return registry_[key];
}

std::shared_ptr<EntityType> EntityTypeRegistry::GetEntityTypeInstanceById(const std::string& id)
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

EntityTypeRegistry* EntityTypeRegistry::self_;