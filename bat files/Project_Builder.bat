@echo off
setlocal EnableDelayedExpansion

rem ============================================================
rem  CONFIGURATION - edit these values
rem ============================================================

rem Drive letter to use for the virtual drive (no colon)
set VDRIVE=X

rem Source drive/root that your folders live on
set SOURCE_ROOT=P:

rem Program to launch (full path, use quotes if spaces)
set TARGET_EXE="C:\Program Files (x86)\Steam\steamapps\common\DayZ Tools\Bin\AddonBuilder\AddonBuilder.exe"

rem Optional: arguments to pass to the program
set TARGET_ARGS=

rem Folders to junction from SOURCE_ROOT to VDRIVE
rem Format: set LINK[n]=FolderName
rem The folder must exist under SOURCE_ROOT
set LINK[0]=bin
set LINK[1]=Core
set LINK[2]=DZ
set LINK[3]=scripts
set LINK[4]=graphics
set LINK[5]=gui
rem Add more as needed: set LINK[6]=AnotherFolder

rem ============================================================
rem  SETUP
rem ============================================================

echo [*] Setting up virtual drive %VDRIVE%: ...

rem Check the drive letter is not already in use
if exist %VDRIVE%:\ (
    echo [!] Drive %VDRIVE%: is already in use. Aborting.
    pause
    exit /b 1
)

rem Create a temp staging folder that will back the virtual drive
set STAGING=%TEMP%\vdrive_staging_%RANDOM%
mkdir "%STAGING%"
if errorlevel 1 (
    echo [!] Failed to create staging directory. Aborting.
    pause
    exit /b 1
)

rem Mount the staging folder as the virtual drive
subst %VDRIVE%: "%STAGING%"
if errorlevel 1 (
    echo [!] Failed to create virtual drive %VDRIVE%:. Aborting.
    rmdir /s /q "%STAGING%"
    pause
    exit /b 1
)
echo [+] Mounted %STAGING% as %VDRIVE%:

rem Create junctions on the virtual drive pointing to source folders
set /a IDX=0
:link_loop
    if not defined LINK[%IDX%] goto :link_done
    call set FOLDER=%%LINK[%IDX%]%%
    set SRC=%SOURCE_ROOT%\!FOLDER!
    set DST=%VDRIVE%:\!FOLDER!

    if not exist "!SRC!\" (
        echo [!] Source folder not found, skipping: !SRC!
    ) else (
        mklink /J "!DST!" "!SRC!" >nul
        if errorlevel 1 (
            echo [!] Failed to create junction for: !FOLDER!
        ) else (
            echo [+] Junction %VDRIVE%:\!FOLDER! -^> !SRC!
        )
    )
    set /a IDX+=1
goto :link_loop
:link_done

echo.
echo [*] Launching: %TARGET_EXE% %TARGET_ARGS%
echo [*] Virtual drive %VDRIVE%: will be removed when the program exits.
echo.

rem ============================================================
rem  LAUNCH - script blocks here until the program exits
rem ============================================================

%TARGET_EXE% %TARGET_ARGS%

rem ============================================================
rem  TEARDOWN
rem ============================================================

echo.
echo [*] Program exited. Cleaning up virtual drive %VDRIVE%: ...

rem Remove junctions (rmdir on a junction removes the link, not the target)
set /a IDX=0
:unlink_loop
    if not defined LINK[%IDX%] goto :unlink_done
    call set FOLDER=%%LINK[%IDX%]%%
    set DST=%VDRIVE%:\!FOLDER!
    if exist "!DST!\" (
        rmdir "!DST!" >nul 2>&1
        echo [-] Removed junction: %VDRIVE%:\!FOLDER!
    )
    set /a IDX+=1
goto :unlink_loop
:unlink_done

rem Unmount the virtual drive
subst %VDRIVE%: /D
if errorlevel 1 (
    echo [!] Warning: could not unmount %VDRIVE%:. Run manually:  subst %VDRIVE%: /D
) else (
    echo [-] Unmounted %VDRIVE%:
)

rem Clean up staging folder
rmdir /s /q "%STAGING%"
echo [-] Removed staging directory.

echo.
echo [*] Done.
timeout /t 3 >nul
endlocal
