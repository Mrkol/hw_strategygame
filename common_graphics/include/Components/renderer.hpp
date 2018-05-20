#pragma once

#ifndef COMMON_GRAPHICS_COMPONENTS_RENDERER_HPP_
#define COMMON_GRAPHICS_COMPONENTS_RENDERER_HPP_

#include <memory>
#include <string>
#include "SDL.hpp"
#include "EntityType.hpp"
#include "EntityInstance.hpp"
#include "IComponentType.hpp"
#include "IComponentInstance.hpp"
#include "CommonHelper.hpp"


namespace Graphics { namespace Components
{
	class RendererComponentInstance;

	class RendererComponent : public Common::IComponentType
	{
		friend class RendererComponentInstance;
	public:

		RendererComponent(GPU_Image* image, std::size_t atlasSize, std::size_t atlasIndex);


		virtual std::shared_ptr<Common::IComponentInstance> Instantiate() override;
		virtual const std::string& GetId() const override;

		GPU_Image* GetAtlas();

		std::size_t GetAtlasSize();

		std::size_t GetAtlasIndex();

		static std::shared_ptr<RendererComponent> 
			Access(std::shared_ptr<Common::EntityType> entityType);

		virtual ~RendererComponent() = default;

	private:
		std::shared_ptr<RendererComponentInstance> access_(
			std::shared_ptr<Common::EntityInstance> instance) const;

		GPU_Image* image_;
		std::size_t atlasSize_;
		std::size_t atlasIndex_;

		static const std::string ID;
	};

	class RendererComponentInstance : public Common::IComponentInstance
	{
		friend class RendererComponent;
	public:
		virtual const std::string& GetTypeId() const override;

		//animation state and such shall be stored here

		virtual ~RendererComponentInstance() = default;
		
	private:
		RendererComponentInstance();
	};
} }

#endif // COMMON_GRAPHICS_COMPONENTS_RENDERER_HPP_
