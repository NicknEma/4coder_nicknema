@echo off

call ..\custom\bin\buildsuper_x64-win.bat .\4coder_nicknema_main.cpp %*

move custom_4coder.dll ..
move custom_4coder.pdb ..