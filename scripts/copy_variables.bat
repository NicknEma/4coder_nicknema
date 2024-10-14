@echo off


REM ------------------------------
REM @Note(ema): Copies bindings, config and themes in the editor's directory. Make sure the path_to.4coder
REM file contains the correct path before calling this script.
echo Copying bindings, config and themes...


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
REM cd %folder_path%


REM ------------------------------
REM Retrieve editor location
set count=0
for /f "tokens=*" %%x in (%root%path_to.4coder) do (
													set /a count+=1
													set var[!count!]=%%x
													)
set editor_dir=%var[1]%

if     exist %editor_path%\4ed.exe echo Found %editor_path%\4ed.exe
if not exist %editor_path%\4ed.exe goto INCORRECT_LOCATION


REM ------------------------------
REM Copy files
copy %root%variables\bindings.4coder %editor_dir%\bindings.4coder > NUL
copy %root%variables\config.4coder   %editor_dir%\config.4coder   > NUL
copy %root%variables\themes          %editor_dir%\themes\         > NUL
goto END

:INCORRECT_LOCATION
echo %editor_dir% does not contain 4ed.exe. Please fix the path in path_to.4coder.

:END
cd %caller_path%
