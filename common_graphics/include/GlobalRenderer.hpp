#pragma once

#ifndef COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_
#define COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_

#include <memory>
#include "SDL.hpp"
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "GL/glu.h"
#include "GuiRenderer.hpp"

namespace Graphics
{
	class GlobalRenderer
	{
	public:
		GlobalRenderer();

		void Init(SDL_Window* window);

		void InitializePipeline();

		void Render();

		void OnResized(int32_t width, int32_t height);

		~GlobalRenderer();

	private:
		SDL_GLContext context_;

		GLuint mainShaderProgramHandle_;
		GLint vertexPositionLocation_;
		GLuint VBOHandle_;
		GLuint IBOHandle_;

		std::unique_ptr<GuiRenderer> guiRenderer_;
	};
}

#endif // COMMON_GRAPHICS_GLOBAL_RENDERER_HPP_
