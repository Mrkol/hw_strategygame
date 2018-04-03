#include "editor_main.hpp"
#include "NsApp/EntryPoint.h"
#include "EditorLauncher.hpp"

int NsMain(int argc, char** argv)
{
	Editor::EditorLauncher launcher;
	launcher.SetArguments(argc, argv);
	launcher.SetApplicationFile("EditorApplication.xaml");
	return launcher.Run();
}
