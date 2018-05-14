#include "RenderHelper.hpp"
#include "UniversalException.hpp"

namespace Graphics
{
	int RenderHelper::CreateAndAttachShader(GLuint programHandle, GLenum type, const char* source)
	{
		GLuint shader = glCreateShader(type);
		if (shader == 0)
		{
			throw Common::UniversalException()
				<< "Unable to create a shader!" << std::endl;
		}

		const GLchar* shaderSource[] = { source };

		glShaderSource(shader, 1, shaderSource, nullptr);
		glCompileShader(shader);
		
		GLint success = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE)
		{
			throw Common::UniversalException()
				<< "Unable to compile fragment shader " << shader << "!" << std::endl;
			//get shader log here
		}

		glAttachShader(programHandle, shader);

		return shader;
	}

	int RenderHelper::GetAttribLocation(GLuint programHandle, const char* name)
	{
		GLuint result = glGetAttribLocation(programHandle, name);
		if (result == -1)
		{
			throw Common::UniversalException()
				<< name << " is not a valid attribute!" << std::endl;
		}
		return result;
	}
}
