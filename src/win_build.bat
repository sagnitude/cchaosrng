@echo off
@set cmake_install_prefix="%PROGRAMFILES%"
@if exist C:\MinGW\bin\mingw32-make.exe set cmake_make_program="C:\MinGW\bin\mingw32-make.exe"
@if exist D:\MinGW\bin\mingw32-make.exe set cmake_make_program="D:\MinGW\bin\mingw32-make.exe"
@if exist E:\MinGW\bin\mingw32-make.exe set cmake_make_program="E:\MinGW\bin\mingw32-make.exe"
@set paths=%PATH%
:STR_R
@for /f "tokens=1,* delims=;" %%a in ("%paths%") do (
  set temp="%%a"
  set paths=%%b
  if not exist "%%a\cmake.exe" goto :STR_R
  set cmakeexe=%%a\cmake.exe
)
@cd ..\bin
@if exist CMakeCache.txt del CMakeCache.txtf >nul 2>nul
@rmdir CMakeFiles /S /Q
@if exist cmake_install.cmake del cmake_install.cmake >nul 2>nul
@if exist Makefile del Makefile >nul 2>nul
@if exist x.exe del x.exe >nul 2>nul
@if exist ..\src\x.exe del ..\src\x.exe >nul 2>nul
@start "" /B /WAIT "%cmakeexe%" %cd%\..\src -DCMAKE_MAKE_PROGRAM:FILEPATH=%cmake_make_program% -G "MinGW Makefiles"
@start /B /WAIT make
@echo off
@if exist ..\bin\x.exe mklink ..\src\x.exe ..\bin\x.exe
@cd ..\src
@pause