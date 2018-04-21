#pragma once

#ifndef COMMON_COMPONENTS_TASK_LIST_HPP_
#define COMMON_COMPONENTS_TASK_LIST_HPP_

#include "Tasks/Task.hpp"
#include <queue.h>
#include <memory>

namespace Common {
	namespace Components
	{
		class TaskListComponentInstance;

		class TaskComponent : public IComponentType
		{
			friend class TaskListComponentInstance;
		public:

			virtual std::shared_ptr<IComponentInstance> Instantiate() override;
			virtual std::string GetId() const override;

			TaskList AttemptCurrentTask(
				std::shared_ptr<EntityInstance> instance) const;

			void AddTask(
				std::shared_ptr<EntityInstance> instance, 
				std::shared_ptr<Tasks::ITask> newTask);// ��� �������, ��� ����� ���������

			void RemoveTask(
				std::shared_ptr<EntityInstance> instance); // ����� ������, ������ �� ����������� ������� ������������ ���� ��� ������ �������

			static std::shared_ptr<TaskListComponent> Access(std::shared_ptr<EntityType> entityType);

		private:
			std::shared_ptr<TaskListComponentInstance> access_(
				std::shared_ptr<EntityInstance> instance) const;

			static const std::string ID;
		};

		class TaskListComponentInstance : public IComponentInstance
		{
			friend class TaskListComponent;

		public:
			virtual std::string GetTypeId() const override;
			
		private:
			TaskListComponentInstance();
			std::queue<std::shared_ptr<Tasks::ITask>> tasks_;
		};
	}
}

#endif // COMMON_COMPONENTS_TASK_LIST_HPP_
