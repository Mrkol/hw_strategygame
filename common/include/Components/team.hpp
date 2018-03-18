#pragma once

#ifndef COMMON_COMPONENTS_TEAM_HPP_
#define COMMON_COMPONENTS_TEAM_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common {
	namespace Components
	{
		class TeamInstance;

		class Team : public IComponentType
		{
			friend class TeamInstance;
		public:

			virtual std::shared_ptr<IComponentInstance> Instantiate() override;
			virtual std::string GetId() const override;

			TeamType GetTeam(
				std::shared_ptr<EntityInstance> instance) const;

			void  SetTeam(
				std::shared_ptr<EntityInstance> instance, TeamType value);


		private:
			std::shared_ptr<TeamInstance> access_(
				std::shared_ptr<EntityInstance> instance) const;

			static const std::string ID;
		};

		class TeamInstance : public IComponentInstance
		{
			friend class Team;
		public:
			virtual std::string GetTypeId() const override;


		private:
			TeamInstance();

			TeamType team_;
		};
	}
}

#endif // COMMON_COMPONENTS_TEAM_HPP_
