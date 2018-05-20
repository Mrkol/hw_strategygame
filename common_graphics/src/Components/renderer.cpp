#include "Components/renderer.hpp"

namespace Graphics { namespace Components
{
	RendererComponent::RendererComponent(GPU_Image* image, 
		std::size_t atlasSize, std::size_t atlasIndex)
		: image_(image), atlasSize_(atlasSize), atlasIndex_(atlasIndex)
	{

	}

	const std::string& RendererComponent::GetId() const
	{
		return RendererComponent::ID;
	}

	std::shared_ptr<RendererComponentInstance> RendererComponent::access_(
		std::shared_ptr<Common::EntityInstance> instance) const
	{
		return std::static_pointer_cast<RendererComponentInstance>(instance->GetComponent(ID));
	}

	const std::string RendererComponent::ID = "renderer";

	std::shared_ptr<Common::IComponentInstance> RendererComponent::Instantiate()
	{
		std::shared_ptr<RendererComponentInstance> 
			instance(new RendererComponentInstance());
		return instance;
	}


	GPU_Image* RendererComponent::GetAtlas()
	{
		return image_;
	}

	std::size_t RendererComponent::GetAtlasSize()
	{
		return atlasSize_;
	}

	std::size_t RendererComponent::GetAtlasIndex()
	{
		return atlasIndex_;
	}

	std::shared_ptr<RendererComponent>
		RendererComponent::Access(std::shared_ptr<Common::EntityType> entityType)
	{
		return std::static_pointer_cast<RendererComponent>(entityType->GetComponent(ID));
	}

	const std::string& RendererComponentInstance::GetTypeId() const
	{
		return RendererComponent::ID;
	}

	RendererComponentInstance::RendererComponentInstance()
	{
	}
} }
