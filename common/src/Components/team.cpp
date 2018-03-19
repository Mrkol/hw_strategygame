#include "Components/team.hpp"

namespace Common { namespace Components
{
	std::string TeamComponent::GetId() const
	{
		return TeamComponent::ID;
	}

	TeamIdType TeamComponent::GetTeamId(
		std::shared_ptr<EntityInstance> instance) const
	{
		return access_(instance)->teamId_;
	}

	void  TeamComponent::SetTeamId(
		std::shared_ptr<EntityInstance> instance, TeamIdType value)
	{
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

	std::string TeamComponentInstance::GetTypeId() const
	{
		return TeamComponent::ID;
	}

	TeamComponentInstance::TeamComponentInstance()
		: teamId_(0)
	{
	}
} }
