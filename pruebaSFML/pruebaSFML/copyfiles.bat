@echo off
echo Duplicador de Archivos para el .exe by Franco Vega

set targetdir=%1
set solutiondir=%2
set config=%3

echo Copiando librerias dinamicas

IF %config% == "1" (

XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-graphics-d-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-system-d-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-window-d-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\thor-v2.0-msvc2015\bin\thor-d.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\TGUI-0.8\bin\tgui-d.dll" "%targetdir%" /E /Y /S

) ELSE IF %config% == "2" (

XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-graphics-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-system-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\SFML-2.5.1\bin\sfml-window-2.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\thor-v2.0-msvc2015\bin\thor.dll" "%targetdir%" /E /Y /S
XCOPY "%solutiondir%lib\TGUI-0.8\bin\tgui.dll" "%targetdir%" /E /Y /S

)

echo Copiando Archivos de Assets....

MKDIR "%targetdir%res/assets"
XCOPY "%solutiondir%res/assets" "%targetdir%res/assets" /E /Y /S

echo Copia de Assets terminada!