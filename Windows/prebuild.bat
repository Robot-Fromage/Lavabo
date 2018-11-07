:::::::::::::::
:: PREBUILD.BAT
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

CALL _smart_cp "%PROJECT_ROOT%\resources" "%PROJECT_PROJECT_DIR%\resources"

:::::::::::::::
:: Reaching End of the Script
GOTO :success

:::::::::::::::
:error
chgcolor %CERROR%
ECHO %0: ERROR
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

