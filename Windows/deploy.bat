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
:: Init Lavabo Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Check & Init
CALL "%SPARK_BUILD_WIN_DIR%\check_install.bat" || goto :error
CALL "%LAVABO_WIN_TOOLS_MSVC_DIR%\_init_msvc.bat" || goto :error
CALL "%LAVABO_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
:::::::::::::::
:: Building Editor
SET "OVERRIDE_WIN_SDK=$(WindowsTargetPlatformVersion)"
IF "%WINDOWS_VERSION%" == "7" SET "OVERRIDE_WIN_SDK=10.0.16299.0"
IF "%WINDOWS_VERSION%" == "10" SET "OVERRIDE_WIN_SDK=10.0.17134.0"

MSBUILD "%LAVABO_PROJECT_DIR%\Lavabo.sln" /p:Configuration=Release;WindowsTargetPlatformVersion="%OVERRIDE_WIN_SDK%" || goto :error

:::::::::::::::
:: Clean & create deploy dir
:Repeat
RMDIR /s /q "%LAVABO_WIN_DIR%\Lavabo_Deployed\"
IF EXIST "%LAVABO_WIN_DIR%\Lavabo_Deployed\" goto :Repeat
chgcolor %CTEXT%
ECHO old deployment was cleaned
MKDIR "%LAVABO_WIN_DIR%\Lavabo_Deployed\"
ECHO "%LAVABO_WIN_DIR%\Lavabo_Deployed\"

:::::::::::::::
:: Copy Files
COPY "%LAVABO_PROJECT_DIR%\x64\Release\Lavabo.exe" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Lavabo.exe"
COPY "%LAVABO_PROJECT_DIR%\x64\Release\openal32.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\openal32.dll"
COPY "%QT_BIN_DIR%\Qt5Core.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Qt5Core.dll"
COPY "%QT_BIN_DIR%\Qt5Gui.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Qt5Gui.dll"
COPY "%QT_BIN_DIR%\Qt5Widgets.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Qt5Widgets.dll"
COPY "%QT_BIN_DIR%\Qt5WinExtras.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Qt5WinExtras.dll"
COPY "%QT_BIN_DIR%\Qt5WebEngineWidgets.dll" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Qt5WebEngineWidgets.dll"

CALL "cp_resources.bat" "%LAVABO_WIN_DIR%\Lavabo_Deployed"

:::::::::::::::
:: Copy Python STD lib files
call:checkMakeDir "%LAVABO_WIN_DIR%\Lavabo_Deployed\Lib\"
XCOPY /e /h /y "%SPARK_ROOT%\static-cpython\Lib" "%LAVABO_WIN_DIR%\Lavabo_Deployed\Lib\"

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

