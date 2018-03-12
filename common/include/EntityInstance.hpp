#pragma once

#ifndef STRATEGY_GAME_ENTITY_INSTANCE_HPP_
#define STRATEGY_GAME_ENTITY_INSTANCE_HPP_

#include <vector>
#include <memory>
#include "ComponentInstance.hpp"

class EntityInstance
{
	friend class EntityType;
public:
	~EntityInstance() = default;
private:
	EntityInstance();
	std::vector<std::shared_ptr<IComponentInstance>> component_instances;
	int type_id;
};

#endif // STRATEGYGAME_ENTITY_INSTANCE_HPP_
