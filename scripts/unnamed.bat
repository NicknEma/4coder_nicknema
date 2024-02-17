@echo off

REM @Todo(ema): Give a short but meaningful name to this file.

REM @Note(ema): Copies bindings, config and themes in the editor's directory. Make sure the path_to.4coder
REM file contains the correct path before calling this script.

REM Retrieve the root directory for the custom layer.
set invoke_dir=%cd%
set me=%~dp0
cd %me%
cd ..
set root=%cd%\
cd %invoke_dir%

REM Retrieve the 4ed.exe directory from the path_to.4coder file.
setlocal enabledelayedexpansion
set count=0
for /f "tokens=*" %%x in (%root%path_to.4coder) do (
													set /a count+=1
													set var[!count!]=%%x
													)
set editor_dir=%var[1]%
REM echo %editor_dir%

if not exist %editor_dir%/4ed.exe goto INCORRECT_LOCATION

copy %root%variables\bindings.4coder %editor_dir%\bindings.4coder > NUL
copy %root%variables\config.4coder   %editor_dir%\config.4coder   > NUL
copy %root%variables\themes          %editor_dir%\themes\         > NUL
goto END

:INCORRECT_LOCATION
echo %editor_dir% does not contain 4ed.exe. Please fix the path in path_to.4coder.

:END
