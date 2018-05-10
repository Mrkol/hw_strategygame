#pragma once

#ifndef EDITOR_EDITOR_APPLICATION_HPP_
#define EDITOR_EDITOR_APPLICATION_HPP_

#include "NsCore/ReflectionDeclare.h"
#include "NsApp/Application.h"

namespace Editor
{
    class EditorApplication final : public NoesisApp::Application
    {
        NS_DECLARE_REFLECTION(EditorApplication, NoesisApp::Application);
    };
}

#endif // EDITOR_EDITOR_APPLICATION_HPP_
