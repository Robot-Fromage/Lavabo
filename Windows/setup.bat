:::::::::::::::
:: SETUP.BAT
:::::::::::::::
:: INIT SHELL
@ECHO OFF
CALL "%~dp0_tools\_initprojectshell.bat"
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
PUSHD "%CD%"
:::::::::::::::
:: INIT ENV
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:: INFO
chgcolor %CTEXT%
TYPE "%~dp0README.txt"

:: BUILD AND INSTALL
CALL "%FUEL_BUILD_WIN_DIR%\buildall.bat" "%PROJECT_BUILD_CONFIG%" || goto :error
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_project.bat" || goto :error
CALL "%PROJECT_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error

:: END SCRIPT
GOTO :success

:::::::::::::::
:: ERROR
:error
POPD
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 1

:::::::::::::::
:: SUCCESS
:success
POPD
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 0
