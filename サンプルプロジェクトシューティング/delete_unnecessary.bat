REM いらないフォルダをすべて削除する。

rd /s /q project\x64
rd /s /q project\.vs
rd /s /q game\x64
rd /s /q aqua\x64
del game\aqua_debug_log.txt

pause
