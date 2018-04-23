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
		/**
		* \brief Create instance of component
		*/
		virtual std::shared_ptr<IComponentInstance> Instantiate() = 0;
		/**
		* \brief Get component ID
		*/
		virtual const std::string& GetId() const = 0;
		virtual ~IComponentType() = default;
	};
}

#endif // COMMON_COMPONENTTYPE_HPP_
