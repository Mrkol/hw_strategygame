#pragma once

#ifndef COMMON_COMPONENTS_HEALTH_HPP_
#define COMMON_COMPONENTS_HEALTH_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class HealthInstance;

	class Health : public IComponentType
	{
		friend class HealthInstance;
	public:
		//TODO: subscribe to the game tick event to regenerate health

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		HealthType GetMaximumHealth(
			std::shared_ptr<EntityInstance> instance) const;
		HealthType GetCurrentHealth(
			std::shared_ptr<EntityInstance> instance) const;
		TimeType GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;
		TimeType GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetMaximumHealth(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		void  SetCurrentHealth(
			std::shared_ptr<EntityInstance> instance, HealthType value);
		void  SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeType value);
		void  SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeType value);

		HealthType GetDefaultMaximumHealth() const;
		HealthType GetDefaultRegenDelay() const;


	private:
		std::shared_ptr<HealthInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		HealthType maximum_;
		HealthType regenDelay_;

		static const std::string ID;
	};

	class HealthInstance : public IComponentInstance
	{
		friend class Health;
	public:
		virtual std::string GetTypeId() const override;


	private:
		HealthInstance();

		HealthType maximum_;
		HealthType current_;
		TimeType regenDelay_;
		TimeType currentRegenDelay_;
	};
} }

#endif // COMMON_COMPONENTS_HEALTH_HPP_
