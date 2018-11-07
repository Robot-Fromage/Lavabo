:::::::::::::::
:: FIX_INSTALL.BAT
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
:: Install Project Extlibs Libraries
chgcolor %CTEXT%
ECHO Installing Extlibs
CALL "%PROJECT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
SETLOCAL
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_project.bat" || goto :error
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error
ENDLOCAL

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

