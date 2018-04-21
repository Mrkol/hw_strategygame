#pragma once

#ifndef COMMON_COMPONENTS_TASKS_ITASK_HPP_
#define COMMON_COMPONENTS_TASKS_ITASK_HPP_

namespace Common { namespace Tasks 
{
	class ITask
	{
	public:
		virtual bool Attempt() = 0;

		virtual ~ITask() = default;
	};
} }

#endif //COMMON_COMPONENTS_TASKS_ITASK_HPP_
