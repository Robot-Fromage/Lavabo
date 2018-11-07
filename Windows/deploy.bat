:::::::::::::::
:: DEPLOY_EDITOR.BAT
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

:::::::::::::::
:: Check & Init
CALL "%FUEL_BUILD_WIN_DIR%\check_install.bat" || goto :error
CALL "%PROJECT_WIN_TOOLS_MSVC_DIR%\_init_msvc.bat" || goto :error
CALL "%PROJECT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
:::::::::::::::
:: Building Editor
SET "OVERRIDE_WIN_SDK=$(WindowsTargetPlatformVersion)"
IF "%WINDOWS_VERSION%" == "7" SET "OVERRIDE_WIN_SDK=10.0.16299.0"
IF "%WINDOWS_VERSION%" == "10" SET "OVERRIDE_WIN_SDK=10.0.17134.0"

MSBUILD "%PROJECT_PROJECT_DIR%\OVID.sln" /p:Configuration=Release;WindowsTargetPlatformVersion="%OVERRIDE_WIN_SDK%" || goto :error

:::::::::::::::
:: Clean & create deploy dir
:Repeat
RMDIR /s /q "%PROJECT_WIN_DIR%\Project_Deployed\"
IF EXIST "%PROJECT_WIN_DIR%\Project_Deployed\" goto :Repeat
chgcolor %CTEXT%
ECHO old deployment was cleaned
MKDIR "%PROJECT_WIN_DIR%\Project_Deployed\"
ECHO "%PROJECT_WIN_DIR%\Project_Deployed\"

:::::::::::::::
:: Copy Files
COPY "%PROJECT_PROJECT_DIR%\x64\Release\OVID.exe" "%PROJECT_WIN_DIR%\Project_Deployed\OVID.exe"
COPY "%PROJECT_PROJECT_DIR%\x64\Release\openal32.dll" "%PROJECT_WIN_DIR%\Project_Deployed\openal32.dll"
COPY "%QT_BIN_DIR%\Qt5Core.dll" "%PROJECT_WIN_DIR%\Project_Deployed\Qt5Core.dll"
COPY "%QT_BIN_DIR%\Qt5Gui.dll" "%PROJECT_WIN_DIR%\Project_Deployed\Qt5Gui.dll"
COPY "%QT_BIN_DIR%\Qt5Widgets.dll" "%PROJECT_WIN_DIR%\Project_Deployed\Qt5Widgets.dll"
COPY "%QT_BIN_DIR%\Qt5WinExtras.dll" "%PROJECT_WIN_DIR%\Project_Deployed\Qt5WinExtras.dll"
COPY "%QT_BIN_DIR%\Qt5WebEngineWidgets.dll" "%PROJECT_WIN_DIR%\Project_Deployed\Qt5WebEngineWidgets.dll"

CALL "cp_resources.bat" "%PROJECT_WIN_DIR%\Project_Deployed"

:::::::::::::::
:: Copy Python STD lib files
call:checkMakeDir "%PROJECT_WIN_DIR%\Project_Deployed\Lib\"
XCOPY /e /h /y "%FUEL_ROOT%\static-cpython\Lib" "%PROJECT_WIN_DIR%\Project_Deployed\Lib\"

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

