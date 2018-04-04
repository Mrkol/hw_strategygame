#pragma once

#ifndef COMMON_I_COMPONENT_INSTANCE_HPP_
#define COMMON_I_COMPONENT_INSTANCE_HPP_

#include <string>

namespace Common
{
	//Forward declaration to avoid circular deps.
	class IComponentType;

	//We want to minimalize the memory footprint of this interface
	//therefore minimalizing the vf table (probably)
	class IComponentInstance
	{
	public:
		virtual const std::string& GetTypeId() const = 0;
	};
}

#endif // COMMON_I_COMPONENT_INSTANCE_HPP_
