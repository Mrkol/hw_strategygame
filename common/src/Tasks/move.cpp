#include "Tasks/move.hpp"
#include "Components/position.hpp"
#include "Components/movement.hpp"

namespace Common { namespace Tasks
{
	MoveTask::MoveTask(std::weak_ptr<EntityInstance> entity)
		: entity_(entity)
	{

	}

	void MoveTask::SetDestination(MapPosition place)
	{
		destination_ = place;
	}

	bool MoveTask::Attempt()
	{
		if (entity_.expired())
		{
			throw std::bad_weak_ptr();
		}

		using namespace Common::Components;

		auto positionComponent = PositionComponent::Access(
			entity_.lock()->GetType());

		MapPosition entityPosition = positionComponent->Get(
			entity_.lock());

		if (IsClose(entityPosition, destination_))
		{
			return true;
		}
		else
		{
			auto movementComponent = MovementComponent::Access(
				entity_.lock()->GetType());

			MoveSpeedType speed = movementComponent->GetCurrentSpeed(
				entity_.lock());

			MovementType type = movementComponent->GetMovementType(
				entity_.lock());

			positionComponent->Set(
				entity_.lock(), FindWay(
					entityPosition, destination_, speed, type));

			return false;
		}
	}
} }