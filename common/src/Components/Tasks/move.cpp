#include "Components/Tasks/move.hpp"

Common::Components::Tasks::move::move(
	std::weak_ptr<PositionComponentInstance> positionInstance_,
	std::weak_ptr<MovementComponentInstance> movementInstance_)
{
	selfPosition_ = positionInstance_;
	selfMovement_ = movementInstance_;
}

void Common::Components::Tasks::move::SetDestination(Position place)
{
	destination_ = place;
}

bool Common::Components::Tasks::move::Attempt()
{
	if (!selfPosition_.expired())
	{
		if (IsClose(selfPosition_.lock()->position_, destination_))
		{
			return true;
		}
		else
		{
			selfPosition_.lock()->position_ = FindWay(
				selfPosition_.lock()->position_, destination_,
				selfMovement_().lock()->current_);
			return false;
		}
	}
	else
	{
		//ALARM, ACHTUNG, etc...
	}
	
}