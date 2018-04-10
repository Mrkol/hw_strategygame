#pragma once

#ifndef EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_
#define EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsApp/Window.h"

namespace Editor
{
	class EntityTypeEditorWindow final : public NoesisApp::Window
	{
	public:
		EntityTypeEditorWindow();

		NS_IMPLEMENT_INLINE_REFLECTION(EntityTypeEditorWindow, NoesisApp::Window)
		{
			NsMeta<Noesis::TypeId>("Editor.EntityTypeEditorWindow");
		}
	};
}

#endif // EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_
