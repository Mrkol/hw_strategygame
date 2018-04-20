#pragma once

#ifndef EDITOR_EDITOR_APPLICATION_HPP_
#define EDITOR_EDITOR_APPLICATION_HPP_

#include "NsCore/ReflectionImplement.h"
#include "NsApp/Application.h"

namespace Editor
{
    class EditorApplication final : public NoesisApp::Application
    {
        NS_IMPLEMENT_INLINE_REFLECTION(EditorApplication, NoesisApp::Application)
        {
            NsMeta<Noesis::TypeId>("Editor.Application");
        }
    };
}

#endif // EDITOR_EDITOR_APPLICATION_HPP_
