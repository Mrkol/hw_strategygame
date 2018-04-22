#pragma once

#ifndef EDITOR_PROTOBUF_EDITOR_HPP_
#define EDITOR_PROTOBUF_EDITOR_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsGui/UserControl.h"
#include "NsCore/Ptr.h"
#include "NsGui/ObservableCollection.h"
#include "NsCore/BaseRefCounted.h"

using Noesis::Ptr;

namespace Editor
{
    class ProtobufEditor final : public Noesis::UserControl
    {
    public:
    	ProtobufEditor();

	private:

		NS_DECLARE_REFLECTION(ProtobufEditor, Noesis::UserControl);
    };

	class TreeMessage final
	{
	public:
		TreeMessage(NsString name);

		NS_DECLARE_REFLECTION(TreeMessage, ITreeElement)

	private:
		NsString content_;
		Ptr<Noesis::ObservableCollection<Ptr<BaseComponent>>> items_;
	};

	class TreeValue final
	{
	public:
		NS_DECLARE_REFLECTION(TreeValue, ITreeElement)

	private:
		NsString content_;
	};
}

#endif // EDITOR_PROTOBUF_EDITOR_HPP_
