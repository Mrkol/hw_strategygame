#include "EditorLauncher.hpp"
#include "NsCore/RegisterComponent.h"
#include "NsCore/Noesis.h"
#include "EditorApplication.hpp"
#include "EditorMainWindow.hpp"
#include "EntityTypeEditor.hpp"
#include "ProtobufEditor.hpp"

#include "EditorApplication_xaml.hpp"
#include "EditorMainWindow_xaml.hpp"
#include "EntityTypeEditor_xaml.hpp"
#include "ProtobufEditor_xaml.hpp"
#include "OpenSans_Regular_ttf.hpp"

namespace Editor
{
    void EditorLauncher::RegisterComponents() const
    {
        NsRegisterComponent<EditorApplication>();
        NsRegisterComponent<EditorMainWindow>();
        NsRegisterComponent<EntityTypeEditor>();
		NsRegisterComponent<ProtobufEditor>();
		NsRegisterComponent<TreeMessage>();
		NsRegisterComponent<TreeOptional>();
		NsRegisterComponent<TreeValue>();
    }

	Ptr<Noesis::XamlProvider> EditorLauncher::GetXamlProvider() const
	{
		NoesisApp::EmbeddedXaml xamls[] =
		{
			{ "EditorApplication.xaml",
				EditorApplication_xaml, EditorApplication_xaml_size },
			{ "EditorMainWindow.xaml",
				EditorMainWindow_xaml, EditorMainWindow_xaml_size },
			{ "EntityTypeEditor.xaml",
				EntityTypeEditor_xaml, EntityTypeEditor_xaml_size },
			{ "ProtobufEditor.xaml",
				ProtobufEditor_xaml, ProtobufEditor_xaml_size }
		};

		return *new NoesisApp::EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
	}

	Ptr<Noesis::FontProvider> EditorLauncher::GetFontProvider() const
	{
		NoesisApp::EmbeddedFont fonts[] =
		{
			{ "", OpenSans_Regular_ttf, OpenSans_Regular_ttf_size }
		};

		return *new NoesisApp::EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
	}
}
