@echo off
setlocal enabledelayedexpansion
REM Set your settings up how you want them
title TrueDolphin Test Server
set serverName=TrueDolphin Test Server
set serverPort=2302
set serverConfig=serverDZ.cfg
set modlist="-mod=@passive;WS/@Community-Online-Tools;WS/@CF;WS/@Dabs Framework;WS/@DayZ-Expansion-Bundle;WS/@DayZ-Expansion-Licensed;WS/@DayZ-Expansion-Animations;"
set servermods="-servermod="
set "startargs=-config=%serverConfig% -profiles=Profiles -port=%serverPort% -cpuCount=%serverCPU% -adminlog -netlog -freezecheck -startNavmeshDataServer -profile"
REM Set the hour to restart on ( example 3rd hour (3am/pm, 6am/pm, 9am/pm, 12am/pm))
set interval_hours=3



REM below this line, care should be taken.
set "startline=%servermods% %modlist% %startargs%"
set processName=DayZServer_x64.exe
set /A "interval_seconds=interval_hours * 3600"
taskkill /f /im "%processName%" >nul
cls
echo First Start Pause
:start
timeout 10
start "DayZ Server" /min "DayZServer_x64.exe" %startline%
:LOOP
REM Get the current time
for /f "tokens=1-3 delims=:." %%a in ("!time!") do (
    set "hours=%%a"
    set "minutes=%%b"
    set "seconds=%%c"
)

REM Check if the current time is a multiple of the interval_hours
set /A "remainder=hours %% interval_hours"

if !remainder! equ 0 (
    if !minutes! equ 0 (
        if !seconds! LSS 5 (
            echo "interval hour reached. killing server and starting new one."
            taskkill /f /im "%processName%" >nul
            echo "(!hours!:!minutes!:!seconds!) %serverName% prep, waiting 10s"
            goto start
        )
    )
)
tasklist | findstr /i "%processName%" >nul

if %errorlevel% equ 0 (
    tasklist /FI "IMAGENAME eq %processName%" | find /i "%processName%" >nul
    if %errorlevel% equ 0 (
	cls
        echo "(!hours!:!minutes!:!seconds!) %processName% is responsive."
    ) else (
        echo %processName% is not responsive. Restarting...
        taskkill /f /im "%processName%" >nul
        echo %processName% is terminated.
	echo Restart Pause
	timeout 10
        start "DayZ Server" /min "DayZServer_x64.exe" %startline%
        echo %processName% is restarted.
    )
) else (
    echo %processName% is not running.
	goto start
)

REM Wait for the specified interval in seconds
timeout /t 1 >nul
goto LOOP