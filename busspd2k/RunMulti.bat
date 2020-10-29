REM  The following starts 3 copies of the program. The optional
REM  third one opens a window but does not run. This might be
REM  required to act as foreground window to ensure that the
REM  other two obtain equal priority/share of time when running
REM  concurrently. Using this procedure on a dual processor
REM  system should result in the programs finishing at about
REM  the same time and two sets of full speed results. On a
REM  single CPU the overall performance of the sum of speeds
REM  should be similar to that obtained on running one BusSpd2k.
REM  With say KB 8192 using RAM, transfers will be slower than
REM  running one copy as memory is shared but, as some of the
REM  time is used by the CPU, the sum of speed might be greater.  

Start BusSpd2k Reliability, KB 8, Log Log1.txt
Start BusSpd2k Reliability, KB 8, Log Log2.txt
Start BusSpd2k