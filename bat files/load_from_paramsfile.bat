


@echo off
set serverName=TrueDolphin Test Server
title %serverName%
set serverPort=2302
set serverConfig=serverDZ.cfg
set processName=DayZServer_x64.exe
set duration=14400
set modlist=""
set servermods="-servermod="
set startargs=-config=%serverConfig% -profiles=Profiles -port=%serverPort% -cpuCount=%serverCPU% -par=params.txt -server -adminlog -netlog -freezecheck -server -newErrorsAreWarnings=1
set startline= %servermods% %modlist% %startargs% 


setlocal enabledelayedexpansion
set startTime=!time: =0!
set /A elapsedTime=0
echo First Start Pause
timeout 10
:start
echo (%time%) %serverName% started.
start "DayZ Server" /min "%processName%" %startline%
:loop
tasklist | findstr /i "%processName%" >nul

if %errorlevel% equ 0 (
    tasklist /FI "IMAGENAME eq %processName%" | find /i "%processName%" >nul
    if %errorlevel% equ 0 (
	cls
        echo %processName% is responsive.
    ) else (
        echo %processName% is not responsive. Restarting...
        taskkill /f /im "%processName%" >nul
        echo %processName% is terminated.
	echo Restart Pause
	timeout 10
        start "DayZ Server" /min "%processName%" %startline%
        echo %processName% is restarted.
    )
) else (
    echo %processName% is not running.
	timeout 10
	goto start
)

timeout /t 1 >nul

setlocal enabledelayedexpansion
set currentTime=!time: =0!
set /A startHour=1!startTime:~0,2! - 100
set /A startMinute=1!startTime:~3,2! - 100
set /A startSecond=1!startTime:~6,2! - 100
set /A currentHour=1!currentTime:~0,2! - 100
set /A currentMinute=1!currentTime:~3,2! - 100
set /A currentSecond=1!currentTime:~6,2! - 100
set /A startSeconds=startHour*3600 + startMinute*60 + startSecond
set /A currentSeconds=currentHour*3600 + currentMinute*60 + currentSecond
endlocal & (
    set /A elapsedTime=currentSeconds-startSeconds
)

if %elapsedTime% lss %duration% goto loop

echo Time limit reached. Restarting %processName%...
taskkill /f /im "%processName%" >nul
echo %processName% is terminated.
echo Timer Pause
start "DayZ Server" /min "%processName%" %startline%
echo %processName% is restarted.
goto loop
