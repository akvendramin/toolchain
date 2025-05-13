@echo off

:: save the parent directory
cd %~dp0
pushd %cd%
cd ..
set project_directory=%cd%
popd

:: delete and recreate the build directory
rmdir "%project_directory%\build"
mkdir "%project_directory%\build"

:: compiler and linker flags for MSVC
set common_compiler_flags=/MTd /nologo /Od /W4 /Z7 /wd4100 /wd4101 /wd4189 /wd4201 /I"%project_directory%\source"
set common_linker_flags=/DEBUG:FASTLINK /INCREMENTAL:NO /OPT:REF

:: set cwd to "build" and compile "main.c"
pushd "%project_directory%\build"
cls
if %errorlevel% == 0 (cl %common_compiler_flags% "%project_directory%\source\test\main.c" /link %common_linker_flags%)
popd