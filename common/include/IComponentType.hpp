#pragma once

#ifndef COMMON_COMPONENT_TYPE_HPP_
#define COMMON_COMPONENT_TYPE_HPP_

#include <memory>
#include <string>
#include "IComponentInstance.hpp"


namespace Common
{
	class IComponentType
	{
	public:
		virtual std::shared_ptr<IComponentInstance> Instantiate() const = 0;
		virtual std::string GetId() const = 0;
	};
}

#endif // COMMON_COMPONENTTYPE_HPP_
