#pragma once

#ifndef COMMON_COMPONENTS_TASK_LIST_HPP_
#define COMMON_COMPONENTS_TASK_LIST_HPP_

#include "Tasks/ITask.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include <queue>
#include <memory>

namespace Common { namespace Components

{
	class TaskListComponentInstance;

	class TaskListComponent : public IComponentType
	{
		friend class TaskListComponentInstance;
	public:
		std::shared_ptr<IComponentInstance> Instantiate() override;
		const std::string& GetId() const override;

		/**
		* \brief Synchromize given instance with given
		*/
		void Synch(
			std::shared_ptr<EntityInstance> to_synch,
			const std::shared_ptr<EntityInstance> other);

		void AttemptCurrentTask(
			std::shared_ptr<EntityInstance> instance) const;

		void AddTask(
			std::shared_ptr<EntityInstance> instance, 
			std::shared_ptr<Tasks::ITask> newTask);
			// Meditation in progress...

		void RemoveTask(
			std::shared_ptr<EntityInstance> instance); 
			// We have to choose, if we want to remove only top task, or any

		static std::shared_ptr<TaskListComponent> Access(
			std::shared_ptr<EntityType> entityType);
			
		virtual ~TaskListComponent() = default;

	private:
		std::shared_ptr<TaskListComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		static const std::string ID;
	};

	class TaskListComponentInstance : public IComponentInstance
	{
		friend class TaskListComponent;

	public:
		virtual const std::string& GetTypeId() const;

		virtual ~TaskListComponentInstance() = default;
			
	private:
		TaskListComponentInstance();
		std::queue<std::shared_ptr<Tasks::ITask>> tasks_;
	};
}
}

#endif // COMMON_COMPONENTS_TASK_LIST_HPP_
