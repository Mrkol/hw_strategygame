#include "Components/Position.hpp"

namespace Common { namespace Components
{
	std::string PositionComponent::GetId() const
	{
		return PositionComponent::ID;
	}

	Position PositionComponent::Get(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->position_;
	}

	void PositionComponent::Set(
		std::shared_ptr<EntityInstance> instance, Position position)
	{
		access_(instance)->position_ = position;
	}

	std::shared_ptr<PositionComponentInstance> PositionComponent::access_(
		std::shared_ptr<EntityInstance> instance) const
	{
		return std::static_pointer_cast<PositionComponentInstance>(instance->GetComponent(ID));
	}

	const std::string PositionComponent::ID = "coordinate";

	std::shared_ptr<IComponentInstance> PositionComponent::Instantiate()
	{
		std::shared_ptr<PositionComponentInstance> instance(new PositionComponentInstance);
		return instance;
	}

	std::shared_ptr<PositionComponent> PositionComponent::Access(std::shared_ptr<EntityType> entityType)
	{
		return std::static_pointer_cast<PositionComponent>(entityType->GetComponent(ID));
	}

	std::string PositionComponentInstance::GetTypeId() const
	{
		return PositionComponent::ID;
	}

	PositionComponentInstance::PositionComponentInstance()
		: position_({0, 0})
	{
	}
} }
