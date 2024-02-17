cl test_2.cpp /nologo /c
lib test_2.obj /nologo /export:foo
cl /nologo test.cpp
