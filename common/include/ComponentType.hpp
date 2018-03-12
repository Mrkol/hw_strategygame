#pragma once

#ifndef COMMON_COMPONENT_TYPE_HPP_
#define COMMON_COMPONENT_TYPE_HPP_

#include <memory>
#include "ComponentInstance.hpp"

class IComponentType
{
public:
	virtual ~IComponentType() = 0;
	virtual std::shared_ptr<IComponentInstance> CreateInstance() const = 0;
private:
	
};

#endif // COMMON_COMPONENTTYPE_HPP_
