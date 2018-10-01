:::::::::::::::
:: SETUP.BAT
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

:::::::::::::::
:: Init BoltExtlibs before anything
SETLOCAL
CD "%~dp0"
chgcolor %CGIT%
@ECHO ON
git submodule update --init
@ECHO OFF
ENDLOCAL

:::::::::::::::
:: Init Lavabo Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Backup
PUSHD "%CD%"

:::::::::::::::
:: SHUT ASK
SET SILENT_ASK=1

:::::::::::::::
:: Display README & Ask User Before Continue
chgcolor %CTEXT%
TYPE "%~dp0README.txt" & CALL _ask_confirm.bat || goto :error

:::::::::::::::
:: Build Lavabo Extlibs Libraries
CALL "%LAVABO_WIN_TOOLS_SETUP_DIR%\_buildextlibs.bat" || goto :error

:::::::::::::::
:: Install Lavabo Extlibs Libraries
CALL "%LAVABO_WIN_TOOLS_SETUP_DIR%\_install_project.bat" || goto :error
CALL "%LAVABO_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error

:::::::::::::::
:: Reaching End of the Script
GOTO :success

:::::::::::::::
:error
POPD
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 1

:::::::::::::::
:success
POPD
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 0

