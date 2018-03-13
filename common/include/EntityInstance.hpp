#pragma once

#ifndef COMMON_ENTITY_INSTANCE_HPP_
#define COMMON_ENTITY_INSTANCE_HPP_

#include <vector>
#include <memory>
#include "IComponentInstance.hpp"

class EntityInstance
{
	friend class EntityType;
public:
	~EntityInstance() = default;
private:
	EntityInstance();
	std::vector<std::shared_ptr<IComponentInstance>> componentInstances_;
	int typeId_;
};

#endif // COMMON_ENTITY_INSTANCE_HPP_
