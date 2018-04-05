#pragma once

#ifndef COMMON_COMPONENTS_TASKS_MOVE_HPP_
#define COMMON_COMPONENTS_TASKS_MOVE_HPP_

#include "MapPosition.hpp"
#include "Components/tasklist.hpp"
#include "Components/position.hpp"
#include "Components/movement.hpp"
#include "Tasks/ITask.hpp"

namespace Common {
	namespace Components
	{
		namespace Tasks {
			class move:public ITask
			{
			public:
				move(std::weak_ptr<EntityInstance>);
				void SetDestination(Position);
				bool Attempt() override;
			private:
				Position destination_;
				std::weak_ptr<EntityInstance> selfEntityInstanse_;
			};
		}
	}
}

#endif //COMMON_COMPONENTS_TASKS_MOVE_HPP_
