@echo off

set editor_loc=..\4coder

set dest=.\one_time
if not exist %dest% ( mkdir %dest% )

call %editor_loc%\custom\bin\build_one_time.bat .\src\4coder_custom_jai_lexer_gen.cpp %dest%
.\one_time\one_time.exe
copy %editor_loc%\custom\generated\lexer_jai.h    .\src\generated\4coder_custom_lexer_jai.h
copy %editor_loc%\custom\generated\lexer_jai.cpp  .\src\generated\4coder_custom_lexer_jai.cpp



call %editor_loc%\custom\bin\build_one_time.bat .\src\4coder_custom_odin_lexer_gen.cpp %dest%
.\one_time\one_time.exe
copy %editor_loc%\custom\generated\lexer_odin.h   .\src\generated\4coder_custom_lexer_odin.h
copy %editor_loc%\custom\generated\lexer_odin.cpp .\src\generated\4coder_custom_lexer_odin.cpp

if exist %dest% ( rmdir %dest% /S /Q )
