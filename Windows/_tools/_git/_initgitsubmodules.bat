:::::::::::::::
:: _INITGITSUBMODULES.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Init Shell
CALL "%~dp0../_initprojectshell.bat"
:::::::::::::::
:: HEADER
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::
:: Init Lavabo Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Backup
PUSHD "%CD%"

:::::::::::::::
:: Checking changes & warning before issuing git operation
CALL "%LAVABO_WIN_TOOLS_GIT_DIR%\_checkgitstatus.bat" || goto :error

:::::::::::::::
:: CD To Lavabo Repository Root
CD %LAVABO_ROOT%

:::::::::::::::
:: Running Submodules init & update recursively, output enabled
chgcolor %CGIT%
@ECHO ON
git submodule update --init --recursive
@ECHO OFF

GOTO :success

:::::::::::::::
:error
POPD
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
EXIT /B 1

:::::::::::::::
:success
POPD
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
EXIT /B 0

