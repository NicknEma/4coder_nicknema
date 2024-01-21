@echo off

echo RESULTS FOR "Todo"
echo:
findstr -s -n -i -l "@Todo" *.c *.h
echo:

echo RESULTS FOR "Cleanup"
echo:
findstr -s -n -i -l "@Cleanup" *.c *.h
echo:

echo RESULTS FOR "Temporary"
echo:
findstr -s -n -i -l "@Temporary" *.c *.h
echo:

echo RESULTS FOR "Speed"
echo:
findstr -s -n -i -l "@Speed" *.c *.h
echo:

echo RESULTS FOR "Incomplete"
echo:
findstr -s -n -i -l "@Incomplete" *.c *.h
echo:

echo RESULTS FOR "Hardcoded"
echo:
findstr -s -n -i -l "@Hardcoded" *.c *.h
echo:

echo RESULTS FOR "Hack"
echo:
findstr -s -n -i -l "@Hack" *.c *.h
echo:

echo RESULTS FOR "Rename"
echo:
findstr -s -n -i -l "@Rename" *.c *.h
echo:

echo RESULTS FOR "Note"
echo:
findstr -s -n -i -l "@Note" *.c *.h
echo:
