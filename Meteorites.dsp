# Microsoft Developer Studio Project File - Name="Meteorites" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Meteorites - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Meteorites.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Meteorites.mak" CFG="Meteorites - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Meteorites - Win32 Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Meteorites - Win32 Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Meteorites - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "c:\develop\projects\Reality\Objects\i386-vc\Meteorites\Release"
# PROP Intermediate_Dir "c:\develop\projects\Reality\Objects\i386-vc\Meteorites\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MT /W2 /GX /Z7 /O2 /I ".." /I "../3dapi" /I "../3dapi/Network" /I "../3dapi/Network/Drivers" /I "../Drivers" /I "../Devices" /I "../Devices/Input" /I "../GameServer" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D MAX_PLAYERS=30 /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 libc.lib oldnames.lib wsock32.lib libdtimt.lib libsrlmt.lib libdxxmt.lib zlib.lib pnglib.lib glide2x.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /profile /map:"C:\RealityMakers\Meteorites\Meteorites.map" /debug /machine:I386 /nodefaultlib /out:"c:\RealityMakers\Meteorites\Meteorites.dll"

!ELSEIF  "$(CFG)" == "Meteorites - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "c:\develop\projects\Reality\Objects\i386-vc\Meteorites\Debug"
# PROP Intermediate_Dir "c:\develop\projects\Reality\Objects\i386-vc\Meteorites\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /MTd /W2 /GX /Z7 /Od /I ".." /I "../3dapi" /I "../3dapi/Network" /I "../3dapi/Network/Drivers" /I "../Drivers" /I "../Devices" /I "../Devices/Input" /I "../GameServer" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NTSDK" /D MAX_PLAYERS=30 /YX /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 glide2x.lib libdtimt.lib libsrlmt.lib libdxxmt.lib libcmt.lib zlib.lib pnglib.lib kernel32.lib user32.lib wsock32.lib user32.lib gdi32.lib kernel32.lib advapi32.lib /nologo /version:0.1 /stack:0x1e8480 /subsystem:windows /dll /incremental:no /map /debug /machine:I386 /nodefaultlib /out:"c:\RealityMakers\Meteorites\db_Meteorites.dll"
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "Meteorites - Win32 Release"
# Name "Meteorites - Win32 Debug"
# Begin Source File

SOURCE=.\Background.cpp
# End Source File
# Begin Source File

SOURCE=.\Background.h
# End Source File
# Begin Source File

SOURCE=.\BlueStrobe.cpp
# End Source File
# Begin Source File

SOURCE=.\BlueStrobe.h
# End Source File
# Begin Source File

SOURCE=.\Boost.cpp
# End Source File
# Begin Source File

SOURCE=.\Boost.h
# End Source File
# Begin Source File

SOURCE=.\CameraAI.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraAI.h
# End Source File
# Begin Source File

SOURCE=.\Fireball.cpp
# End Source File
# Begin Source File

SOURCE=.\Fireball.h
# End Source File
# Begin Source File

SOURCE=.\FirePickup.cpp
# End Source File
# Begin Source File

SOURCE=.\FirePickup.h
# End Source File
# Begin Source File

SOURCE=.\Flare.cpp
# End Source File
# Begin Source File

SOURCE=.\Flare.h
# End Source File
# Begin Source File

SOURCE=.\LensFlare.cpp
# End Source File
# Begin Source File

SOURCE=.\LensFlare.h
# End Source File
# Begin Source File

SOURCE=.\Meteorites.cpp

!IF  "$(CFG)" == "Meteorites - Win32 Release"

!ELSEIF  "$(CFG)" == "Meteorites - Win32 Debug"

# ADD CPP /GB
# SUBTRACT CPP /O<none>

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Meteorites.h
# End Source File
# Begin Source File

SOURCE=.\Nebula.cpp
# End Source File
# Begin Source File

SOURCE=.\Nebula.h
# End Source File
# Begin Source File

SOURCE=.\Number.cpp
# End Source File
# Begin Source File

SOURCE=.\Number.h
# End Source File
# Begin Source File

SOURCE=.\PhoneNumber.cpp
# End Source File
# Begin Source File

SOURCE=.\PhoneNumber.h
# End Source File
# Begin Source File

SOURCE=.\Planet.cpp
# End Source File
# Begin Source File

SOURCE=.\Planet.h
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# Begin Source File

SOURCE=.\Process_startup.cpp
# End Source File
# Begin Source File

SOURCE=.\Process_startup.h
# End Source File
# Begin Source File

SOURCE=.\RedStrobe.cpp
# End Source File
# Begin Source File

SOURCE=.\RedStrobe.h
# End Source File
# Begin Source File

SOURCE=.\RockAI.cpp
# End Source File
# Begin Source File

SOURCE=.\RockAI.h
# End Source File
# Begin Source File

SOURCE=.\Scene.cpp
# End Source File
# Begin Source File

SOURCE=.\Scene.h
# End Source File
# Begin Source File

SOURCE=.\ScoreViews.cpp
# End Source File
# Begin Source File

SOURCE=.\ScoreViews.h
# End Source File
# Begin Source File

SOURCE=.\Shield.cpp
# End Source File
# Begin Source File

SOURCE=.\Shield.h
# End Source File
# Begin Source File

SOURCE=.\Shock.cpp
# End Source File
# Begin Source File

SOURCE=.\Shock.h
# End Source File
# Begin Source File

SOURCE=.\Sparcle.cpp
# End Source File
# Begin Source File

SOURCE=.\Sparcle.h
# End Source File
# Begin Source File

SOURCE=.\Sun.cpp
# End Source File
# Begin Source File

SOURCE=.\Sun.h
# End Source File
# Begin Source File

SOURCE=.\TextView.cpp
# End Source File
# Begin Source File

SOURCE=.\TextView.h
# End Source File
# Begin Source File

SOURCE=.\Win32_Specific.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32_specific_conflict.cpp
# End Source File
# End Target
# End Project
