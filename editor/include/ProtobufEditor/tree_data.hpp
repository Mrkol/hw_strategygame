#pragma once

#ifndef EDITOR_PROTOBUF_EDITOR_TREE_DATA_HPP_
#define EDITOR_PROTOBUF_EDITOR_TREE_DATA_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsGui/ObservableCollection.h"
#include "google/protobuf/message.h"
#include "NsGui/IntegrationAPI.h"
#include "NsGui/RoutedEvent.h"

namespace Editor { namespace ProtobufEditor
{
	using Noesis::Ptr;

	class TreeMessage final : public Noesis::BaseComponent
	{
	public:
		TreeMessage();
		TreeMessage(google::protobuf::Message* message);

		const char* GetName() const;

		NS_DECLARE_REFLECTION(TreeMessage, Noesis::BaseComponent)

	private:
		google::protobuf::Message* message_;

		Ptr<Noesis::ObservableCollection<Noesis::BaseComponent>> items_;
	};

	class TreeOptional final : public Noesis::BaseComponent
	{
	public:
		TreeOptional();

		TreeOptional(google::protobuf::Message* message, 
			const google::protobuf::FieldDescriptor* field);

		const char* GetType() const;
		const char* GetName() const;
		const char* GetButtonLabel() const;

		NS_DECLARE_REFLECTION(TreeOptional, Noesis::BaseComponent)
	private:
	    void onRemoveClick(BaseComponent* sender, const Noesis::RoutedEventArgs& args);



		google::protobuf::Message* message_;
		const google::protobuf::FieldDescriptor* field_;

		Ptr<Noesis::ObservableCollection<Noesis::BaseComponent>> items_;
	};

	class TreeValue final : public Noesis::BaseComponent
	{
	public:
		TreeValue(NsString name = "Value");

		NS_DECLARE_REFLECTION(TreeValue, Noesis::BaseComponent)

	private:
		NsString content_;
	};
} }

#endif // EDITOR_PROTOBUF_EDITOR_TREE_DATA_HPP_
