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

:: Init Lavabo Env Paths
:: Lavabo Paths
chgcolor %CLAVABO%
::  | Pseudo Funk     | Var Name                    | Relative Path
call:makeAbsolutePath LAVABO_ROOT                   "%~dp0..\..\"
call:makeAbsolutePath LAVABO_WIN_DIR                "%LAVABO_ROOT%\Windows"
call:makeAbsolutePath LAVABO_WIN_TOOLS_DIR          "%LAVABO_ROOT%\Windows\_tools"
call:makeAbsolutePath LAVABO_WIN_TOOLS_SETUP_DIR    "%LAVABO_ROOT%\Windows\_tools\_setup"
call:makeAbsolutePath LAVABO_WIN_TOOLS_GIT_DIR      "%LAVABO_ROOT%\Windows\_tools\_git"
call:makeAbsolutePath LAVABO_WIN_TOOLS_QT_DIR       "%LAVABO_ROOT%\Windows\_tools\_qt"
call:makeAbsolutePath LAVABO_WIN_TOOLS_MSVC_DIR     "%LAVABO_ROOT%\Windows\_tools\_msvc"
call:makeAbsolutePath LAVABO_WIN_TOOLS_PREBUILD_DIR "%LAVABO_ROOT%\Windows\_tools\_prebuild"
call:makeAbsolutePath LAVABO_SRC_DIR                "%LAVABO_ROOT%\src"
call:makeAbsolutePath LAVABO_RESOURCES_DIR          "%LAVABO_ROOT%\resources"

call:makeAbsolutePath LAVABO_PROJECT_DIR            "%LAVABO_ROOT%\Windows\Lavabo"

:: Extlib Paths
chgcolor %CSPARK%
call:makeAbsolutePath SPARK_ROOT                    "%LAVABO_ROOT%\Spark\"
call:makeAbsolutePath SPARK_BUILD_DIR               "%SPARK_ROOT%\_build"
call:makeAbsolutePath SPARK_BUILD_WIN_DIR           "%SPARK_ROOT%\_build\Windows"
call:makeAbsolutePath SPARK_BUILD_WIN_TOOLS_DIR     "%SPARK_ROOT%\_build\Windows\_tools"

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

