:::::::::::::::
:: _CLEAN_RES_CHECK.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Fast Init
CALL "%~dp0..\_initprojectshell.bat"
:::::::::::::::
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::
:: Init Project Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

IF EXIST "%~dp0reschecksum.txt" (
DEL "%~dp0reschecksum.txt"
)

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

