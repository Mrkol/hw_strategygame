#include "EditorLauncher.hpp"
#include "NsCore/Registercomponent.h"
#include "NsCore/Noesis.h"
#include "EditorApplication.hpp"
#include "EditorMainWindow.hpp"
#include "EditorApplication_xaml.h"
#include "EditorMainWindow_xaml.h"
#include "DejaVuSans_ExtraLight_ttf.h"

namespace Editor
{
    void EditorLauncher::RegisterComponents() const
    {
        NsRegisterComponent<EditorApplication>();
        NsRegisterComponent<EditorMainWindow>();
    }

	Ptr<Noesis::XamlProvider> EditorLauncher::GetXamlProvider() const
	{
		NoesisApp::EmbeddedXaml xamls[] =
		{
			{ "EditorApplication.xaml",
				EditorApplication_xaml, sizeof(EditorApplication_xaml) },
			{ "EditorMainWindow.xaml",
				EditorMainWindow_xaml, sizeof(EditorMainWindow_xaml) }
		};

		return *new NoesisApp::EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
	}

	Ptr<Noesis::FontProvider> EditorLauncher::GetFontProvider() const
	{
		NoesisApp::EmbeddedFont fonts[] =
		{
			{ "", DejaVuSans_ExtraLight_ttf, sizeof(DejaVuSans_ExtraLight_ttf) }
		};

		return *new NoesisApp::EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
	}
}
