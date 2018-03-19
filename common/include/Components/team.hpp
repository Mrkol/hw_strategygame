#pragma once

#ifndef COMMON_COMPONENTS_TEAM_HPP_
#define COMMON_COMPONENTS_TEAM_HPP_

#include <memory>
#include <string>
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class TeamComponentInstance;

	class TeamComponent : public IComponentType
	{
		friend class TeamComponentInstance;
	public:

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		TeamIdType GetTeamId(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetTeamId(
			std::shared_ptr<EntityInstance> instance, TeamIdType value);

		static std::shared_ptr<TeamComponent> Access(std::shared_ptr<EntityType> entityType);

	private:
		std::shared_ptr<TeamComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		static const std::string ID;
	};

	class TeamComponentInstance : public IComponentInstance
	{
		friend class TeamComponent;
	public:
		virtual std::string GetTypeId() const override;


	private:
		TeamComponentInstance();

		TeamIdType teamId_;
	};
} }

#endif // COMMON_COMPONENTS_TEAM_HPP_
