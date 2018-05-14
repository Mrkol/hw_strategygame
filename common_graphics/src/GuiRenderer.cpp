#include "GuiRenderer.hpp"

#include "SDL.hpp"
#include "GL/glew.h"
#include "SDL_opengl.h"
#include "GL/glu.h"

#include "NsCore/Noesis.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsApp/LocalTextureProvider.h"
#include "NsApp/EmbeddedFontProvider.h"
#include "NsRender/GLFactory.h"
#include "NsGui/IView.h"
#include "NsGui/IRenderer.h"
#include "NsGui/FrameworkElement.h"

#include "OpenSans_Regular_ttf.hpp"
#include "DiagnosticOverlay_xaml.hpp"


namespace Graphics
{
	GuiRenderer::GuiRenderer()
		: currentScreen_(nullptr), view_(nullptr), device_(nullptr)
	{

	}

	void GuiRenderer::Init(int32_t width, int32_t height)
	{
		Noesis::GUI::Init(nullptr, GuiRenderer::NoesisLogHandler, nullptr);

		Noesis::GUI::SetXamlProvider(CreateXamlProvider());
		Noesis::GUI::SetTextureProvider(CreateTextureProvider());
		Noesis::GUI::SetFontProvider(CreateFontProvider());

		currentScreen_ = Noesis::GUI::LoadXaml<Noesis::FrameworkElement>("DiagnosticOverlay.xaml");
		view_ = Noesis::GUI::CreateView(currentScreen_);
		view_->SetSize(width, height);
		view_->SetIsPPAAEnabled(true);

		device_ = NoesisApp::GLFactory::CreateDevice();
		view_->GetRenderer()->Init(device_);
	}

	void GuiRenderer::PreRender()
	{
		double time = SDL_GetTicks();
		view_->Update(time);

		view_->GetRenderer()->UpdateRenderTree();
		view_->GetRenderer()->RenderOffscreen();
	}

	void GuiRenderer::Render()
	{
		view_->GetRenderer()->Render();
	}

	void GuiRenderer::OnResized(int32_t width, int32_t height)
	{
		view_->SetSize(width, height);
	}

	Noesis::Ptr<Noesis::XamlProvider> GuiRenderer::CreateXamlProvider() const
	{
		NoesisApp::EmbeddedXaml xamls[] =
		{
			{ "DiagnosticOverlay.xaml",
				DiagnosticOverlay_xaml, DiagnosticOverlay_xaml_size }
		};

		return *new NoesisApp::EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
	}

	Noesis::Ptr<Noesis::TextureProvider> GuiRenderer::CreateTextureProvider() const
	{
		return *new NoesisApp::LocalTextureProvider(".");
	}

	Noesis::Ptr<Noesis::FontProvider> GuiRenderer::CreateFontProvider() const
	{
		NoesisApp::EmbeddedFont fonts[] =
		{
			{ "", OpenSans_Regular_ttf, OpenSans_Regular_ttf_size }
		};

		return *new NoesisApp::EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
	}

	void GuiRenderer::NoesisLogHandler(const char* filename, uint32_t line, 
		uint32_t level, const char* channel, const char* message)
	{
		if (strcmp(channel, "") != 0) return;

        const char* prefixes[] = { "T", "D", "I", "W", "E" };
        const char* prefix = level < NS_COUNTOF(prefixes) ? prefixes[level] : " ";
		SDL_Log("[NOESIS/%s] %s", prefix, message);
	}

	GuiRenderer::~GuiRenderer()
	{
		view_->GetRenderer()->Shutdown();
		view_.Reset();
		currentScreen_.Reset();
		device_.Reset();
		Noesis::GUI::Shutdown();
	}
}
