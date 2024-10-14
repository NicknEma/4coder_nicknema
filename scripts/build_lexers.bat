@echo off


REM ------------------------------
REM NOTE(ema): Builds the lexer generators, generates the lexers and places them in the correct folder
REM for later use by the custom layer.
REM Make sure the path_to.4coder file contains the correct path before calling this script.
echo Building lexers...


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
REM For each lexer generator:
REM - Build the lexer generator
REM - Run the lexer generator to generate the lexer
REM - Copy the generated lexer in the custom layer so it can be #included

set lexers_path=%folder_path%layer\languages

set lexgen_path=%folder_path%lexer_generator
if not exist %lexgen_path% mkdir %lexgen_path%



call %editor_path%\custom\bin\build_one_time.bat   %lexers_path%\4coder_custom_lexer_generator_js.cpp %lexgen_path%
%lexgen_path%\one_time.exe
copy %editor_path%\custom\generated\lexer_js.h     %lexers_path%\4coder_custom_lexer_js.h
copy %editor_path%\custom\generated\lexer_js.cpp   %lexers_path%\4coder_custom_lexer_js.cpp



call %editor_path%\custom\bin\build_one_time.bat   %lexers_path%\4coder_custom_lexer_generator_jai.cpp %lexgen_path%
%lexgen_path%\one_time.exe
copy %editor_path%\custom\generated\lexer_jai.h    %lexers_path%\4coder_custom_lexer_jai.h
copy %editor_path%\custom\generated\lexer_jai.cpp  %lexers_path%\4coder_custom_lexer_jai.cpp



call %editor_path%\custom\bin\build_one_time.bat   %lexers_path%\4coder_custom_lexer_generator_odin.cpp %lexgen_path%
%lexgen_path%\one_time.exe
copy %editor_path%\custom\generated\lexer_odin.h   %lexers_path%\4coder_custom_lexer_odin.h
copy %editor_path%\custom\generated\lexer_odin.cpp %lexers_path%\4coder_custom_lexer_odin.cpp


REM ------------------------------
REM Cleanup after the storm
REM TODO(ema): Figure out how to delete directories that have files in them.
REM if exist %lexgen_path% del %lexgen_path% /S /Q
goto END

:INCORRECT_LOCATION
echo %editor_path% does not contain 4ed.exe. Please fix the path in path_to.4coder.

:END
cd %caller_path%
