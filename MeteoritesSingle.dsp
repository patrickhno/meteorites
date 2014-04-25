# Microsoft Developer Studio Project File - Name="MeteoritesSingle" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MeteoritesSingle - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MeteoritesSingle.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MeteoritesSingle.mak" CFG="MeteoritesSingle - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MeteoritesSingle - Win32 Release" (based on\
 "Win32 (x86) Application")
!MESSAGE "MeteoritesSingle - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MeteoritesSingle - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Meteorit"
# PROP BASE Intermediate_Dir "Meteorit"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Meteorit"
# PROP Intermediate_Dir "Meteorit"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 libsrlmt.lib libdxxmt.lib Qmixer95.lib zlib.lib pnglib.lib wsock32.lib glide2x.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /profile /debug /machine:I386 /nodefaultlib:"libcd.lib" /out:"c:\games\game\Meteorites\MeteoritesSingle.exe"

!ELSEIF  "$(CFG)" == "MeteoritesSingle - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Meteori0"
# PROP BASE Intermediate_Dir "Meteori0"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Meteori0"
# PROP Intermediate_Dir "Meteori0"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /G6 /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_NTSDK" /D MAX_PLAYERS=24 /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libsrlmt.lib libdxxmt.lib Qmixer95.lib zlib.lib pnglib.lib wsock32.lib glide2x.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "MeteoritesSingle - Win32 Release"
# Name "MeteoritesSingle - Win32 Debug"
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

SOURCE=.\Meteorites.h
# End Source File
# Begin Source File

SOURCE=.\MeteoritesSingle.cpp
# End Source File
# Begin Source File

SOURCE=.\Nebula.cpp
# End Source File
# Begin Source File

SOURCE=.\Number.cpp
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

SOURCE=..\ScoreViews.cpp
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

SOURCE=.\TextView.cpp
# End Source File
# End Target
# End Project
