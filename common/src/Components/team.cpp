#include "Components/team.hpp"

namespace Common {
	namespace Components
	{
		std::string Team::GetId() const
		{
			return Team::ID;
		}

		TeamType Team::GetTeam(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->team_;
		}

		void  Team::SetTeam(
			std::shared_ptr<EntityInstance> instance, TeamType value)
		{
			access_(instance)->team_ = value;
		}

		std::shared_ptr<TeamInstance> Team::access_(
			std::shared_ptr<EntityInstance> instance) const
		{
			return std::static_pointer_cast<TeamInstance>(instance->GetComponent(ID));
		}

		const std::string Team::ID = "team";

		std::shared_ptr<IComponentInstance> Team::Instantiate()
		{
			std::shared_ptr<TeamInstance> instance(new TeamInstance);
			return instance;
		}

		std::string TeamInstance::GetTypeId() const
		{
			return Team::ID;
		}
	}
}
