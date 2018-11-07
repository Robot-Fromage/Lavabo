:::::::::::::::
:: INITPROJECTENV.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: GUARD
IF DEFINED _INIT_PROJECT_ENV_HH goto :EOF
:::::::::::::::
:: Fast Init
CALL "%~dp0_initprojectshell.bat"
:::::::::::::::
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::

:::::::::::::::
:: Prefix
SET CHECK_PATH_PREFIX==

:: Check Windows Ver
for /f "tokens=4-5 delims=. " %%i in ('ver') do set WINDOWS_VERSION=%%i.%%j
if "%WINDOWS_VERSION%" == "10.0" SET "WINDOWS_VERSION=10"
if "%WINDOWS_VERSION%" == "6.3" SET "WINDOWS_VERSION=8.1"
if "%WINDOWS_VERSION%" == "6.2" SET "WINDOWS_VERSION=8"
if "%WINDOWS_VERSION%" == "6.1" SET "WINDOWS_VERSION=7"
if "%WINDOWS_VERSION%" == "6.0" SET "WINDOWS_VERSION=Vista"
chgcolor %CRESET%
ECHO [WINDOWS_VERSION] = "%WINDOWS_VERSION%"

:: Init Project Env Paths
:: Project Paths
chgcolor %CPROJECT%
::  | Pseudo Funk     | Var Name                    | Relative Path
call:makeAbsolutePath PROJECT_ROOT                   "%~dp0..\..\"
call:makeAbsolutePath PROJECT_WIN_DIR                "%PROJECT_ROOT%\Windows"
call:makeAbsolutePath PROJECT_WIN_TOOLS_DIR          "%PROJECT_ROOT%\Windows\_tools"
call:makeAbsolutePath PROJECT_WIN_TOOLS_SETUP_DIR    "%PROJECT_ROOT%\Windows\_tools\_setup"
call:makeAbsolutePath PROJECT_WIN_TOOLS_GIT_DIR      "%PROJECT_ROOT%\Windows\_tools\_git"
call:makeAbsolutePath PROJECT_WIN_TOOLS_QT_DIR       "%PROJECT_ROOT%\Windows\_tools\_qt"
call:makeAbsolutePath PROJECT_WIN_TOOLS_MSVC_DIR     "%PROJECT_ROOT%\Windows\_tools\_msvc"
call:makeAbsolutePath PROJECT_WIN_TOOLS_PREBUILD_DIR "%PROJECT_ROOT%\Windows\_tools\_prebuild"
call:makeAbsolutePath PROJECT_SRC_DIR                "%PROJECT_ROOT%\src"
call:makeAbsolutePath PROJECT_RESOURCES_DIR          "%PROJECT_ROOT%\resources"
call:makeAbsolutePath PROJECT_PROJECT_DIR            "%PROJECT_ROOT%\Windows\Lavabo"

SET BUILDCONFIG_FILE="%PROJECT_ROOT%\Windows\buildconfig.ini"

:::::::::::::::
:: INIT FUEL
IF NOT EXIST "%PROJECT_ROOT%\fuel\.git" (
    SETLOCAL
    CD "%PROJECT_ROOT%"
    chgcolor %CGIT%
    @ECHO ON
    git submodule update --init fuel
    @ECHO OFF
    ENDLOCAL
)
:::::::::::::::

:: Extlib Paths
chgcolor %CFUEL%
call:makeAbsolutePath FUEL_ROOT                    "%PROJECT_ROOT%\FUEL\"
call:makeAbsolutePath FUEL_BUILD_DIR               "%FUEL_ROOT%\_build"
call:makeAbsolutePath FUEL_BUILD_WIN_DIR           "%FUEL_ROOT%\_build\Windows"
call:makeAbsolutePath FUEL_BUILD_WIN_TOOLS_DIR     "%FUEL_ROOT%\_build\Windows\_tools"

:::::::::::::::
:: Init MSVC Env Paths
SET "MSVC_INSTALL_DIR="
for /f "usebackq delims=" %%i in (`vswhere -latest -version "[15.0,16.0)" -requires Microsoft.Component.MSBuild -property installationPath`) do (
  set MSVC_INSTALL_DIR=%%i
)

:: Checking MSVC Path
chgcolor %CMSVC%
IF "%MSVC_INSTALL_DIR%"=="" ( GOTO :error )
IF NOT EXIST "%MSVC_INSTALL_DIR%\" ( GOTO :error )
ECHO [MSVC_INSTALL_DIR] %CHECK_PATH_PREFIX% %MSVC_INSTALL_DIR%

SET "MSVC_VCVARS_DIR=%MSVC_INSTALL_DIR%\VC\Auxiliary\Build"
IF NOT EXIST "%MSVC_VCVARS_DIR%\" ( GOTO :error )
ECHO [MSVC_VCVARS_DIR] %CHECK_PATH_PREFIX% %MSVC_VCVARS_DIR%

:::::::::::::::
:: Read Qt Paths
CALL "%~dp0_qt\_init_qtpath.bat" || goto :error
IF NOT EXIST "%~dp0_qt\qtpath.txt" ( GOTO :error )
set "QTDIR="
for /f "delims=" %%a in ('type "%~dp0_qt\qtpath.txt"') do (
SET QTDIR=%%a
GOTO :break
)
)
:break
SET BREAK_PLACEHOLDER_STATEMENT=
REM TRIM EXTRA QUOTES
set QTDIR=%QTDIR:"=%

:: Checking Qt Paths
chgcolor %CQT%
dir "%QTDIR%" > nul || goto :error
ECHO [QTDIR] %CHECK_PATH_PREFIX% %QTDIR%

set "QT_BIN_DIR=%QTDIR%\bin"
dir "%QT_BIN_DIR%" > nul || goto :error
ECHO [QT_BIN_DIR] %CHECK_PATH_PREFIX% %QT_BIN_DIR%

set "QT_MOC_EXE=%QT_BIN_DIR%\moc.exe"
dir "%QT_MOC_EXE%" > nul || goto :error
ECHO [QT_MOC_EXE] %CHECK_PATH_PREFIX% %QT_MOC_EXE%

set "QT_QMAKE_EXE=%QT_BIN_DIR%\qmake.exe"
dir "%QT_QMAKE_EXE%" > nul || goto :error
ECHO [QT_QMAKE_EXE] %CHECK_PATH_PREFIX% %QT_QMAKE_EXE%

:: Append QtBinDir to PATH
ECHO [QT_BIN_DIR] has been added to the PATH.
SET "PATH=%PATH%;%QT_BIN_DIR%;"

:: PARSE BUILD CONFIG
SET "PROJECT_BUILD_CONFIG="
SETLOCAL EnableDelayedExpansion
SET "LOCAL_BUILD_CONFIG="
IF EXIST "%BUILDCONFIG_FILE%" (
	FOR /F "delims=" %%A IN ( 'TYPE "%BUILDCONFIG_FILE%"' ) DO (
		IF "!LOCAL_BUILD_CONFIG!" NEQ "" SET "LOCAL_BUILD_CONFIG=!LOCAL_BUILD_CONFIG!;"
		SET "LOCAL_BUILD_CONFIG=!LOCAL_BUILD_CONFIG!%%A"
	)
)
(
	ENDLOCAL
	SET PROJECT_BUILD_CONFIG=%LOCAL_BUILD_CONFIG%
)

:: DEF GUARD
SET _INIT_PROJECT_ENV_HH=1

GOTO :success

:::::::::::::::
:: Path Processing
:makeAbsolutePath
PUSHD "%CD%"
IF NOT EXIST "%~2\" ( GOTO :error )
CD "%~2"
SET "%~1=%CD%"
ECHO [%~1] %CHECK_PATH_PREFIX% "%CD%"
POPD
goto:EOF
:: Return

:::::::::::::::
:error
chgcolor %CERROR%
ECHO %0: ERROR
ECHO %0: There was an error while checking the value of some environment paths
ECHO //////////
chgcolor %CRESET%
EXIT /B 1

:::::::::::::::
:success
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
EXIT /B 0

