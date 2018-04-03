#pragma once

#ifndef EDITOR_EDITOR_LAUNCHER_HPP_
#define EDITOR_EDITOR_LAUNCHER_HPP_

#include "NsApp/ApplicationLauncher.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsApp/EmbeddedFontProvider.h"

namespace Editor
{
	using Noesis::Ptr;

	class EditorLauncher final : public NoesisApp::ApplicationLauncher
	{
	private:
	    void RegisterComponents() const override;

		Ptr<Noesis::XamlProvider> GetXamlProvider() const override;

		Ptr<Noesis::FontProvider> GetFontProvider() const override;
	};
}


#endif // EDITOR_EDITOR_LAUNCHER_HPP_
