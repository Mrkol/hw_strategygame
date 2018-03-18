#pragma once

#ifndef COMMON_COMPONENTS_POSITION_HPP_
#define COMMON_COMPONENTS_POSITION_HPP_

#include <memory>
#include <string>
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class PositionComponentInstance;

	class PositionComponent : public IComponentType
	{
		friend class PositionComponentInstance;
	public:

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		Position Get(
			std::shared_ptr<EntityInstance> instance) const;
		
		void Set(
			std::shared_ptr<EntityInstance> instance, Position position);

		static std::shared_ptr<PositionComponent> Access(std::shared_ptr<EntityType> entityType);

	private:
		std::shared_ptr<PositionComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		static const std::string ID;
	};

	class PositionComponentInstance : public IComponentInstance
	{
		friend class PositionComponent;
	public:
		virtual std::string GetTypeId() const override;


	private:
		PositionComponentInstance();

		Position position_;
	};
} }

#endif // COMMON_COMPONENTS_POSITION_HPP_
