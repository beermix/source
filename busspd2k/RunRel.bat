REM  The following runs the twelve reliability tests for 10 seconds 
REM  each using 4096 KBytes. Results will be in log file Log1.txt.   
REM  KBytes 600000 works using 640 MB RAM on W2K and Win98
REM  Change KBytes to test most of RAM or smaller values to fit in cache
REM  A good test is via using 10 of these commands at appropriate Kbytes

Start BusSpd2k Reliability, KBytes 4096, Seconds 10, Log Log1.txt