:::::::::::::::
:: QUICK_CLEAN.BAT
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
:: Init Lavabo Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

CALL "%LAVABO_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
call:checkRmDir "%LAVABO_WIN_DIR%\Lavabo_Deployed"
call:checkRmDir "%LAVABO_PROJECT_DIR%\.vs"
call:checkRmDir "%LAVABO_PROJECT_DIR%\GeneratedFiles"
call:checkRmDir "%LAVABO_PROJECT_DIR%\resources"

GOTO :success

:::::::::::::::
:: Dir processing
:checkRmDir
:Repeat
RMDIR /s /q "%~1\"
IF EXIST "%~1\" goto :Repeat
chgcolor %CTEXT%
ECHO "%~1\" was cleaned
goto:EOF
:: Return

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

