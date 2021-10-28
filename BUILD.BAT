@echo off

set RGBDS_PATH=.\rgbds

set ROOT_PATH=.
set ASM=%RGBDS_PATH%\rgbasm
set LNK=%RGBDS_PATH%\rgblink
set FIX=%RGBDS_PATH%\rgbfix

set PROJECT_PATH=.
set PROJECT_INCLUDES=%PROJECT_PATH%\include\
set PROJECT_SRC=%PROJECT_PATH%\src\

set OUTPUT_PATH=%PROJECT_PATH%\build
set OUTPUT_NAME=%OUTPUT_PATH%\metallurgical-nightshades

set ASM_FLAGS=-i%PROJECT_INCLUDES%
set LNK_FLAGS=-m %OUTPUT_NAME%.map -n %OUTPUT_NAME%.sym -o %OUTPUT_NAME%.gb

if not exist "%RGBDS_PATH%" (
    echo ** Failed to build **
    echo RGBDS tools not found!
    exit /b -1
)

if not exist "%OUTPUT_PATH%" mkdir %OUTPUT_PATH%

del "%OUTPUT_PATH%"\*.o /s /f /q
del "%OUTPUT_PATH%"\*.map /s /f /q
del "%OUTPUT_PATH%"\*.sym /s /f /q

echo Assembling...

for %%I in (%PROJECT_SRC%\*.s) do (
    echo - %%~I
    %ASM% %ASM_FLAGS% -o %OUTPUT_PATH%\%%~nI.o %%~I
)
echo.
echo Linking...
setlocal EnableDelayedExpansion
set OBJFILES=
for %%I in (%OUTPUT_PATH%\*.o) do (
    set OBJFILES=!OBJFILES! %OUTPUT_PATH%\%%~nI.o
)

%LNK% %LNK_FLAGS% %OBJFILES%
echo.
echo Checksum Fix...

%FIX% -p0 -v %OUTPUT_NAME%.gb

echo - %OUTPUT_NAME%.gb created!