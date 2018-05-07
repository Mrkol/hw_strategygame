#pragma once

#ifndef EDITOR_EDITOR_LAUNCHER_HPP_
#define EDITOR_EDITOR_LAUNCHER_HPP_

#include "NsApp/ApplicationLauncher.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsApp/EmbeddedFontProvider.h"

namespace Editor
{
	class EditorLauncher final : public NoesisApp::ApplicationLauncher
	{
	public:
		EditorLauncher();

	private:
	    void RegisterComponents() const override;

		Noesis::Ptr<Noesis::XamlProvider> GetXamlProvider() const override;

		Noesis::Ptr<Noesis::FontProvider> GetFontProvider() const override;
	};
}


#endif // EDITOR_EDITOR_LAUNCHER_HPP_
