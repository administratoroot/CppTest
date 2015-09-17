@echo off
color a
setlocal  enabledelayedexpansion
set localpath="C:\tmp"
for /f "tokens=* delims= " %%i in ('reg query "hkcu\software\winrar sfx"^|findstr /i /c:"D:\Program Files\WinRAR"') do (
    set str=%%i
    set str1=!str:~-23!
)
set RarPath="%str1%\winrar.exe"
%RarPath% x %localpath%\GGP5.0_forTest.zip Win32\*.pdb %localpath%
del %localpath%\*.zip /f /s /q /a

xcopy %localpath%\Win32\*.pdb F:\GTJ2015\GCL\bin /e /i /y /f
xcopy %localpath%\Win32\*.pdb F:\GCL2015\GCL\bin /e /i /y /f

rd /s /q %localpath%\Win32