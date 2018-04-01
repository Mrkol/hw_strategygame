#pragma once

#ifndef COMMON_COMPONENTS_TASKS_MOVE_HPP_
#define COMMON_COMPONENTS_TASKS_MOVE_HPP_

#include "MapPosition.hpp"
#include "Components/tasklist.hpp"
#include "Components/posiion.hpp"
#include "Components/movement.hpp"

namespace Common {
	namespace Components
	{
		namespace Tasks {
			class move:public ITask
			{
			public:
				move() = delete override;//maybe just delete this. Or see cpp file
				move(weak_ptr<MovementComponentInstance>, weak_ptr<MovementComponentInstance>);
				~move() = default override;
				void SetDestination(Position);
				bool Attempt() override;
			private:
				Position destination_;
				std::weak_ptr<PositionComponentInstance> selfPosition_;
				std::weak_ptr<MovementComponentInstance> selfMovement_;
				std::shared_ptr<TaskListComponentInstance> selfList_;
			};
		}
	}
}

#endif //COMMON_COMPONENTS_TASKS_MOVE_HPP_
