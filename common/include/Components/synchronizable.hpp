#pragma once

#ifndef COMMON_COMPONENTS_TEAM_HPP_
#define COMMON_COMPONENTS_TEAM_HPP_

#include <memory>
#include <string>
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class SynchronizableComponentInstance;

	class SynchronizableComponent : public IComponentType
	{
		friend class SynchronizableComponentInstance;
	public:

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual const std::string& GetId() const override;

		/**
		* \brief Synchromize given instance with given
		*/
		void Synch(
			std::shared_ptr<EntityInstance> to_synch,
			const std::shared_ptr<EntityInstance> other);

		static std::shared_ptr<SynchronizableComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~SynchronizableComponent() = default;

	private:
		std::shared_ptr<SynchronizableComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		static const std::string ID;
	};

	class SynchronizableComponentInstance : public IComponentInstance
	{
		friend class SynchronizableComponent;
	public:
		virtual const std::string& GetTypeId() const override;

		virtual ~SynchronizableComponentInstance() = default;
		
	private:
		SynchronizableComponentInstance();
	};
} }

#endif // COMMON_COMPONENTS_TEAM_HPP_
