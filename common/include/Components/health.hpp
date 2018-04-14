#pragma once

#ifndef COMMON_COMPONENTS_HEALTH_HPP_
#define COMMON_COMPONENTS_HEALTH_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "EntityType.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class HealthComponentInstance;

	class HealthComponent : public IComponentType
	{
		friend class HealthComponentInstance;
	public:
		//TODO: subscribe to the game tick event to regenerate health
		HealthComponent(HealthType maximum, TimeIntervalType regenDelay);

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		HealthType GetMaximum(
			std::shared_ptr<EntityInstance> instance) const;
		HealthType GetCurrent(
			std::shared_ptr<EntityInstance> instance) const;
		TimeIntervalType GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;
		TimeIntervalType GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetMaximum(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		void  SetCurrent(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		void  SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);
		void  SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);

		HealthType GetDefaultMaximum() const;
		TimeIntervalType GetDefaultRegenDelay() const;

		static std::shared_ptr<HealthComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~HealthComponent() = default;

	private:
		std::shared_ptr<HealthComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		HealthType maximum_;
		HealthType regenDelay_;

		static const std::string ID;
	};

	class HealthComponentInstance : public IComponentInstance
	{
		friend class HealthComponent;
	public:
		virtual std::string GetTypeId() const override;

		virtual ~HealthComponentInstance() = default;

	private:
		HealthComponentInstance(HealthType maximum, TimeIntervalType regenDelay);

		HealthType maximum_;
		HealthType current_;
		TimeIntervalType regenDelay_;
		TimeIntervalType currentRegenDelay_;
	};
} }

#endif // COMMON_COMPONENTS_HEALTH_HPP_
