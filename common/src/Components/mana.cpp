#include "Components/mana.hpp"

namespace Common {
	namespace Components
	{
		std::string Mana::GetId() const
		{
			return Mana::ID;
		}

		ManaType Mana::GetMaximumMana(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->maximum_;
		}

		ManaType Mana::GetCurrentMana(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->current_;
		}

		TimeType Mana::GetRegenDelay(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->regenDelay_;
		}

		TimeType Mana::GetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->currentRegenDelay_;
		}

		void  Mana::SetMaximumMana(
			std::shared_ptr<EntityInstance> instance, ManaType value)
		{
			access_(instance)->maximum_ = value;
		}

		void  Mana::SetCurrentMana(
			std::shared_ptr<EntityInstance> instance, ManaType value)
		{
			access_(instance)->current_ = value;
		}

		void  Mana::SetRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeType value)
		{
			access_(instance)->regenDelay_ = value;
		}

		void  Mana::SetCurrentRegenDelay(
			std::shared_ptr<EntityInstance> instance, TimeType value)
		{
			access_(instance)->currentRegenDelay_ = value;
		}

		ManaType Mana::GetDefaultMaximumMana() const
		{
			return maximum_;
		}

		ManaType Mana::GetDefaultRegenDelay() const
		{
			return regenDelay_;
		}

		std::shared_ptr<ManaInstance> Mana::access_(
			std::shared_ptr<EntityInstance> instance) const
		{
			return std::static_pointer_cast<ManaInstance>(instance->GetComponent(ID));
		}

		const std::string Mana::ID = "mana";

		std::shared_ptr<IComponentInstance> Mana::Instantiate()
		{
			std::shared_ptr<ManaInstance> instance(new ManaInstance);
			return instance;
		}

		std::string ManaInstance::GetTypeId() const
		{
			return Mana::ID;
		}
	}
}
