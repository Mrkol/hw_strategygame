#pragma once

#ifndef EDITOR_PROTOBUF_EDITOR_HPP_
#define EDITOR_PROTOBUF_EDITOR_HPP_

#include "NsCore/ReflectionDeclare.h"
#include "NsGui/UserControl.h"
#include "NsCore/Ptr.h"
#include "NsGui/ObservableCollection.h"
#include "NsCore/BaseRefCounted.h"
#include "google/protobuf/message.h"

using Noesis::Ptr;

namespace Editor
{
	class ProtobufEditor final : public Noesis::UserControl
	{
	public:
		ProtobufEditor();

		void AddMessage(::google::protobuf::Message* message);

		NS_DECLARE_REFLECTION(ProtobufEditor, Noesis::UserControl);

	private:
		Ptr<Noesis::ObservableCollection<Noesis::BaseComponent>> messages_;
	};

	class TreeMessage final : public Noesis::BaseComponent
	{
	public:
		TreeMessage();

		TreeMessage(::google::protobuf::Message* message);

		NS_DECLARE_REFLECTION(TreeMessage, Noesis::BaseComponent)

	private:
		NsString name_;
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
}

#endif // EDITOR_PROTOBUF_EDITOR_HPP_
