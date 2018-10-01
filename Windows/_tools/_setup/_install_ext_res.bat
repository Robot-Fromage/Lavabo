:::::::::::::::
:: _INSTALL_EXT_RES.BAT
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
:: Check if Extlibs are installed properly since we are going to install them in the project directories
chgcolor %CTEXT%
ECHO Checking install setup before proceeding
CALL "%SPARK_BUILD_WIN_DIR%\check_install.bat" || goto :error

:::::::::::::::
:: Copy Ext res files
XCOPY /e /h /y "%SPARK_ROOT%\_install\resources" "%LAVABO_RESOURCES_DIR%"

GOTO :success

:::::::::::::::
:: Dir processing
:checkMakeDir
IF NOT EXIST "%~1\" ( MKDIR "%~1" )
goto:EOF
:: Return

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

