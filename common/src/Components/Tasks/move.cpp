#include "Tasks/move.hpp"

Common::Components::Tasks::move::move(
	std::weak_ptr<EntityInstance> selfInstance_)
{
	selfEntityInstanse_ = selfInstance_;
}

void Common::Components::Tasks::move::SetDestination(Position place)
{
	destination_ = place;
}

bool Common::Components::Tasks::move::Attempt()
{
	if (!selfEntityInstanse_.expired())
	{
		auto selfPositionComponent_ = PositionComponent::Access(
			selfEntityInstanse_.lock()->GetType());

		Position selfPosition_ = selfPositionComponent_->Get(
			selfEntityInstanse_.lock());

		if (IsClose(selfPosition_, destination_))
		{
			return true;
		}
		else
		{
			auto selfMovementComponent_ = MovementComponent::Access(
				selfEntityInstanse_.lock()->GetType());

			MovementType selfMovement_ = selfMovementComponent_->GetCurrent(
				selfEntityInstanse_.lock());

			MovementStyleType selfMovementStyle_ = selfMovementComponent_->GetMoveStyle(
				selfEntityInstanse_.lock());

			selfPositionComponent_->Set(
				selfEntityInstanse_.lock(), FindWay(
					selfPosition_, destination_, selfMovement_, selfMovementStyle_));

			return false;
		}
	}
	else
	{
		//ALARM, ACHTUNG, etc...
	}
	
}
