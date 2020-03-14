@echo off

cls
echo Enter Development Environment to Generate Project Files For. (Default vs2019)
set /p devEnvironment=: 
IF NOT DEFINED devEnvironment (SET devEnvironment=vs2019)

cls
echo Generating Project files for %devEnvironment%
start Vendor/Premake/premake5.exe %devEnvironment%
echo Done.

pause
