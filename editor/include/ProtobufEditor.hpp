#pragma once

#ifndef EDITOR_PROTOBUF_EDITOR_HPP_
#define EDITOR_PROTOBUF_EDITOR_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsGui/UserControl.h"
#include "NsCore/Ptr.h"
#include "NsGui/ObservableCollection.h"

using Noesis::Ptr;

namespace Editor
{
    class ProtobufEditor final : public Noesis::UserControl
    {
    public:
    	ProtobufEditor();

	private:
		class ITreeElement : public Noesis::Interface
		{
		public:
			virtual NsString GetContent() = 0;
			virtual void SetContent(NsString value) = 0;

			NS_IMPLEMENT_INLINE_REFLECTION_(ITreeElement, Interface)
		};

		class TreeMessage final : public ITreeElement
		{
		public:
			virtual NsString GetContent() override;
			virtual void SetContent(NsString value) override;

		    Ptr<Noesis::ObservableCollection<Ptr<ITreeElement>>> Items;

			NS_IMPLEMENT_INTERFACE_FIXUP

			NS_DECLARE_REFLECTION(TreeMessage, ITreeElement)
		};

		class TreeValue final : public ITreeElement
		{
		public:
			virtual NsString GetContent() override;
			virtual void SetContent(NsString value) override;

			NsString Content;

			NS_IMPLEMENT_INTERFACE_FIXUP
			
			NS_DECLARE_REFLECTION(TreeValue, ITreeElement)
		};

		NS_DECLARE_REFLECTION(ProtobufEditor, Noesis::UserControl);
    };
}

#endif // EDITOR_PROTOBUF_EDITOR_HPP_
