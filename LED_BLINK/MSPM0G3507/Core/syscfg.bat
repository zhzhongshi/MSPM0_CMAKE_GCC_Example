@echo off

set SYSCFG_PATH="C:\ti\sysconfig_1.23.0\sysconfig_cli.bat"
set SDK_ROOT="C:\ti\mspm0_sdk_2_04_00_06"
%SYSCFG_PATH% -o "%CD%" -s "%SDK_ROOT%\.metadata\product.json" --compiler gcc "%CD%\empty.syscfg --device MSPM0G3507

