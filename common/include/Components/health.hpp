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
		HealthComponent(HealthType maximum, TimeUnitType regenDelay);

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual const std::string& GetId() const override;

		/**
		* \brief Synchromize given instance with given
		*/
		void Synch(
			std::shared_ptr<EntityInstance> to_synch, 
			const std::shared_ptr<EntityInstance> other);

		/**
		* \brief Get maximum health of health instance of specific Entity instance
		*/
		HealthType GetMaximum(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get current health of health instance of specific Entity instance
		*/
		HealthType GetCurrent(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get basic regen delay of health instance of specific Entity instance
		*/
		TimeIntervalType GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get current regen delay of health instance of specific Entity instance
		*/
		TimeIntervalType GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;

		/**
		* \brief Set maximum health to health instance of specific Entity instance
		*/
		void  SetMaximum(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		/**
		* \brief Set current health to health instance of specific Entity instance
		*/
		void  SetCurrent(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		/**
		* \brief Set regen delay to health instance of specific Entity instance
		*/
		void  SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);
		/**
		* \brief Set current regen delay to health instance of specific Entity instance
		*/
		void  SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);

		/**
		* \brief Get default max hp for this component type
		*/
		HealthType GetDefaultMaximum() const;
		/**
		* \brief Get default regen delay for this component type
		*/
		TimeIntervalType GetDefaultRegenDelay() const;

		/**
		* \brief Get acces to specific component type of specific entity type
		*/
		static std::shared_ptr<HealthComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~HealthComponent() = default;

	private:
		/**
		* \brief Get acces to specific component instance of specific entity instance
		*/
		std::shared_ptr<HealthComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		HealthType maximum_;
		TimeIntervalType regenDelay_;

		static const std::string ID;
	};

	class HealthComponentInstance : public IComponentInstance
	{
		friend class HealthComponent;
	public:
		virtual const std::string& GetTypeId() const override;

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
