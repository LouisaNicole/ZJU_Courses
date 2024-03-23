@echo off
setlocal enabledelayedexpansion

:main
set /p "p1=Please input your command (choose pdadd/pdshow/pdlist/pdremove, or exit to quit): "

if "!p1!"=="pdadd" (
    set /p "p2=Please input your date (end with a single character '.'): "
    .\add.exe "!p2!"
) else if "!p1!"=="pdshow" (
    set /p "p2=Please input your date: "
    .\show.exe "!p2!"
) else if "!p1!"=="pdlist" (
    set /p "flag=Do you want to list all? (1 for yes, 0 for no): "
    if "!flag!"=="1" (
        .\list.exe
    ) else (
        set /p "p2=Begin date: "
        set /p "p3=End date: "
        .\list.exe "!p2!" "!p3!"
    )
) else if "!p1!"=="pdremove" (
    set /p "p2=Please input your date (return -1 means remove failed): "
    .\remove.exe "!p2!"
) else if "!p1!"=="exit" (
    goto :eof
) else (
    echo Invalid command
)

goto :main

:eof
endlocal
pause