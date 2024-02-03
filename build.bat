@echo off

set editor_loc=..\4coder

REM call %editor_loc%\custom\bin\buildsuper_x64-win.bat .\src\4coder_custom_entry.cpp release
call %editor_loc%\custom\bin\buildsuper_x64-win.bat .\src\4coder_custom_entry.cpp

copy .\custom_4coder.dll %editor_loc%\custom_4coder.dll
copy .\custom_4coder.pdb %editor_loc%\custom_4coder.pdb

del custom_4coder.* > NUL 2> NUL

copy bindings.4coder %editor_loc%\bindings.4coder
copy config.4coder %editor_loc%\config.4coder
