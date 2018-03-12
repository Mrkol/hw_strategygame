#pragma once

#ifndef STRATEGY_GAME_COMPONENT_TYPE_HPP_
#define STRATEGY_GAME_COMPONENT_TYPE_HPP_

#include <memory>
#include "ComponentInstance.hpp"

class IComponentType
{
public:
	virtual ~IComponentType() = 0;
	virtual std::shared_ptr<IComponentInstance> CreateInstance() const = 0;
private:
	
};

#endif // STRATEGYGAME_COMPONENTTYPE_HPP_
