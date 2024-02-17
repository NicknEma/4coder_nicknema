@echo off

REM @Note(ema): Invokes the actual build script in the editor's directory. Make sure the path_to.4coder
REM file contains the correct path before calling this script.

REM Retrieve the root directory for the custom layer.
set invoke_dir=%cd%
set me=%~dp0
cd %me%
cd ..
set root=%cd%\
cd %invoke_dir%

REM Retrieve the editor location from the path_to.4coder file
setlocal enabledelayedexpansion
set count=0
for /f "tokens=*" %%x in (%root%path_to.4coder) do (
													set /a count+=1
													set var[!count!]=%%x
													)
set editor_dir=%var[1]%
REM echo %editor_dir%

if not exist %editor_dir%/4ed.exe goto INCORRECT_LOCATION

REM set mode=debug
if "%1"=="release" set mode=release

REM Invoke buildsuper
set binary_name=custom_4coder
call %editor_dir%\custom\bin\buildsuper_x64-win.bat %root%layer\4coder_custom_entry.cpp %mode% %binary_name%

REM Cleanup after the storm
set me=%~dp0
if not exist %root%%binary_name%.dll goto END
copy %root%%binary_name%.dll %editor_dir%\%binary_name%.dll
copy %root%%binary_name%.pdb %editor_dir%\%binary_name%.pdb
del  %root%%binary_name%.*
del  %root%*.pdb
goto END

:INCORRECT_LOCATION
echo %editor_dir% does not contain 4ed.exe. Please fix the path in path_to.4coder.

:END
