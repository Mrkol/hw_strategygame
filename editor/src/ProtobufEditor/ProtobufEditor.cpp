#include "ProtobufEditor/ProtobufEditor.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"
#include "ProtobufEditor/tree_data.hpp"


namespace Editor { namespace ProtobufEditor
{
	using namespace google::protobuf;
	using namespace Noesis;

	ProtobufEditor::ProtobufEditor()
	{
        GUI::LoadComponent(this, "ProtobufEditor.xaml");
        messages_ = *new ObservableCollection<BaseComponent>;
	}

	void ProtobufEditor::AddMessage(Message* message)
	{
		Ptr<TreeMessage> mess = *new TreeMessage(message);
		messages_->Add(mess);
	}

	NS_IMPLEMENT_REFLECTION(ProtobufEditor)
	{
		NsMeta<TypeId>("Editor.ProtobufEditor");
		NsProp("Messages", &ProtobufEditor::messages_);
	}
} }
