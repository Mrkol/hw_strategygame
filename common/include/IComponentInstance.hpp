#pragma once

#ifndef COMMON_I_COMPONENT_INSTANCE_HPP_
#define COMMON_I_COMPONENT_INSTANCE_HPP_

#include <memory>
#include "IComponentType.hpp"

namespace Common
{
	//We want to minimalize the memory footprint of this interface
	//therefore minimalizing the vf table (probably)
	class IComponentInstance
	{
	public:
		virtual std::shared_ptr<IComponentType> GetType() const = 0;
	};
}

#endif // COMMON_I_COMPONENT_INSTANCE_HPP_
