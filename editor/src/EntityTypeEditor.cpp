#include "EntityTypeEditor.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"

namespace Editor
{
	EntityTypeEditor::EntityTypeEditor()
	{
		Noesis::GUI::LoadComponent(this, "EntityTypeEditor.xaml");
	}


	NS_IMPLEMENT_REFLECTION(EntityTypeEditor)
	{
		NsMeta<Noesis::TypeId>("EntityTypeEditor");
	}
}
