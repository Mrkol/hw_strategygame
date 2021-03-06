#include "Components/health.hpp"

namespace Common { namespace Components 
{
	HealthComponent::HealthComponent(HealthType maximum, TimeIntervalType regenDelay)
		: maximum_(maximum), regenDelay_(regenDelay)
	{

	}

	std::string HealthComponent::GetId() const
	{
		return HealthComponent::ID;
	}

	HealthType HealthComponent::GetMaximum(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->maximum_;
	}

	HealthType HealthComponent::GetCurrent(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->current_;
	}

	TimeIntervalType HealthComponent::GetRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->regenDelay_;
	}

	TimeIntervalType HealthComponent::GetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->currentRegenDelay_;
	}

	void  HealthComponent::SetMaximum(
		std::shared_ptr<EntityInstance> instance, HealthType value)
	{
		access_(instance)->maximum_ = value;
	}

	void  HealthComponent::SetCurrent(
		std::shared_ptr<EntityInstance> instance, HealthType value)
	{
		access_(instance)->current_ = value;
	}

	void  HealthComponent::SetRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeIntervalType value)
	{
		access_(instance)->regenDelay_ = value;
	}

	void  HealthComponent::SetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeIntervalType value)
	{
		access_(instance)->currentRegenDelay_ = value;
	}

	HealthType HealthComponent::GetDefaultMaximum() const
	{
		return maximum_;
	}

	HealthType HealthComponent::GetDefaultRegenDelay() const
	{
		return regenDelay_;
	}

	std::shared_ptr<HealthComponentInstance> HealthComponent::access_(
		std::shared_ptr<EntityInstance> instance) const
	{
		return std::static_pointer_cast<HealthComponentInstance>(instance->GetComponent(ID));
	}

	const std::string HealthComponent::ID = "health";	

	std::shared_ptr<IComponentInstance> HealthComponent::Instantiate()
	{
		std::shared_ptr<HealthComponentInstance> instance(new HealthComponentInstance(maximum_, regenDelay_));
		return instance;
	}

	std::shared_ptr<HealthComponent> HealthComponent::Access(std::shared_ptr<EntityType> entityType)
	{
		return std::static_pointer_cast<HealthComponent>(entityType->GetComponent(ID));
	}

	std::string HealthComponentInstance::GetTypeId() const
	{
		return HealthComponent::ID;
	}

	HealthComponentInstance::HealthComponentInstance(HealthType maximum, TimeIntervalType regenDelay)
		: maximum_(maximum), current_(maximum), regenDelay_(regenDelay), currentRegenDelay_(regenDelay)
	{
		
	}
} }
