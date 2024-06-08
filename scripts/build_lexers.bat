@echo off

set editor_loc=C:\dev\4coder

set dest=.\one_time
if not exist %dest% ( mkdir %dest% )

call %editor_loc%\custom\bin\build_one_time.bat .\layer\languages\4coder_custom_lexer_generator_js.cpp %dest%
%dest%\one_time.exe
copy %editor_loc%\custom\generated\lexer_js.h    .\layer\generated\4coder_custom_lexer_js.h
copy %editor_loc%\custom\generated\lexer_js.cpp  .\layer\generated\4coder_custom_lexer_js.cpp



call %editor_loc%\custom\bin\build_one_time.bat .\layer\languages\4coder_custom_lexer_generator_jai.cpp %dest%
%dest%\one_time.exe
copy %editor_loc%\custom\generated\lexer_jai.h    .\layer\generated\4coder_custom_lexer_jai.h
copy %editor_loc%\custom\generated\lexer_jai.cpp  .\layer\generated\4coder_custom_lexer_jai.cpp



call %editor_loc%\custom\bin\build_one_time.bat .\layer\languages\4coder_custom_lexer_generator_odin.cpp %dest%
%dest%\one_time.exe
copy %editor_loc%\custom\generated\lexer_odin.h   .\layer\generated\4coder_custom_lexer_odin.h
copy %editor_loc%\custom\generated\lexer_odin.cpp .\layer\generated\4coder_custom_lexer_odin.cpp

REM if exist %dest% ( del %dest% /S /Q )
