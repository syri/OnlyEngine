:: Written by syri.
::
@echo off

set EngineDirectory=%~dp0

cls
echo Enter New Project Name. (Default: Game)
set /p ProjectName=: 
IF NOT DEFINED ProjectName (SET ProjectName=Game)

cls
echo Enter Development Environment to Generate Project Files for Uma. (Default: vs2019)
set /p DevelopmentEnvironment=: 
IF NOT DEFINED DevelopmentEnvironment (SET DevelopmentEnvironment=vs2019)

cls
echo Creating Project Files For: %ProjectName% [Engine Directory: %EngineDirectory%, Environment: %DevelopmentEnvironment%]
call %EngineDirectory%Binaries/Win64/Tools/ProjectBuilder.exe /ProjectName:%ProjectName% /EngineDirectory:%EngineDirectory% /DevelopmentEnvironment:%DevelopmentEnvironment%
pause
