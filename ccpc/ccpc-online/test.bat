@REM gen
test a -o ..\1.txt && test std -o ..\2.txt
lcmp ..\input\in.txt ..\1.txt ..\2.txt
