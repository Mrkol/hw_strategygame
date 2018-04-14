#include "EditorLauncher.hpp"
#include "NsCore/RegisterComponent.h"
#include "NsCore/Noesis.h"
#include "EditorApplication.hpp"
#include "EditorMainWindow.hpp"
#include "EntityTypeEditor.hpp"

#include "EditorApplication_xaml.hpp"
#include "EditorMainWindow_xaml.hpp"
#include "EntityTypeEditor_xaml.hpp"
#include "DejaVuSans_ExtraLight_ttf.hpp"

namespace Editor
{
    void EditorLauncher::RegisterComponents() const
    {
        NsRegisterComponent<EditorApplication>();
        NsRegisterComponent<EditorMainWindow>();
        NsRegisterComponent<EntityTypeEditor>();
    }

	Ptr<Noesis::XamlProvider> EditorLauncher::GetXamlProvider() const
	{
		NoesisApp::EmbeddedXaml xamls[] =
		{
			{ "EditorApplication.xaml",
				EditorApplication_xaml, EditorApplication_xaml_size },
			{ "EditorMainWindow.xaml",
				EditorMainWindow_xaml, EditorMainWindow_xaml_size },
			{ "EntityTypeEditorWindow.xaml",
				EntityTypeEditor_xaml, EntityTypeEditor_xaml_size }
		};

		return *new NoesisApp::EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
	}

	Ptr<Noesis::FontProvider> EditorLauncher::GetFontProvider() const
	{
		NoesisApp::EmbeddedFont fonts[] =
		{
			{ "", DejaVuSans_ExtraLight_ttf, DejaVuSans_ExtraLight_ttf_size }
		};

		return *new NoesisApp::EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
	}
}
