@echo off

REM call ..\bin\buildsuper_x64-win.bat .\src\4coder_custom_entry.cpp release
call ..\bin\buildsuper_x64-win.bat .\src\4coder_custom_entry.cpp

copy .\custom_4coder.dll ..\..\custom_4coder.dll
copy .\custom_4coder.pdb ..\..\custom_4coder.pdb