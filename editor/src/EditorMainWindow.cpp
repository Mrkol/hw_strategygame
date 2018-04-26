#include "EditorMainWindow.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"
#include "ProtobufEditor.hpp"

namespace Editor
{
	EditorMainWindow::EditorMainWindow()
		: message()
	{
		Noesis::GUI::LoadComponent(this, "EditorMainWindow.xaml");

		message.set_type_id("Kek");
		message.mutable_position();
		message.mutable_health();

        Initialized() += MakeDelegate(this, &EditorMainWindow::OnInitialized);
	}

	void EditorMainWindow::OnInitialized(Noesis::BaseComponent*, const Noesis::EventArgs&)
	{
		ProtobufEditor* editor = FindName<ProtobufEditor>("Proto");
		editor->AddMessage(&message);
	}

	NS_IMPLEMENT_REFLECTION(EditorMainWindow)
	{
		NsMeta<Noesis::TypeId>("Editor.EditorMainWindow");
	}
}
