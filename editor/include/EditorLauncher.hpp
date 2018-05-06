#pragma once

#ifndef EDITOR_EDITOR_LAUNCHER_HPP_
#define EDITOR_EDITOR_LAUNCHER_HPP_

#include "NsApp/ApplicationLauncher.h"
#include "NsApp/EmbeddedXamlProvider.h"
#include "NsApp/EmbeddedFontProvider.h"

#include "osg/ref_ptr"
#include "osg/Camera"
#include "osg/Texture2D"
#include "osgViewer/Viewer"
#include "osgViewer/GraphicsWindow"

namespace Editor
{
	class EditorLauncher final : public NoesisApp::ApplicationLauncher
	{
	public:
		EditorLauncher();

	private:
		osg::Camera* CreateOSGCamera(
			int width, int height, osg::Texture2D* texture);
		void RenderOSG(NoesisApp::Display* display);

	    void RegisterComponents() const override;

		Noesis::Ptr<Noesis::XamlProvider> GetXamlProvider() const override;

		Noesis::Ptr<Noesis::FontProvider> GetFontProvider() const override;

		osg::ref_ptr<osgViewer::Viewer> viewer_;
		osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> context_;
	};
}


#endif // EDITOR_EDITOR_LAUNCHER_HPP_
