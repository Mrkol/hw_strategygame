#include "EditorLauncher.hpp"
#include "NsCore/RegisterComponent.h"
#include "NsCore/Noesis.h"
#include "EditorApplication.hpp"
#include "EditorMainWindow.hpp"
#include "EntityTypeEditor.hpp"
#include "ProtobufEditor/ProtobufEditor.hpp"
#include "ProtobufEditor/tree_data.hpp"

#include "osgViewer/Viewer"
#include "osg/Notify"
#include "osgDB/ReadFile"

#include "EditorApplication_xaml.hpp"
#include "EditorMainWindow_xaml.hpp"
#include "EntityTypeEditor_xaml.hpp"
#include "ProtobufEditor_xaml.hpp"
#include "OpenSans_Regular_ttf.hpp"


namespace Editor
{
	EditorLauncher::EditorLauncher()
		: viewer_(new osgViewer::Viewer)
	{
		/*
		osg::ref_ptr<osg::Texture2D> texture = 
			new osg::Texture2D; 
		osg::ref_ptr<osg::Camera> camera = 
			CreateOSGCamera(1600, 900, texture.get()); 

		osg::ref_ptr<osg::Group> root = new osg::Group; 
		root->addChild(camera.get());

		viewer_.setSceneData(root.get());

		this->GetDisplay()->Render() += 
			Noesis::MakeDelegate(this, &EditorLauncher::RenderOSG);
		*/

		// left window + left slave camera
		{
			osg::ref_ptr<osg::GraphicsContext::Traits> traits = 
				new osg::GraphicsContext::Traits;

			traits->width = 600;
			traits->height = 480;
			traits->windowDecoration = true;
			traits->doubleBuffer = true;
			traits->sharedContext = 0;

			osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());

			osg::ref_ptr<osg::Camera> camera = new osg::Camera;
			camera->setGraphicsContext(gc.get());
			camera->setViewport(new osg::Viewport(0,0, traits->width, traits->height));
			GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
			camera->setDrawBuffer(buffer);
			camera->setReadBuffer(buffer);

			// add this slave camera to the viewer, with a shift left of the projection matrix
			viewer_->addSlave(camera.get(), osg::Matrixd::translate(1.0,0.0,0.0), osg::Matrixd());
		}
		
		osg::ref_ptr<osg::Node> modelNode = osgDB::readNodeFile(".\\cow.osg");
		osg::ref_ptr<osg::Group> root = new osg::Group();
		root->addChild(modelNode.get());
		viewer_->setSceneData(root.get());

		viewer_->realize();
	}

	/*osg::Camera* EditorLauncher::CreateOSGCamera(
		int width, int height, osg::Texture2D* texture)
	{
		texture->setTextureSize(width, height); 
		texture->setInternalFormat(GL_RGB); 
		texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR); 
		texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR); 

		osg::ref_ptr<osg::Camera> rttCamera = new osg::Camera; 

		rttCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		rttCamera->setClearColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f)); 
		rttCamera->setViewport(0, 0, width, height); 
		rttCamera->setRenderOrder(osg::Camera::PRE_RENDER); 
		rttCamera->setReferenceFrame(osg::Transform::RELATIVE_RF); 
		rttCamera->setRenderTargetImplementation(
			osg::Camera::FRAME_BUFFER_OBJECT); 
		rttCamera->attach(osg::Camera::COLOR_BUFFER, texture); 

		return rttCamera.release(); 
	}*/

	void EditorLauncher::RenderOSG(NoesisApp::Display* display)
	{
		viewer_->frame();
	}

	void EditorLauncher::RegisterComponents() const
	{
		NsRegisterComponent<EditorApplication>();
		NsRegisterComponent<EditorMainWindow>();
		NsRegisterComponent<EntityTypeEditor>();
		NsRegisterComponent<ProtobufEditor::ProtobufEditor>();
		NsRegisterComponent<ProtobufEditor::TreeMessage>();
		NsRegisterComponent<ProtobufEditor::TreeOptional>();
		NsRegisterComponent<ProtobufEditor::TreeValue>();
	}

	Ptr<Noesis::XamlProvider> EditorLauncher::GetXamlProvider() const
	{
		NoesisApp::EmbeddedXaml xamls[] =
		{
			{ "EditorApplication.xaml",
				EditorApplication_xaml, EditorApplication_xaml_size },
			{ "EditorMainWindow.xaml",
				EditorMainWindow_xaml, EditorMainWindow_xaml_size },
			{ "EntityTypeEditor.xaml",
				EntityTypeEditor_xaml, EntityTypeEditor_xaml_size },
			{ "ProtobufEditor.xaml",
				ProtobufEditor_xaml, ProtobufEditor_xaml_size }
		};

		return *new NoesisApp::EmbeddedXamlProvider(xamls, NS_COUNTOF(xamls));
	}

	Ptr<Noesis::FontProvider> EditorLauncher::GetFontProvider() const
	{
		NoesisApp::EmbeddedFont fonts[] =
		{
			{ "", OpenSans_Regular_ttf, OpenSans_Regular_ttf_size }
		};

		return *new NoesisApp::EmbeddedFontProvider(fonts, NS_COUNTOF(fonts));
	}
}
