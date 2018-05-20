#include "Components/team.hpp"

namespace Common { namespace Components
{
	const std::string& TeamComponent::GetId() const
	{
		return TeamComponent::ID;
	}

	/**
	* \brief Synchromize given instance with given
	*/
	void TeamComponent::Synch(
		std::shared_ptr<EntityInstance> to_synch,
		const std::shared_ptr<EntityInstance> other)
	{
		TeamComponent::SetTeamId(to_synch, GetTeamId(other));
	}

	TeamIdType TeamComponent::GetTeamId(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->teamId_;
	}

	void  TeamComponent::SetTeamId(
		std::shared_ptr<EntityInstance> instance, TeamIdType value)
	{
		instance->toSynch = true;
		access_(instance)->teamId_ = value;
	}

	std::shared_ptr<TeamComponentInstance> TeamComponent::access_(
		std::shared_ptr<EntityInstance> instance) const
	{
		return std::static_pointer_cast<TeamComponentInstance>(instance->GetComponent(ID));
	}

	const std::string TeamComponent::ID = "team";

	std::shared_ptr<IComponentInstance> TeamComponent::Instantiate()
	{
		std::shared_ptr<TeamComponentInstance> instance(new TeamComponentInstance);
		return instance;
	}

	std::shared_ptr<TeamComponent> TeamComponent::Access(std::shared_ptr<EntityType> entityType)
	{
		return std::static_pointer_cast<TeamComponent>(entityType->GetComponent(ID));
	}

	const std::string& TeamComponentInstance::GetTypeId() const
	{
		return TeamComponent::ID;
	}

	TeamComponentInstance::TeamComponentInstance()
		: teamId_(0)
	{
	}
} }
