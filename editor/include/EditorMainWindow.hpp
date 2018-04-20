#pragma once

#ifndef EDITOR_EDITOR_MAIN_WINDOW_HPP_
#define EDITOR_EDITOR_MAIN_WINDOW_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsApp/Window.h"

namespace Editor
{
	class EditorMainWindow final : public NoesisApp::Window
	{
	public:
		EditorMainWindow();

		NS_DECLARE_REFLECTION(EditorMainWindow, NoesisApp::Window)
	};
}

#endif // EDITOR_EDITOR_MAIN_WINDOW_HPP_
