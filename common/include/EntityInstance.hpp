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
	EntityInstance();
	~EntityInstance() = default;

private:
	
	std::vector<std::shared_ptr<IComponentInstance>> componentInstances_;
	std::size_t typeId_;
};

#endif // COMMON_ENTITY_INSTANCE_HPP_
