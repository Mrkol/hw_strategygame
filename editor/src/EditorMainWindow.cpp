#include "EditorMainWindow.hpp"
#include "NsGui/IntegrationAPI.h"

namespace Editor
{
	EditorMainWindow::EditorMainWindow()
	{
		Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
	}

	NS_IMPLEMENT_REFLECTION(EditorMainWindow)
	{
		NsMeta<Noesis::TypeId>("Editor.MainWindow");
	}
}
