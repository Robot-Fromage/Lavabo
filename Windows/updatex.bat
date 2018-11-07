:::::::::::::::
:: UPDATEX.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Init Shell
CALL "%~dp0_tools\_initprojectshell.bat"
:::::::::::::::
:: HEADER
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::
:: Init Project Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: PARSE BUILD CONFIG
SET "OUT_BUILD_CONFIG="
setlocal EnableDelayedExpansion
SET "LOCAL_BUILD_CONFIG="
IF EXIST "%~dp0buildconfig.ini" (
	FOR /f "delims=" %%A IN ('TYPE "%~dp0buildconfig.ini"') DO (
	IF "!LOCAL_BUILD_CONFIG!" neq "" SET "LOCAL_BUILD_CONFIG=!LOCAL_BUILD_CONFIG!;"
	SET "LOCAL_BUILD_CONFIG=!LOCAL_BUILD_CONFIG!%%A"
	)
)
(
	endlocal
	SET OUT_BUILD_CONFIG=%LOCAL_BUILD_CONFIG%
)

:::::::::::::::
:: Display Info
chgcolor %CTEXT%
ECHO Update specific libs from FUEL extlibs and fast reinstall.
ECHO You can pass multiple values separated with ';'
ECHO Possible values:
CALL "%FUEL_BUILD_WIN_DIR%\list.bat" || goto :error
ECHO Although build config is:
ECHO %OUT_BUILD_CONFIG%
ECHO An empty input just does reinstall.

:::::::::::::::
:: Ask User
chgcolor %CRESET%
set /p SENDCOMMAND=":"

:::::::::::::::
:: Build
CALL "%FUEL_BUILD_WIN_DIR%\buildall.bat" "%SENDCOMMAND%" || goto :error

:::::::::::::::
:: Install
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_project.bat" || goto :error
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error

:::::::::::::::
:: Reaching End of the Script
GOTO :success

:::::::::::::::
:error
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 1

:::::::::::::::
:success
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 0

