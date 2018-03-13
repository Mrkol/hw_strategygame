#pragma once

#ifndef COMMON_SERIALIZATION_I_COMPONENT_INSTANCE_SERIALIZER_HPP_
#define COMMON_SERIALIZATION_I_COMPONENT_INSTANCE_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include "ComponentInstance.hpp"


namespace Serialization
{
	class IComponentInstanceSerializer
	{
	public:
		virtual std::shared_ptr<IComponentInstance> Deserialize(
			std::istream& in) = 0;
		//Here, the refernce will be used for argument contravariance
		virtual void Serialize(
			const IComponentInstance& object, std::ostream& out) = 0;
	};
}

#endif // COMMON_SERIALIZATION_I_COMPONENT_INSTANCE_SERIALIZER_HPP_
