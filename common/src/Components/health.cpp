#include "Components/health.hpp"

namespace Common { namespace Components 
{
	std::string Health::GetId() const
	{
		return Health::ID;
	}

	HealthType Health::GetMaximumHealth(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->maximum_;
	}

	HealthType Health::GetCurrentHealth(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->current_;
	}

	TimeType Health::GetRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->regenDelay_;
	}

	TimeType Health::GetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->currentRegenDelay_;
	}

	void  Health::SetMaximumHealth(
		std::shared_ptr<EntityInstance> instance, HealthType value)
	{
		access_(instance)->maximum_ = value;
	}

	void  Health::SetCurrentHealth(
		std::shared_ptr<EntityInstance> instance, HealthType value)
	{
		access_(instance)->current_ = value;
	}

	void  Health::SetRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeType value)
	{
		access_(instance)->regenDelay_ = value;
	}

	void  Health::SetCurrentRegenDelay(
		std::shared_ptr<EntityInstance> instance, TimeType value)
	{
		access_(instance)->currentRegenDelay_ = value;
	}

	HealthType Health::GetDefaultMaximumHealth() const
	{
		return maximum_;
	}

	HealthType Health::GetDefaultRegenDelay() const
	{
		return regenDelay_;
	}

	std::shared_ptr<HealthInstance> Health::access_(
		std::shared_ptr<EntityInstance> instance) const
	{
		return std::static_pointer_cast<HealthInstance>(instance->GetComponent(ID));
	}

	const std::string Health::ID = "health";	

	std::shared_ptr<IComponentInstance> Health::Instantiate()
	{
		std::shared_ptr<HealthInstance> instance(new HealthInstance);
	}

	std::string HealthInstance::GetTypeId() const
	{
		return Health::ID;
	}
} }
