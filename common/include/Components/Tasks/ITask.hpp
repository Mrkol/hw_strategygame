#pragma once

#ifndef COMMON_COMPONENTS_TASKS_TASK_HPP_
#define COMMON_COMPONENTS_TASKS_TASK_HPP_

namespace Common {
	namespace Components
	{
		namespace Tasks {
			class ITask
			{
			public:
				virtual Task() = 0;
				virtual ~Task() = 0;
				virtual bool Attempt() = 0;
			private:

			};
		}
	}
}

#endif //COMMON_COMPONENTS_TASKS_TASK_HPP_
