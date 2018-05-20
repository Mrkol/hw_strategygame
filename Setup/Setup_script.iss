; Script generated by the Inno Script Studio Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Ultimate Strategy: return of deadlines"
#define MyAppVersion "0.0000000001"
#define MyAppPublisher "Botalka gk encorporated"
#define MyAppURL "http://www.github.com/"
#define MyAppExeName "client.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{721DFEE1-8421-4113-AB97-0F5D6DCCD981}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputBaseFilename=setup
Compression=lzma
SolidCompression=yes
AppComments=Enjoy your time, friend!
AppContact=No connection
AppReadmeFile=Here be dragons...

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "C:\hw_strategygame\build\client\client.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\glew32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\glew32d.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\libprotobuf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\Noesis.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\NoesisApp.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\hw_strategygame\build\client\SDL2_gpud.dll"; DestDir: "{app}"; Flags: ignoreversion


[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent
