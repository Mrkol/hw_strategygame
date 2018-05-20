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
		entityRenderer_(nullptr)
	{

	}

	void GlobalRenderer::Init(Graphics::UserInputManager& inputManager)
	{
		GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);
		target_ = GPU_InitRenderer(GPU_RENDERER_OPENGL_3, 800, 600, 0);

		if (target_ == nullptr)
		{
			throw Common::UniversalException()
				<< "SDL_gpu could not create a target!";
		}

		entityAtlas_ = GPU_LoadImage_RW(SDL_RWFromConstMem(test_png, test_png_size), true);

		camera_ = std::make_shared<Camera>(target_->base_w, target_->base_h);

		entityRenderer_ = std::make_unique<EntityRenderer>();
		entityRenderer_->Init(target_, camera_);

		guiRenderer_ = std::make_unique<GuiRenderer>();
		guiRenderer_->Init(inputManager, target_->base_w, target_->base_h);
	}

	void GlobalRenderer::Render()
	{
		guiRenderer_->PreRender();
		
		GPU_Clear(target_);
		GPU_ResetRendererState();

		
		//draw stuff here
		Common::EntityTypeRegistry registry;
		Common::EntityTypeBuilder builder(registry);

		builder.StartBuilding("mage");

		builder.AddComponent(
			std::make_shared<Common::Components::PositionComponent>());
		builder.AddComponent(
			std::make_shared<Graphics::Components::RendererComponent>(
				entityAtlas_, 2, 0));

		std::shared_ptr<Common::EntityType> mage = builder.FinishBuilding();

		std::shared_ptr<Common::EntityInstance> instance = mage->Instantiate();

		Common::Components::PositionComponent::Access(mage)->Set(instance, {0, 200});


		entityRenderer_->Render(instance);


		GPU_FlushBlitBuffer();

		glPushAttrib(GL_TEXTURE_BIT);
		guiRenderer_->Render();
		glPopAttrib();


		GPU_Flip(target_);
	}

	std::shared_ptr<Camera> GlobalRenderer::GetCamera()
	{
		return camera_;
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
