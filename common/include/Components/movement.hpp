#pragma once

#ifndef COMMON_COMPONENTS_MOVEMENT_HPP_
#define COMMON_COMPONENTS_MOVEMENT_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "EntityType.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common { namespace Components
{
	class MovementComponentInstance;

	class MovementComponent : public IComponentType
	{
		friend class MovementComponentInstance;
	public:
		MovementComponent(MovementType maximum, TimeIntervalType regenDelay);

		virtual std::shared_ptr<IComponentInstance> Instantiate() override;
		virtual std::string GetId() const override;

		MovementType GetBase(
			std::shared_ptr<EntityInstance> instance) const;
		MovementType GetCurrent(
			std::shared_ptr<EntityInstance> instance) const;
		MovementStyleType GetMoveStyle(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetBase(//have to decide if we ideologically need it
			std::shared_ptr<EntityInstance> instance, MovementType value);
		void  SetCurrent(
			std::shared_ptr<EntityInstance> instance, MovementType value);
		void  SetGetMoveStyle(
			std::shared_ptr<EntityInstance> instance, MovementStyleType value);

		MovementType GetDefaultBase() const;
		MovementStyleType GetDefaultMoveStyle() const;

		static std::shared_ptr<MovementComponent> Access(std::shared_ptr<EntityType> entityType);

	private:
		std::shared_ptr<MovementComponentInstance> access_(
			std::shared_ptr<EntityInstance> instance) const;

		MovementType base_;
		MovementStyleType moveStyle_;

		static const std::string ID;
	};

	class MovementComponentInstance : public IComponentInstance
	{
		friend class MovementComponent;
		friend class move;
	public:
		virtual std::string GetTypeId() const override;


	private:
		MovementComponentInstance(MovementType maximum, TimeIntervalType regenDelay);

		MovementType base_;
		MovementType current_;
		MovementStyleType moveStyle_;
	};
} }

#endif // COMMON_COMPONENTS_MOVEMENT_HPP_
