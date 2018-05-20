#include "Components/mana.hpp"

namespace Common { namespace Components
{
	void ManaComponent::Synch(
		std::shared_ptr<EntityInstance> to_synch,
		const std::shared_ptr<EntityInstance> other)
	{
		SetMaximum(to_synch, ManaComponent::GetMaximum(other));

		SetCurrent(to_synch, ManaComponent::GetCurrent(other));

		ManaComponent::SetRegenDelay(to_synch, ManaComponent::GetRegenDelay(other));

		ManaComponent::SetCurrentRegenDelay(to_synch,
			ManaComponent::GetCurrentRegenDelay(other));
	}

	ManaComponent::ManaComponent(ManaType maximum, TimeIntervalType regenDelay)
		: maximum_(maximum), regenDelay_(regenDelay)
	{

	}
	ManaComponent::ManaComponent(ManaType maximum, TimeUnitType regenDelay)
		: maximum_(maximum), regenDelay_(regenDelay)
	{

	}

	const std::string& ManaComponent::GetId() const
	{
		return ManaComponent::ID;
	}

	ManaType ManaComponent::GetMaximum(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->maximum_;
	}

	ManaType ManaComponent::GetCurrent(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->current_;
	}

	TimeIntervalType ManaComponent::GetRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->regenDelay_;
	}

	TimeIntervalType ManaComponent::GetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->currentRegenDelay_;
	}

	void  ManaComponent::SetMaximum(
		std::shared_ptr<EntityInstance> instance, ManaType value)
	{
		instance->toSynch = true;
		access_(instance)->maximum_ = value;
	}

	void  ManaComponent::SetCurrent(
		std::shared_ptr<EntityInstance> instance, ManaType value)
	{
		instance->toSynch = true;
		access_(instance)->current_ = value;
	}

	void  ManaComponent::SetRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeIntervalType value)
	{
		instance->toSynch = true;
		access_(instance)->regenDelay_ = value;
	}

	void  ManaComponent::SetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeIntervalType value)
	{
		instance->toSynch = true;
		access_(instance)->currentRegenDelay_ = value;
	}

	ManaType ManaComponent::GetDefaultMaximum() const
	{
		return maximum_;
	}

	TimeIntervalType ManaComponent::GetDefaultRegenDelay() const
	{
		return regenDelay_;
	}

	std::shared_ptr<ManaComponentInstance> ManaComponent::access_(
		std::shared_ptr<EntityInstance> instance) const
	{
		return std::static_pointer_cast<ManaComponentInstance>(instance->GetComponent(ID));
	}

	const std::string ManaComponent::ID = "mana";

	std::shared_ptr<IComponentInstance> ManaComponent::Instantiate()
	{
		std::shared_ptr<ManaComponentInstance> instance(new ManaComponentInstance(maximum_, regenDelay_));
		return instance;
	}

	std::shared_ptr<ManaComponent> ManaComponent::Access(std::shared_ptr<EntityType> entityType)
	{
		return std::static_pointer_cast<ManaComponent>(entityType->GetComponent(ID));
	}

	const std::string& ManaComponentInstance::GetTypeId() const
	{
		return ManaComponent::ID;
	}

	ManaComponentInstance::ManaComponentInstance(ManaType maximum, TimeIntervalType regenDelay)
		: maximum_(maximum), current_(maximum), regenDelay_(regenDelay), currentRegenDelay_(regenDelay)
	{
	}
} }
