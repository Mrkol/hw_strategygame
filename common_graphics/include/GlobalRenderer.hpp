#pragma once

#ifndef COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_
#define COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_

#include <memory>
#include "SDL.hpp"
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "GL/glu.h"
#include "GuiRenderer.hpp"
#include "EntityRenderer.hpp"
#include "UserInputManager.hpp"
#include "Camera.hpp"

namespace Graphics
{
	class GlobalRenderer
	{
	public:
		GlobalRenderer();

		void Init(Graphics::UserInputManager& inputManager,
			std::shared_ptr<Common::EntityInstanceStorageType> entities,
			std::shared_ptr<Camera> camera);

		void Render();

		GPU_Image* GetEntityAtlas();

		void OnResized(int32_t width, int32_t height);

		~GlobalRenderer();

	private:
		GPU_Target* target_;
		GPU_Image* entityAtlas_;

		std::shared_ptr<Graphics::Camera> camera_;
		std::unique_ptr<GuiRenderer> guiRenderer_;
		std::unique_ptr<EntityRenderer> entityRenderer_;
		std::shared_ptr<Common::EntityInstanceStorageType> entities_; 
	};
}

#endif // COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_
