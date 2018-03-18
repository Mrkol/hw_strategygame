#include "Components/coords.hpp"

namespace Common {
	namespace Components
	{
		std::string Coords::GetId() const
		{
			return Coords::ID;
		}

		CoordsType Coords::GetCoords(
			std::shared_ptr<EntityInstance> instance) const
		{
			return access_(instance)->team_;
		}

		void  Coords::SetX(
			std::shared_ptr<EntityInstance> instance, CoordsType value)
		{
			access_(instance)->x_ = value;
		}
		void  Coords::SetY(
			std::shared_ptr<EntityInstance> instance, CoordsType value)
		{
			access_(instance)->y_ = value;
		}

		std::shared_ptr<CoordsInstance> Coords::access_(
			std::shared_ptr<EntityInstance> instance) const
		{
			return std::static_pointer_cast<CoordsInstance>(instance->GetComponent(ID));
		}

		const std::string Coords::ID = "coordinate";

		std::shared_ptr<IComponentInstance> Coords::Instantiate()
		{
			std::shared_ptr<CoordsInstance> instance(new CoordsInstance);
			return instance;
		}

		std::string CoordsInstance::GetTypeId() const
		{
			return Coords::ID;
		}
	}
}
