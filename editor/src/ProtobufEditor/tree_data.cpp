#include "ProtobufEditor/tree_data.hpp"
#include "NsCore/ReflectionImplement.h"
#include "NsGui/IntegrationAPI.h"

namespace Editor { namespace ProtobufEditor
{
	using namespace Noesis;
	using namespace google::protobuf;

	TreeMessage::TreeMessage()
	{

	}

	TreeMessage::TreeMessage(Message* message)
		: message_(message),
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

	const char* TreeMessage::GetName() const
	{
		return message_->GetDescriptor()->full_name().c_str();
	}

	NS_IMPLEMENT_REFLECTION(TreeMessage)
	{
		NsMeta<TypeId>("Editor.ProtobufEditor.TreeMessage");
		NsProp("Name", &TreeMessage::GetName);
		NsProp("Items", &TreeMessage::items_);
	}

	TreeOptional::TreeOptional()
	{

	}

	TreeOptional::TreeOptional(Message* message, const FieldDescriptor* field)
		: message_(message), field_(field),
		items_(*new ObservableCollection<BaseComponent>)
	{
		const google::protobuf::Reflection* refl = message->GetReflection();
		
		if (!refl->HasField(*message, field)) return;

		if (field->type() == FieldDescriptor::Type::TYPE_MESSAGE)
		{
			Ptr<TreeMessage> msg = *new TreeMessage(refl->MutableMessage(message, field));
			items_->Add(msg);
		}
	}

	const char* TreeOptional::GetType() const
	{
		return field_->type_name();
	}

	const char* TreeOptional::GetName() const
	{
		return field_->name().c_str();
	}

	bool TreeOptional::GetPresent() const
	{
		return message_->GetReflection()->HasField(*message_, field_);
	}

	void TreeOptional::SetPresent(bool value)
	{
		const google::protobuf::Reflection* refl = message_->GetReflection();

		if (field_->type() == FieldDescriptor::TYPE_MESSAGE)
		{
			if (value)
			{
				Message* submessage =
					MessageFactory::generated_factory()
					->GetPrototype(field_->message_type())->New();

				refl->SetAllocatedMessage(message_, submessage, field_);

				Ptr<TreeMessage> msg = *new TreeMessage(submessage);
				items_->Add(msg);
			}
			else
			{
				message_->GetReflection()->SetAllocatedMessage(message_, nullptr, field_);
				items_->Clear();
			}
		}
	}

	NS_IMPLEMENT_REFLECTION(TreeOptional)
	{
		NsMeta<TypeId>("Editor.ProtobufEditor.TreeOptional");
		NsProp("Name", &TreeOptional::GetName);
		NsProp("Type", &TreeOptional::GetType);
		NsProp("Present", &TreeOptional::GetPresent, &TreeOptional::SetPresent);
		NsProp("Items", &TreeOptional::items_);
	}

	TreeValue::TreeValue(NsString content)
		: content_(content)
	{

	}

	NS_IMPLEMENT_REFLECTION(TreeValue)
	{
		NsMeta<TypeId>("Editor.ProtobufEditor.TreeValue");
		NsProp("Content", &TreeValue::content_);
	}
} }
