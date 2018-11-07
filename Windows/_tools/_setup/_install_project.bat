:::::::::::::::
:: _INSTALL_EDITOR.BAT
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
:: Init Project Dev Env Variables
CALL _initprojectenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Check if Extlibs are installed properly since we are going to install them in the project directories
chgcolor %CTEXT%
ECHO Checking install setup before proceeding
CALL "%FUEL_BUILD_WIN_DIR%\check_install.bat" %1 || goto :error

:::::::::::::::
:: MKDIRS
call:checkMakeDir "%PROJECT_PROJECT_DIR%\x64\"
call:checkMakeDir "%PROJECT_PROJECT_DIR%\x64\Release\"
call:checkMakeDir "%PROJECT_PROJECT_DIR%\x64\Debug\"
:: COPY ALL DLL TO PROJECT
for /R "%FUEL_ROOT%\_install\release_x64\bin" %%f in (*.dll) do copy %%f "%PROJECT_PROJECT_DIR%\x64\Release\"
for /R "%FUEL_ROOT%\_install\debug_x64\bin" %%f in (*.dll) do copy %%f "%PROJECT_PROJECT_DIR%\x64\Debug\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\DLLs\*") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Release\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\DLLs\*d.dll") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Debug\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\DLLs\*d.pyd") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Debug\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\Lib\site-packages\*.dll") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Release\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\Lib\site-packages\*.pyd") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Release\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\Lib\site-packages\*d.dll") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Debug\"
FOR %%G IN ("%EXTLIBS_DIR%\_install\opencv_python\Lib\site-packages\*d.pyd") DO copy %%G "%PROJECT_PROJECT_DIR%\x64\Debug\"
:: SOME CLEAN IN CASE OVERSHOOT COPYING DEBUG DLLS TO RELEASE DIR
FOR %%G IN ("%PROJECT_PROJECT_DIR%\x64\Release\*d.dll") DO del %%G
FOR %%G IN ("%PROJECT_PROJECT_DIR%\x64\Release\*d.pyd") DO del %%G
:::::::::::::::
:: Copy Python STD lib files
call:checkMakeDir "%PROJECT_PROJECT_DIR%\Lib\"
XCOPY /e /h /y "%FUEL_ROOT%\_install\opencv_python\Lib" "%PROJECT_PROJECT_DIR%\Lib\"

:: Install Qt dependeancies
copy "%QT_BIN_DIR%\Qt5WinExtrasd.dll" "%PROJECT_PROJECT_DIR%\x64\Debug\"
copy "%QT_BIN_DIR%\Qt5Cored.dll" "%PROJECT_PROJECT_DIR%\x64\Debug\"
copy "%QT_BIN_DIR%\Qt5Guid.dll" "%PROJECT_PROJECT_DIR%\x64\Debug\"
copy "%QT_BIN_DIR%\Qt5WebEngineWidgetsd.dll" "%PROJECT_PROJECT_DIR%\x64\Debug\"
copy "%QT_BIN_DIR%\Qt5Widgetsd.dll" "%PROJECT_PROJECT_DIR%\x64\Debug\"

copy "%QT_BIN_DIR%\Qt5WinExtras.dll" "%PROJECT_PROJECT_DIR%\x64\Release\"
copy "%QT_BIN_DIR%\Qt5Core.dll" "%PROJECT_PROJECT_DIR%\x64\Release\"
copy "%QT_BIN_DIR%\Qt5Gui.dll" "%PROJECT_PROJECT_DIR%\x64\Release\"
copy "%QT_BIN_DIR%\Qt5WebEngineWidgets.dll" "%PROJECT_PROJECT_DIR%\x64\Release\"
copy "%QT_BIN_DIR%\Qt5Widgets.dll" "%PROJECT_PROJECT_DIR%\x64\Release\"

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

