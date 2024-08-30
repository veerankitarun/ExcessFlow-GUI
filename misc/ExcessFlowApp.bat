@echo off

:start
cd ..\rigGUI && ^
call .venv\Scripts\activate.bat && ^
call python "MainWindow.py" %*
pause
cls
goto start