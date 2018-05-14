#pragma once

#ifndef COMMON_GRAPHICS_RENDER_HELPER_HPP_
#define COMMON_GRAPHICS_RENDER_HELPER_HPP_
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "GL/glu.h"

namespace Graphics
{
	class RenderHelper
	{
		RenderHelper() = delete;
	public:
		static int CreateAndAttachShader(GLuint programHandle, GLenum type, const char* source);

		static int GetAttribLocation(GLuint programHandle, const char* name);
	};
}

#endif // COMMON_GRAPHICS_RENDER_HELPER_HPP_
