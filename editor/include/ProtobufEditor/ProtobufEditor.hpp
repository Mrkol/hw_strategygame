#pragma once

#ifndef EDITOR_PROTOBUF_EDITOR_PROTOBUF_EDITOR_HPP_
#define EDITOR_PROTOBUF_EDITOR_PROTOBUF_EDITOR_HPP_

#include "NsCore/ReflectionDeclare.h"
#include "NsGui/UserControl.h"
#include "NsCore/Ptr.h"
#include "NsGui/ObservableCollection.h"
#include "NsCore/BaseRefCounted.h"
#include "google/protobuf/message.h"

using Noesis::Ptr;

namespace Editor { namespace ProtobufEditor
{
	class ProtobufEditor final : public Noesis::UserControl
	{
	public:
		ProtobufEditor();

		void AddMessage(google::protobuf::Message* message);

		NS_DECLARE_REFLECTION(ProtobufEditor, Noesis::UserControl);

	private:
		Ptr<Noesis::ObservableCollection<Noesis::BaseComponent>> messages_;
	};
} }

#endif // EDITOR_PROTOBUF_EDITOR_PROTOBUF_EDITOR_HPP_
