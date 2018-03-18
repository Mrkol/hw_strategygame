#pragma once

#ifndef COMMON_COMPONENTS_COORDS_HPP_
#define COMMON_COMPONENTS_COORDS_HPP_

#include <memory>
#include <string>
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"

namespace Common {
	namespace Components
	{
		class CoordsInstance;

		class Coords : public IComponentType
		{
			friend class CoordsInstance;
		public:

			virtual std::shared_ptr<IComponentInstance> Instantiate() override;
			virtual std::string GetId() const override;

			float GetX(
				std::shared_ptr<EntityInstance> instance) const;
			float GetY(
				std::shared_ptr<EntityInstance> instance) const;

			void  SetX(
				std::shared_ptr<EntityInstance> instance, float value);
			void  SetY(
				std::shared_ptr<EntityInstance> instance, float value);


		private:
			std::shared_ptr<CoordsInstance> access_(
				std::shared_ptr<EntityInstance> instance) const;

			static const std::string ID;
		};

		class CoordsInstance : public IComponentInstance
		{
			friend class Coords;
		public:
			virtual std::string GetTypeId() const override;


		private:
			CoordsInstance();

			float x_;
			float y_;
		};
	}
}

#endif // COMMON_COMPONENTS_COORDS_HPP_
