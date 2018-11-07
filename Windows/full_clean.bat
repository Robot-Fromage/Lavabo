:::::::::::::::
:: FULL_CLEAN.BAT
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

CALL "%PROJECT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
call:checkRmDir "%PROJECT_WIN_DIR%\Project_Deployed"
call:checkRmDir "%PROJECT_PROJECT_DIR%\x64"
call:checkRmDir "%PROJECT_PROJECT_DIR%\.vs"
call:checkRmDir "%PROJECT_PROJECT_DIR%\GeneratedFiles"
call:checkRmDir "%PROJECT_PROJECT_DIR%\Lib"
call:checkRmDir "%PROJECT_PROJECT_DIR%\resources"

DEL "%PROJECT_PROJECT_DIR%\Project.vcxproj.user"
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

