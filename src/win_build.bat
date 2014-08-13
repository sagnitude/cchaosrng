@echo off
@set cmake_install_prefix="%PROGRAMFILES%"
@if exist C:\MinGW\bin\mingw32-make.exe set cmake_make_program="C:\MinGW\bin\mingw32-make.exe"
@if exist D:\MinGW\bin\mingw32-make.exe set cmake_make_program="D:\MinGW\bin\mingw32-make.exe"
@if exist E:\MinGW\bin\mingw32-make.exe set cmake_make_program="E:\MinGW\bin\mingw32-make.exe"
@REM @set paths=%PATH%
@start /B /WAIT make
@REM echo %paths%
@REM :STR_R
@REM  echo "looping"
@REM @for /f "tokens=1,* delims=;" %%a in ("%paths%") do (
@REM   set temp="%%a"
@REM   set paths=%%b
  @REM  echo "%%a\cmake.exe"
@REM   if not exist "%%a\cmake.exe" goto :STR_R
  @REM  goto STR_R
@REM   set cmakeexe=%%a\cmake.exe
@REM )
@REM @echo "%cmakeexe%"
@cd ..\bin
@if exist CMakeCache.txt del CMakeCache.txt
@rmdir CMakeFiles /S /Q
@if exist cmake_install.cmake del cmake_install.cmake
@if exist Makefile del Makefile
@if exist x.exe del x.exe
@if exist ..\src\x.exe del ..\src\x.exe
@echo on
@start /B /WAIT cmake %cd%\..\src -DCMAKE_MAKE_PROGRAM:FILEPATH=%cmake_make_program% -G "MinGW Makefiles"
@start /B /WAIT make
@echo off
@if exist ..\bin\x.exe mklink ..\src\x.exe ..\bin\x.exe
@cd ..\src