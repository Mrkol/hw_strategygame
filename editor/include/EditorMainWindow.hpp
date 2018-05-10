#pragma once

#ifndef EDITOR_EDITOR_MAIN_WINDOW_HPP_
#define EDITOR_EDITOR_MAIN_WINDOW_HPP_

#include "NsCore/ReflectionDeclare.h"
#include "NsApp/Window.h"
#include "entity.pb.h"

namespace Editor
{
	class EditorMainWindow final : public NoesisApp::Window
	{
	public:
		EditorMainWindow();

		void OnInitialized(Noesis::BaseComponent*, const Noesis::EventArgs&);

		Entities::EntityType message;

		NS_DECLARE_REFLECTION(EditorMainWindow, NoesisApp::Window)
	};
}

#endif // EDITOR_EDITOR_MAIN_WINDOW_HPP_
