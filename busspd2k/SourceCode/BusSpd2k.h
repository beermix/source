#include <windows.h>

void WhatConfig();

extern char    configData1[200];
extern char    configData2[200];
extern char    configData3[200];
extern int     hasMMX;
extern DWORD   ramsize;
extern DWORD   freesize;

#define EXTRA_DATA_OFFSET   0
#define MENU_ABOUT          1
#define MENU_PHELP          2
#define MENU_RHELP          3
#define MENU_BHELP          4
#define MENU_EXIT           9
#define MENU_RUNALL        11
#define MENU_TEST          12
#define MENU_DISPLAY       10

#define RESULTS           949
#define TEST_IT           936
#define RUN_ALL           937
#define RUN2              933
#define EXIT_BUTTON       934
#define RESULTS1          849
#define NOTES1            850
#define KB_USED           960
#define MSECS             961
#define OFFSET            962
#define AT_KB             970
#define AT_SECS           971

