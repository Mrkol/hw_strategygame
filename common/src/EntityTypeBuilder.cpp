#include "EntityTypeBuilder.hpp"

void EntityTypeBuilder::StartBuilding(std::string id)
{
	current_ = std::make_shared<EntityType>()
}

void EntityTypeBuilder::AddComponent(
	std::shared_ptr<IComponentType> component)
{

}

std::shared_ptr<EntityType> EntityTypeBuilder::FinishBuilding()
{

}
