#pragma once

#ifndef COMMON_COMPONENTS_MANA_HPP_
#define COMMON_COMPONENTS_MANA_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common {
	namespace Components
	{
		class ManaInstance;

		class Mana : public IComponentType
		{
			friend class ManaInstance;
		public:
			//TODO: subscribe to the game tick event to regenerate mana

			virtual std::shared_ptr<IComponentInstance> Instantiate() override;
			virtual std::string GetId() const override;

			ManaType GetMaximumMana(
				std::shared_ptr<EntityInstance> instance) const;
			ManaType GetCurrentMana(
				std::shared_ptr<EntityInstance> instance) const;
			TimeType GetRegenDelay(
				std::shared_ptr<EntityInstance> instance) const;
			TimeType GetCurrentRegenDelay(
				std::shared_ptr<EntityInstance> instance) const;

			void  SetMaximumMana(
				std::shared_ptr<EntityInstance> instance, ManaType value);
			void  SetCurrentMana(
				std::shared_ptr<EntityInstance> instance, ManaType value);
			void  SetRegenDelay(
				std::shared_ptr<EntityInstance> instance, TimeType value);
			void  SetCurrentRegenDelay(
				std::shared_ptr<EntityInstance> instance, TimeType value);

			ManaType GetDefaultMaximumMana() const;
			ManaType GetDefaultRegenDelay() const;


		private:
			std::shared_ptr<ManaInstance> access_(
				std::shared_ptr<EntityInstance> instance) const;

			ManaType maximum_;
			ManaType regenDelay_;

			static const std::string ID;
		};

		class ManaInstance : public IComponentInstance
		{
			friend class Mana;
		public:
			virtual std::string GetTypeId() const override;


		private:
			ManaInstance();

			ManaType maximum_;
			ManaType current_;
			TimeType regenDelay_;
			TimeType currentRegenDelay_;
		};
	}
}

#endif // COMMON_COMPONENTS_MANA_HPP_
