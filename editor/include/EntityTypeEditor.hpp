#pragma once

#ifndef EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_
#define EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_

#include "NsCore/ReflectionDeclare.h"
#include "NsGui/UserControl.h"

namespace Editor
{
	class EntityTypeEditor final : public Noesis::UserControl
	{
	public:
		EntityTypeEditor();

		NS_DECLARE_REFLECTION(EntityTypeEditor, Noesis::UserControl)
	};
}

#endif // EDITOR_ENTITY_TYPE_EDITOR_WINDOW_HPP_
