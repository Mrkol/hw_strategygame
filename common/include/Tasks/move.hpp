#pragma once

#ifndef COMMON_COMPONENTS_TASKS_MOVE_HPP_
#define COMMON_COMPONENTS_TASKS_MOVE_HPP_

#include "MapPosition.hpp"
#include "Components/tasklist.hpp"
#include "Components/position.hpp"
#include "Components/movement.hpp"
#include "Tasks/ITask.hpp"

namespace Common { namespace Tasks 
{
	class MoveTask : public ITask
	{
	public:
		MoveTask(std::weak_ptr<EntityInstance> entity);

		void SetDestination(MapPosition destination);

		bool Attempt() override;
	private:
		MapPosition destination_;
		std::weak_ptr<EntityInstance> entity_;
	};
} }

#endif //COMMON_COMPONENTS_TASKS_MOVE_HPP_
