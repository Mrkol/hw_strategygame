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
		virtual const std::string& GetId() const override;

		/**
		* \brief Synchromize given instance with given
		*/
		void Synch(
			std::shared_ptr<EntityInstance> to_synch,
			const std::shared_ptr<EntityInstance> other);

		MoveSpeedType GetCurrentSpeed(
			std::shared_ptr<EntityInstance> instance) const;
		MovementType GetMovementType(
			std::shared_ptr<EntityInstance> instance) const;

		void  SetCurrentSpeed(
			std::shared_ptr<EntityInstance> instance, MoveSpeedType value);
		void  SetMovementType(
			std::shared_ptr<EntityInstance> instance, MovementType value);

		MoveSpeedType GetDefaultSpeed() const;
		MovementType GetDefaultMovementType() const;
		void SetDefaultSpeed(MoveSpeedType value);
		void SetDefaultMovementType(MovementType value);

		static std::shared_ptr<MovementComponent> Access(std::shared_ptr<EntityType> entityType);

		virtual ~MovementComponent() = default;

	private:
		std::shared_ptr<MovementComponentInstance> access_(
			std::shared_ptr<Common::EntityInstance> instance) const;

		MoveSpeedType baseMovementSpeed_;
		MovementType movementType_;

		static const std::string ID;
	};

	class MovementComponentInstance : public IComponentInstance
	{
		friend class MovementComponent;

	public:
		virtual const std::string& GetTypeId() const override;

		virtual ~MovementComponentInstance() = default;

	private:
		MovementComponentInstance(MoveSpeedType current, MovementType type);

		MoveSpeedType current_;
		MovementType moveType_;
	};
} }

#endif // COMMON_COMPONENTS_MOVEMENT_HPP_
