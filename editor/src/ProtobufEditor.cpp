#include "ProtobufEditor.hpp"


namespace Editor
{
	TreeMessage::TreeMessage(NsString name)
		: content_(name)
	{

	}

	NsString TreeMessage::GetContent()
	{

	}

	void TreeMessage::SetContent(NsString value)
	{

	}

	NS_IMPLEMENT_REFLECTION(TreeMessage)
	{
		NsMeta<Noesis::TypeId>("Editor.ProtobufEditor.TreeMessage");
		NsProp("content", &TreeValue::content_);
	}

	NS_IMPLEMENT_REFLECTION(TreeValue)
	{
		NsMeta<Noesis::TypeId>("Editor.ProtobufEditor.TreeValue");
		NsProp("content", &TreeValue::content_);
	}
}