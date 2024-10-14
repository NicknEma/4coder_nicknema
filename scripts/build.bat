@echo off


REM ------------------------------
REM NOTE(ema): Invokes the actual build script in the editor's directory.
REM Make sure the path_to.4coder file contains the correct path before calling this script.
echo Building custom layer...


REM ------------------------------
REM IMPORTANT NOTE(ema): Needs to happen before everything else or the caller will me moved to
REM another directory, which is annoying.
setlocal enabledelayedexpansion


REM ------------------------------
REM Setup paths
set caller_path=%cd%\
set script_path=%~dp0
cd %script_path%\..
set folder_path=%cd%\


REM ------------------------------
REM Retrieve editor location
set count=0
for /f "tokens=*" %%x in (%folder_path%path_to.4coder) do (
														   set /a count+=1
														   set var[!count!]=%%x
														   )
set editor_path=%var[1]%

if     exist %editor_path%\4ed.exe echo Found %editor_path%\4ed.exe
if not exist %editor_path%\4ed.exe goto INCORRECT_LOCATION


REM ------------------------------
REM Invoke buildsuper
if "%1"=="release" set mode=release else set mode=debug

REM This is buildsuper's default binary name. This parameter is not passed correctly for some reason.
REM TODO(ema): Figure out why and allow this variable to be anything we want.
set binary_name="custom_4coder"
call %editor_path%\custom\bin\buildsuper_x64-win.bat %folder_path%layer\4coder_custom_entry.cpp %mode% %binary_name%


REM ------------------------------
REM Cleanup after the storm
if not exist %folder_path%%binary_name%.dll goto BINARY_NOT_FOUND
copy %folder_path%%binary_name%.dll %editor_path%\%binary_name%.dll
copy %folder_path%%binary_name%.pdb %editor_path%\%binary_name%.pdb
del  %folder_path%%binary_name%.*
del  %folder_path%*.pdb
goto END

:INCORRECT_LOCATION
echo %editor_path% does not contain 4ed.exe. Please fix the path in path_to.4coder.
goto END

:BINARY_NOT_FOUND
echo Could not find the generated binary. Maybe the build failed or it has a different name than %binary_name%.

:END
cd %caller_path%
