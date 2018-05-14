#include "GlobalRenderer.hpp"
#include "UniversalException.hpp"
#include "RenderHelper.hpp"

#include "main_vsh.hpp"
#include "main_fsh.hpp"

namespace Graphics
{
	GlobalRenderer::GlobalRenderer()
		: context_(nullptr), 
		mainShaderProgramHandle_(0),
		vertexPositionLocation_(-1),
		VBOHandle_(0),
		IBOHandle_(0),
		guiRenderer_(nullptr)
	{

	}

	void GlobalRenderer::Init(SDL_Window* window)
	{
		context_ = SDL_GL_CreateContext(window);

		if (context_ == nullptr)
		{
			throw Common::UniversalException()
				<< "Unable to initialize SDL renderer! SDL_Error:" << std::endl
				<< SDL_GetError() << std::endl;
		}
		
		glewExperimental = GL_TRUE; 
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			throw Common::UniversalException()
				<< "Unable to initialize GLEW! GLEW error:" << std::endl
				<< glewGetErrorString(glewError) << std::endl;
		}

		if (SDL_GL_SetSwapInterval( 1 ) < 0)
		{
			throw Common::UniversalException()
				<< "Unable to set VSync! SDL_Error:" << std::endl
				<< SDL_GetError() << std::endl;
		}

		InitializePipeline();
	
		guiRenderer_ = std::make_unique<GuiRenderer>();
		int32_t width = 0;
		int32_t height = 0;
		SDL_GetWindowSize(window, &width, &height);
		guiRenderer_->Init(width, height);
	}

	void GlobalRenderer::InitializePipeline()
	{
   		mainShaderProgramHandle_ = glCreateProgram();

   		if (mainShaderProgramHandle_ == 0)
   		{
			throw Common::UniversalException()
				<< "Unable to create a shader program!" << std::endl;
   		}

		RenderHelper::CreateAndAttachShader(mainShaderProgramHandle_, GL_VERTEX_SHADER, 
			reinterpret_cast<const char*>(main_vsh));
		RenderHelper::CreateAndAttachShader(mainShaderProgramHandle_, GL_FRAGMENT_SHADER, 
			reinterpret_cast<const char*>(main_fsh));

		glLinkProgram(mainShaderProgramHandle_);

		GLint programSuccess = GL_TRUE;
		glGetProgramiv(mainShaderProgramHandle_, GL_LINK_STATUS, &programSuccess);
		if (programSuccess != GL_TRUE)
		{
			throw Common::UniversalException()
				<< "Unable to link shader program " << mainShaderProgramHandle_
				<< "!" << std::endl;
			//get program log here
		}


		vertexPositionLocation_ = RenderHelper::GetAttribLocation(mainShaderProgramHandle_, "position");

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.5f,  0.5f,
			-0.5f,  0.5f
		};

		GLuint indexData[] = { 0, 1, 2, 3 };

		glGenBuffers(1, &VBOHandle_);
		glBindBuffer(GL_ARRAY_BUFFER, VBOHandle_);
		glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &IBOHandle_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOHandle_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
	}

	void GlobalRenderer::Render()
	{
		/*glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glUseProgram(mainShaderProgramHandle_);
        glEnableVertexAttribArray(vertexPositionLocation_);

        //Set vertex data
        glBindBuffer(GL_ARRAY_BUFFER, VBOHandle_);
        glVertexAttribPointer(vertexPositionLocation_, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        //Set index data and render
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOHandle_);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(vertexPositionLocation_);
        glUseProgram(0);*/

		guiRenderer_->PreRender();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(0.0f, 0.0f, 0.25f, 0.0f);
		glClearStencil(0);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		guiRenderer_->Render();
	}

	void GlobalRenderer::OnResized(int32_t width, int32_t height)
	{
		guiRenderer_->OnResized(width, height);
	}

	GlobalRenderer::~GlobalRenderer()
	{
		if (mainShaderProgramHandle_ != 0)
			glDeleteProgram(mainShaderProgramHandle_);
	}
}
