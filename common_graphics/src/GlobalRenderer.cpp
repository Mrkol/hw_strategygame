#include "GlobalRenderer.hpp"
#include "UniversalException.hpp"


#include "CommonHelper.hpp"
#include "MapPosition.hpp"
#include "EntityTypeBuilder.hpp"
#include "Components/position.hpp"
#include "Components/renderer.hpp"

#include "test_png.hpp"

namespace Graphics
{
	GlobalRenderer::GlobalRenderer()
		: target_(nullptr), 
		entityAtlas_(nullptr),
		camera_(nullptr),
		guiRenderer_(nullptr),
		entityRenderer_(nullptr),
		entities_(nullptr)
	{

	}

	void GlobalRenderer::Init(Graphics::UserInputManager& inputManager, 
		std::shared_ptr<Common::EntityInstanceStorageType> entities,
		std::shared_ptr<Graphics::Camera> camera)
	{
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
		target_ = GPU_InitRenderer(GPU_RENDERER_OPENGL_3, 800, 600, 0);

		if (target_ == nullptr)
		{
			throw Common::UniversalException()
				<< "SDL_gpu could not create a target!";
		}


		camera_ = camera;
		entityAtlas_ = GPU_LoadImage_RW(SDL_RWFromConstMem(test_png, test_png_size), true);

		entities_ = entities;
		entityRenderer_ = std::make_unique<EntityRenderer>();
		entityRenderer_->Init(target_, camera);

		guiRenderer_ = std::make_unique<GuiRenderer>();
		guiRenderer_->Init(inputManager, target_->base_w, target_->base_h);
	}

	GPU_Image* GlobalRenderer::GetEntityAtlas()
	{
		return entityAtlas_;
	}

	void GlobalRenderer::Render()
	{
		guiRenderer_->PreRender();
		
		GPU_Clear(target_);
		GPU_ResetRendererState();

		
		//draw stuff here

		for (auto& pair : *entities_)
		{
			entityRenderer_->Render(pair.second);
		}


		GPU_FlushBlitBuffer();

		glPushAttrib(GL_TEXTURE_BIT);
		guiRenderer_->Render();
		glPopAttrib();


		GPU_Flip(target_);
	}

	void GlobalRenderer::OnResized(int32_t width, int32_t height)
	{
		guiRenderer_->OnResized(width, height);
		camera_->SetViewport(width, height);
	}

	GlobalRenderer::~GlobalRenderer()
	{
		GPU_FreeImage(entityAtlas_);
		guiRenderer_.reset();
		entityRenderer_.reset();
		if (target_ != nullptr)
			GPU_FreeTarget(target_);
		GPU_Quit();
	}
}
