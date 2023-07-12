@echo off
cls
echo "Closing App Inventor 2 environtment...."
taskkill /IM emulator.exe > nul
taskkill /IM adb.exe > nul
taskkill /IM aiWinStarter.exe > nul
taskkill /IM cmd.exe > nul