#include "ProtobufEditor.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"


namespace Editor
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

	TreeMessage::TreeMessage()
	{

	}

	TreeMessage::TreeMessage(Message* message)
		: message_(message),
		name_(message_->GetTypeName().c_str()),
		items_(*new ObservableCollection<BaseComponent>)
	{
		const Descriptor* desc = message->GetDescriptor();
		const google::protobuf::Reflection* refl = message->GetReflection();

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
				Ptr<TreeOptional> opt = 
					*new TreeOptional(message, field);
				items_->Add(opt);
			}
			else if (field->label() == FieldDescriptor::Label::LABEL_REPEATED)
			{
				//complicated things
			}
		}
	}

	NS_IMPLEMENT_REFLECTION(TreeMessage)
	{
		NsMeta<TypeId>("Editor.ProtobufEditorTreeMessage");
		NsProp("Name", &TreeMessage::name_);
		NsProp("Items", &TreeMessage::items_);
	}

	TreeOptional::TreeOptional()
	{

	}

	TreeOptional::TreeOptional(Message* message, const FieldDescriptor* field)
		: message_(message), field_(field),
		name_(field_->name().c_str()), type_(field_->type_name()),
		items_(*new ObservableCollection<BaseComponent>)
	{

	}

	NS_IMPLEMENT_REFLECTION(TreeOptional)
	{
		NsMeta<TypeId>("Editor.ProtobufEditorTreeOptional");
		NsProp("Name", &TreeOptional::name_);
		NsProp("Type", &TreeOptional::type_);
		NsProp("Items", &TreeOptional::items_);
	}

	TreeValue::TreeValue(NsString content)
		: content_(content)
	{

	}

	NS_IMPLEMENT_REFLECTION(TreeValue)
	{
		NsMeta<TypeId>("Editor.ProtobufEditorTreeValue");
		NsProp("Content", &TreeValue::content_);
	}

	NS_IMPLEMENT_REFLECTION(ProtobufEditor)
	{
		NsMeta<TypeId>("Editor.ProtobufEditor");
		NsProp("Messages", &ProtobufEditor::messages_);
	}
}
