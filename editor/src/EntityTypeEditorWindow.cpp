#include "EntityTypeEditorWindow.hpp"
#include "NsGui/IntegrationAPI.h"

namespace Editor
{
	EntityTypeEditorWindow::EntityTypeEditorWindow()
	{
		Noesis::GUI::LoadComponent(this, "EntityTypeEditorWindow.xaml");
	}
}
