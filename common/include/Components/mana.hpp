#pragma once

#ifndef COMMON_COMPONENTS_MANA_HPP_
#define COMMON_COMPONENTS_MANA_HPP_

#include <memory>
#include <string>
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class ManaComponentInstance;

	class ManaComponent : public IComponentType
	{
		friend class ManaComponentInstance;
	public:
		//TODO: subscribe to the game tick event to regenerate mana
		ManaComponent(HealthType maximum, TimeIntervalType regenDelay);
		ManaComponent(HealthType maximum, TimeUnitType regenDelay);

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual const std::string& GetId() const override;

		/**
		* \brief Get maximum mana of mana instance of specific Entity instance
		*/
		ManaType GetMaximum(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get current mana of mana instance of specific Entity instance
		*/
		ManaType GetCurrent(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get basic regen delay of mana instance of specific Entity instance
		*/
		TimeIntervalType GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;
		/**
		* \brief Get current regen delay of mana instance of specific Entity instance
		*/
		TimeIntervalType GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;

		/**
		* \brief Set maximum mana to mana instance of specific Entity instance
		*/
		void  SetMaximum(
			std::shared_ptr<EntityInstance> instance, ManaType value);
		/**
		* \brief Set current mana to mana instance of specific Entity instance
		*/
		void  SetCurrent(
			std::shared_ptr<EntityInstance> instance, ManaType value);
		/**
		* \brief Set regen delay to mana instance of specific Entity instance
		*/
		void  SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);
		/**
		* \brief Set current regen delay to mana instance of specific Entity instance
		*/
		void  SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);

		/**
		* \brief Get default max mp for this component type
		*/
		ManaType GetDefaultMaximum() const;
		/**
		* \brief Get default regen delay for this component type
		*/
		TimeIntervalType GetDefaultRegenDelay() const;

		/**
		* \brief Get acces to specific component type of specific entity type
		*/
		static std::shared_ptr<ManaComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~ManaComponent() = default;

	private:
		/**
		* \brief Get acces to specific component instance of specific entity instance
		*/
		std::shared_ptr<ManaComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		ManaType maximum_;
		TimeIntervalType regenDelay_;

		static const std::string ID;
	};

	class ManaComponentInstance : public IComponentInstance
	{
		friend class ManaComponent;
	public:
		virtual const std::string& GetTypeId() const override;

		virtual ~ManaComponentInstance() = default;

	private:
		ManaComponentInstance(ManaType maximum, TimeIntervalType regenDelay);

		ManaType maximum_;
		ManaType current_;
		TimeIntervalType regenDelay_;
		TimeIntervalType currentRegenDelay_;
	};
} }

#endif // COMMON_COMPONENTS_MANA_HPP_
