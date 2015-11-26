@echo off
color a
setlocal  enabledelayedexpansion
set localpath="C:\tmp"
set RarPath="D:\Program Files\WinRAR\winrar.exe"
%RarPath% x %localpath%\GGP*.zip Win32\*.pdb %localpath%
del %localpath%\*.zip /f /s /q /a

xcopy %localpath%\Win32\*.pdb F:\GTJ2017\GTJ\bin /e /i /y /f

rd /s /q %localpath%\Win32