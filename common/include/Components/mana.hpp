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

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		ManaType GetMaximum(
			std::shared_ptr<EntityInstance> instance) const;
		ManaType GetCurrent(
			std::shared_ptr<EntityInstance> instance) const;
		TimeIntervalType GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;
		TimeIntervalType GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetMaximum(
			std::shared_ptr<EntityInstance> instance, ManaType value);
		void  SetCurrent(
			std::shared_ptr<EntityInstance> instance, ManaType value);
		void  SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);
		void  SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeIntervalType value);

		ManaType GetDefaultMaximum() const;
		ManaType GetDefaultRegenDelay() const;

		static std::shared_ptr<ManaComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~ManaComponent() = default;

	private:
		std::shared_ptr<ManaComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		ManaType maximum_;
		ManaType regenDelay_;

		static const std::string ID;
	};

	class ManaComponentInstance : public IComponentInstance
	{
		friend class ManaComponent;
	public:
		virtual std::string GetTypeId() const override;

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
