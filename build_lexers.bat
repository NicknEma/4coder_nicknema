@echo off
echo --

set dest=.\one_time\



call ..\bin\build_one_time.bat .\src\4coder_custom_jai_lexer_gen.cpp  %dest%
.\one_time\one_time.exe
copy ..\generated\lexer_jai.h    .\src\generated\4coder_lexer_jai.h
copy ..\generated\lexer_jai.cpp  .\src\generated\4coder_lexer_jai.cpp



call ..\bin\build_one_time.bat .\src\4coder_custom_odin_lexer_gen.cpp %dest%
.\one_time\one_time.exe
copy ..\generated\lexer_odin.h   .\src\generated\4coder_lexer_odin.h
copy ..\generated\lexer_odin.cpp .\src\generated\4coder_lexer_odin.cpp