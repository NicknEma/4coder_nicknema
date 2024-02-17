REM @echo off

call ..\custom\bin\build_one_time.bat .\languages\4coder_nicknema_odin_lexer_gen.cpp .\
.\one_time.exe
mkdir generated 2> NUL
copy ..\custom\generated\lexer_odin.h   .\generated\4coder_nicknema_lexer_odin.h
copy ..\custom\generated\lexer_odin.cpp .\generated\4coder_nicknema_lexer_odin.cpp