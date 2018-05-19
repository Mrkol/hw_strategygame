#include "Components\movement.hpp"

namespace Common { namespace Components
{
	MovementComponent::MovementComponent(MovementType maximum, TimeIntervalType regenDelay)
		: baseMovementSpeed_(), movementType_()
	{

	}

	std::shared_ptr<IComponentInstance> MovementComponent::Instantiate()
	{
		return std::shared_ptr<MovementComponentInstance>(
			new MovementComponentInstance(baseMovementSpeed_, movementType_));
	}

	const std::string& MovementComponent::GetId() const
	{
		return MovementComponent::ID;
	}

	/**
	* \brief Synchromize given instance with given
	*/
	void MovementComponent::Synch(
		std::shared_ptr<EntityInstance> to_synch,
		const std::shared_ptr<EntityInstance> other)
	{
		SetCurrentSpeed(to_synch, MovementComponent::GetCurrentSpeed(other));

		SetMovementType(to_synch, MovementComponent::GetMovementType(other));
	}

	MoveSpeedType MovementComponent::GetCurrentSpeed(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->current_;
	}
	MovementType MovementComponent::GetMovementType(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->moveType_;
	}
		
	void MovementComponent::SetCurrentSpeed(
		std::shared_ptr<EntityInstance> instance, MoveSpeedType value)
	{
		access_(instance)->current_ = value;
	}
	void MovementComponent::SetMovementType(
		std::shared_ptr<EntityInstance> instance, MovementType value)
	{
		access_(instance)->moveType_ = value;
	}

	MoveSpeedType MovementComponent::GetDefaultSpeed() const
	{
		return baseMovementSpeed_;
	}
	MovementType MovementComponent::GetDefaultMovementType() const
	{
		return movementType_;
	}

	void MovementComponent::SetDefaultSpeed(MoveSpeedType value)
	{
		baseMovementSpeed_ = value;
	}

	void MovementComponent::SetDefaultMovementType(MovementType value)
	{
		movementType_ = value;
	}

	std::shared_ptr<MovementComponent> MovementComponent::Access(
		std::shared_ptr<EntityType> entityType)
	{
		return std::static_pointer_cast<MovementComponent>(entityType->GetComponent(ID));
	}

	std::shared_ptr<MovementComponentInstance> MovementComponent::access_(
		std::shared_ptr<Common::EntityInstance> instance) const
	{
		return std::static_pointer_cast<MovementComponentInstance>(instance->GetComponent(ID));
	}

	const std::string MovementComponent::ID = "movement";
	
	const std::string& MovementComponentInstance::GetTypeId() const
	{
		return MovementComponent::ID;
	}
	MovementComponentInstance::MovementComponentInstance(MoveSpeedType current, MovementType type)
		: current_(current), moveType_(type)
	{

	}

}
}
