@echo off

echo RESULTS FOR "static"
echo:
findstr -s -n -i -l "static" *.c *.h
echo:

echo RESULTS FOR "global"
echo:
findstr -s -n -i -l "global" *.c *.h
echo:

echo RESULTS FOR "constant"
echo:
findstr -s -n -i -l "constant" *.c *.h
echo:
