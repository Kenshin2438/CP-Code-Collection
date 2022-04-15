@echo off

:loop
	gen.exe > _.in
	ac.exe < _.in > _.out
	bf.exe < _.in > _.ans
	fc _.out _.ans
if not errorlevel 1 goto loop
pause
goto loop
