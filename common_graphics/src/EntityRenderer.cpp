#include "EntityRenderer.hpp"
#include "Components/position.hpp"
#include "Components/renderer.hpp"

namespace Graphics
{
	EntityRenderer::EntityRenderer()
		: target_(nullptr), camera_(nullptr)
	{

	}

	void EntityRenderer::Init(GPU_Target* target, std::shared_ptr<Camera> camera)
	{
		target_ = target;
		camera_ = camera;
	}

	void EntityRenderer::Render(std::shared_ptr<Common::EntityInstance> instance)
	{
		using namespace Common::Components;
		using namespace Graphics::Components;

		auto posComp = PositionComponent::Access(instance->GetType());
		auto position = posComp->Get(instance);

		auto rendComp = RendererComponent::Access(instance->GetType());
		
		std::size_t strideW = rendComp->GetAtlas()->w / rendComp->GetAtlasSize();
		std::size_t strideH = rendComp->GetAtlas()->h / rendComp->GetAtlasSize();

		GPU_Rect source = 
			{
				strideW * (rendComp->GetAtlasIndex() % rendComp->GetAtlasSize()),
				strideH * (rendComp->GetAtlasIndex() / rendComp->GetAtlasSize()),
				strideW,
				strideH
			};

		auto coords = camera_->ToScreenSpace(position);
		GPU_Rect dest =
			{
				coords.first, coords.second,
				100 * camera_->GetScale(), 100 * camera_->GetScale()
			};
		GPU_BlitRect(rendComp->GetAtlas(), &source, target_, &dest);
	}

	EntityRenderer::~EntityRenderer()
	{

	}
}
