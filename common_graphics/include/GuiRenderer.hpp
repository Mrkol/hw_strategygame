#pragma once

#ifndef COMMON_GRAPHICS_GUI_RENDERER_HPP_
#define COMMON_GRAPHICS_GUI_RENDERER_HPP_

#include <cstdint>
#include "NsGui/IntegrationAPI.h"
#include "NsGui/InputEnums.h"
#include "NsRender/RenderDevice.h"
#include "UserInputManager.hpp"


namespace Graphics
{
	class GuiRenderer
	{
	public:
		GuiRenderer();

		void Init(Graphics::UserInputManager& inputManager,
			int32_t width, int32_t height);

		void PreRender();
		void Render();

		void OnResized(int32_t width, int32_t height);

		Noesis::Ptr<Noesis::XamlProvider> CreateXamlProvider() const;
		Noesis::Ptr<Noesis::TextureProvider> CreateTextureProvider() const;
		Noesis::Ptr<Noesis::FontProvider> CreateFontProvider() const;

		static void NoesisLogHandler(const char* filename, uint32_t line, 
			uint32_t level, const char* channel, const char* message);

		~GuiRenderer();


		static Noesis::MouseButton MouseButtonSDLtoNoesis(uint32_t button);

	private:
		Noesis::Ptr<Noesis::FrameworkElement> currentScreen_;
		Noesis::Ptr<Noesis::IView> view_;
		Noesis::Ptr<Noesis::RenderDevice> device_;
	};
}

#endif // COMMON_GRAPHICS_GUI_RENDERER_HPP_
