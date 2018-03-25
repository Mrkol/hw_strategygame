#pragma once

#ifndef COMMON_COMPONENTS_TASKS_MOVE_HPP_
#define COMMON_COMPONENTS_TASKS_MOVE_HPP_

#include "MapPosition.hpp"
#include "Components/tasklist.hpp"

namespace Common {
	namespace Components
	{
		namespace Tasks {
			class move:public ITask
			{
			public:
				Task() override;
				~Task() override;
				bool Attempt() override;
			private:
				Position destination_;
				std::shared_ptr<TaskListComponent> selfList_;
			};
		}
	}
}

#endif //COMMON_COMPONENTS_TASKS_MOVE_HPP_