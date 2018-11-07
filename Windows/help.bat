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
:: SHUT ASK
SET SILENT_ASK=1

:::::::::::::::
:: Display README & Ask User Before Continue
chgcolor %CTEXT%
TYPE "%~dp0README.txt"

ECHO deploy.bat             ... Build and Deploy application
ECHO fix_install.bat        ... Copy ext dependancies in solution dirs
ECHO full_clean.bat         ... Clean deploy, dependancies and VisualStudio files
ECHO help.bat               ... Display help
ECHO prebuild.bat           ... Copy resources in Core if needed before build
ECHO quick_clean.bat        ... Clean deploy and VisualStudio files but keeps dependancies
ECHO README.txt             ... Display info
ECHO setup.bat              ... Full setup of Project environment
ECHO updatex.bat            ... Update a specific FUEL Extlib ( prompted ) and reinstall
ECHO _tools                 ... Batch framework tools

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

