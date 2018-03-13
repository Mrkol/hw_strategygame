#pragma once

#ifndef COMMON_COMPONENT_TYPE_HPP_
#define COMMON_COMPONENT_TYPE_HPP_

#include <memory>
#include "IComponentInstance.hpp"

class IComponentType
{
public:
	virtual ~IComponentType() = 0;
	virtual std::shared_ptr<IComponentInstance> Create() const = 0;
};

#endif // COMMON_COMPONENTTYPE_HPP_
