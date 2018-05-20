#pragma once

#ifndef COMMON_GRAPHICS_ENTITY_RENDERER_HPP_
#define COMMON_GRAPHICS_ENTITY_RENDERER_HPP_

#include <memory>
#include "EntityInstance.hpp"
#include "SDL.hpp"
#include "Camera.hpp"


namespace Graphics
{
	class EntityRenderer
	{
	public:
		EntityRenderer();

		void Init(GPU_Target* target, std::shared_ptr<Camera> camera);

		void Render(std::shared_ptr<Common::EntityInstance> instance);

		~EntityRenderer();

	private:
		GPU_Target* target_;
		std::shared_ptr<Camera> camera_;
	};
}

#endif // COMMON_GRAPHICS_ENTITY_RENDERER_HPP_
