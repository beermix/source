REM  Paging Test

REM  This runs one of the six write/read reliability tests

REM  Start with say 0.75 of RAM size, repeat once, then run further tests
REM  increasing KB to RAM size or greater

start busspd2k.exe Reliability, Paging, KB 200000, Log Paging.txt
