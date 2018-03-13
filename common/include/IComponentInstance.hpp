#pragma once

#ifndef COMMON_I_COMPONENT_INSTANCE_HPP_
#define COMMON_I_COMPONENT_INSTANCE_HPP_

class IComponentInstance
{
public:
	virtual ~IComponentInstance() = 0;
	virtual int GetTypeId() = 0;
};

#endif // COMMON_I_COMPONENT_INSTANCE_HPP_
