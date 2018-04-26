#include "ProtobufEditor.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"


namespace Editor
{
	using namespace ::google::protobuf;

	ProtobufEditor::ProtobufEditor()
	{
        Noesis::GUI::LoadComponent(this, "ProtobufEditor.xaml");
        messages_ = *new Noesis::ObservableCollection<Noesis::BaseComponent>;
        
	}

	void ProtobufEditor::AddMessage(::google::protobuf::Message* message)
	{
		Ptr<TreeMessage> mess = *new TreeMessage(message);
		messages_->Add(mess);
	}

	TreeMessage::TreeMessage()
		: items_(*new Noesis::ObservableCollection<Noesis::BaseComponent>)
	{

	}

	TreeMessage::TreeMessage(Message* message)
		: TreeMessage()
	{
		const Descriptor* desc = message->GetDescriptor();
		const Reflection* refl = message->GetReflection();
		name_ = desc->name().c_str();
		for (int i = 0; i < desc->field_count(); ++i)
		{
			const FieldDescriptor* field = desc->field(i);
			if (field->label() == FieldDescriptor::Label::LABEL_REQUIRED)
			{	
				if (field->type() == FieldDescriptor::Type::TYPE_MESSAGE)
				{
					Ptr<TreeMessage> msg = *new TreeMessage(refl->MutableMessage(message, field));
					items_->Add(msg);
				}
			}
			else if (field->label() == FieldDescriptor::Label::LABEL_OPTIONAL)
			{
				//something
			}
			else if (field->label() == FieldDescriptor::Label::LABEL_REPEATED)
			{
				//complicated things
			}
		}
	}

	NS_IMPLEMENT_REFLECTION(TreeMessage)
	{
		NsMeta<Noesis::TypeId>("Editor.ProtobufEditorTreeMessage");
		NsProp("Name", &TreeMessage::name_);
		NsProp("Items", &TreeMessage::items_);
	}

	TreeValue::TreeValue(NsString content)
		: content_(content)
	{

	}

	NS_IMPLEMENT_REFLECTION(TreeValue)
	{
		NsMeta<Noesis::TypeId>("Editor.ProtobufEditorTreeValue");
		NsProp("Content", &TreeValue::content_);
	}

	NS_IMPLEMENT_REFLECTION(ProtobufEditor)
	{
		NsMeta<Noesis::TypeId>("Editor.ProtobufEditor");
		NsProp("Messages", &ProtobufEditor::messages_);
	}
}
