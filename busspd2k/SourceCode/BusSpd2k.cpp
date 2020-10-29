/* 
 * BusSpd2K Benchmark Version 2.1 Copyright (c) Roy Longbottom 2004 
 *            V2.2 allocMem line 422 - 21
 *            V2.2a changes for MMX to avoid compiler warnings
 *
 * BusSpd2K.exe is a Windows based program with two kinds of tests, Performance and Reliability
 *
 * Performance Tests
 *
 * These measures performance on transferring data from memory. Ten tests
 * are run with data size 4, 8, 16, 32 etc. Kbytes with a default maximum
 * of 50% of main RAM size for 128 MB or greater. Above 128 MB options are
 * available to select maximum of RAM size minus 64 MB. Default running
 * time is a minimum of 100 milliseconds per test. Extended sequences of
 * assembly code instructions are used and multiple registers, attempting
 * to transfer data as fast as possible. Results are calculated in millions
 * of bytes per second. Results are displayed as the tests are running and
 * appended to a log file, BusRead.txt. The benchmark runs via Win9X or
 * NT/2K/XP.   
 *  
 * The first four tests do not transfer all data to CPU registers but use
 * memory address increments of 64, 32, 16 and 8 bytes, loading 4 bytes,
 * to show speed when data is transferred over buses in a burst. Test 5
 * loads all data to 1 register and Test 6 to 2 registers alternately.
 * Tests 7/8 are as 5/6 but use AND instead of MOV. Tests 9/10 use MMX
 * instructions, loading data to 1/8 registers. The latter generally show
 * maximum data transfer rate but, on CPUs with 64 byte burst reading
 * (AMD and P4), potential maximum from RAM is test 1 speed x 16. Data
 * for Tests 7 and 8 is checked for correctness and any errors reported.
 *
 * Reliability Tests (using MMX instructions)
 *
 * A facility is provided to select memory size in the same range as
 * Performance Tests in order to test via caches or RAM. Twelve tests
 * are run, each for the selected time of 1 to 1000 seconds (default 5).  
 * Six tests write to memory then read read/compare and 6 tests
 * repetitively read and compare. Data patterns used for the latter are:
 *
 *             Test 1   0x00000000 and 0x00000000
 *             Test 2   0xFFFFFFFF and 0xFFFFFFFF
 *             Test 3   0xA5A5A5A5 and 0x5A5A5A5A
 *             Test 4   0x55555555 and 0xAAAAAAAA
 *             Test 5   0x33333333 and 0xCCCCCCCC
 *             Test 6   0xF0F0F0F0 and 0x0F0F0F0F
 *
 * The first 6 tests use the same patterns as above except for the first
 * two which use 0x00000000 and 0xFFFFFFFF. On alternate passes, the
 * patterns are reversed so that all memory data is changed.
 *
 *  Modules
 *
 *  Config.cpp - via WhatConfig() identifies CPU type/speed, memory size
 *  and OS version,
 *
 *  BusSpd2K.rc - menus and dialog boxes
 *     MENU_ABOUT    - AboutDlgProc() DIALOG AboutBox
 *     MENU_PHELP    - AboutDlgProc() DIALOG PerfHelp
 *     MENU_RHELP    - AboutDlgProc() DIALOG RelHelp
 *     MENU_BHELP    - AboutDlgProc() DIALOG BatchHelp   
 *     MENU_RUNALL   - runTests();
 *     MENU_TEST     - runOtherTests()
 *     MENU_DISPLAY  - displayWhatever()
 *     MENU_EXIT     - CleanUpAndPostQuit()
 *     DIALOG_8      - TestPanel()
 *     DIALOG_9      - RunPanel()
 *     DIALOG AboutBox 
 *     DIALOG PerfHelp
 *     DIALOG RelHelp
 *     DIALOG BatchHelp
 *
 *  BusSpd2K.h and BusSpd2K.ico
 *
 *  BusSpd2K.cpp
 *
 *  Functions
 *
 *  WinMain() - usual Windows functions
 *  InitApp() - usual Windows functions, allocates variable values,
 *     calculates maximum memory to be tested, uses WhatConfig()
 *     and displayWhatever(), processes command line.
 *  WindowProc() - usual Windows functions for menus   
 *  AboutDlgProc() - displays About and Help text
 *  CleanUpAndPostQuit() - set up exit
 *  TestPanel() - dialog box displayed at start with information
 *     including RAM size and CPU type, Two panels:
 *     1 - Performance - Drop down lists for selection of Maximum
 *         Memory KB, Millisecs Per Test and Bytes Offset (0 to 31).
 *         Offset can test with data not aligned on word boudaries.
 *         RUN_ALL button as MENU_RUNALL
 *     2 - Reliability - Drop down lists for selection of At Memory
 *         KB (size to test) and Seconds Per Test.
 *         TEST_IT as MENU_TEST
 *     Also EXIT_BUTTON as MENU_EXIT
 *     TestPanel is also displayed after tests showing results
 *  RunPanel() - dialog box cleared and refreshed after each set of
 *      tests, showing all results so far, no buttons
 *
 *  displayWhatever() clears dialog boxes and displays TestPanel()
 *  runTests() - Opens log file, executes local_time(), logs date/time
 *      and headings, allocates maximum memory used, executes findmem().
 *      Loop j used for each memory size and runs the 10 tests, firstly
 *      filling the memory with a data pattern. Each test uses
 *      start_time(), end_time() and checkTime() and executes an
 *      assembly code function:
 *
 *      Test  1 - readmem64()  - 64 byte inc mov 1 reg
 *      Test  2 - readmem32()  - 32 byte inc mov 1 reg
 *      Test  3 - readmem16()  - 16 byte inc mov 1 reg
 *      Test  4 - readmem8()   -  8 byte inc mov 1 reg
 *      Test  5 - readmem4()   -  4 byte inc mov 1 reg
 *      Test  6 - readmem4b()  -  4 byte inc mov 2 reg
 *      Test  7 - checkmem2()  -  4 byte inc and 1 reg
 *      Test  8 - checkmem2b() -  4 byte inc and 2 reg
 *      Test  9 - readmmx1()   -  8 byte inc MMX 1 reg
 *      Test 10 - readmmx8()   -  8 byte inc MMX 8 reg
 *
 *      Results are updated in RunPanel and saved to log file.
 *      At end local_time() and WhatConfig() are run, configuration
 *      data, end time and memory stats are logged, the memory
 *      released then displayWhatever(). logErrors() is called
 *      after test 8 if data is incorrect. 
 *  checkTime() - recalibrates n1 passes so tests run for at least
 *      runTime (100 milliseconds default)
 *  local_time() - date/time of day
 *  start_time() - start time from high resolution timer
 *  end_time() - end time and running time msecs
 *  findmem() - Assembly code to find start address
 *  logErrors() - saves details or errors to file ERRORlog.txt
 *  runOtherTests() - Defines data patterns, Opens log file, executes
 *      local_time(), logs date/time and headings, allocates memory to be
 *      used, executes findmem(). Loop j used for first six tests,
 *      selecting different data patterns, uses start_time(), end_time(),
 *      writemmx(), checkData(), displays and logs results and any errors.
 *      Loop j then runs second 6 tests first with one pass of the first
 *      tests then repeats mmxRun() with start_time() and end_time().
 *      After test checkData() is run and results/errors reported.
 *  writemmx() - assembly code writing to memory
 *  checkData() - runs errorcheck(). If any errors, data checked C code. 
 *  mmxRun() - assembly code reading memory with add and subtract to
       produce a single 64 bit pattern for checking purposes 
 *  errorcheck() - assembly code using OR and AND to produce 8 x 32 bit
 *      check words.
 *
 */
 
#define NAME "Test"
#define TITLE " Test Bus Speed"
#define INITGUID

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <time.h>
#include <mmintrin.h>
#include <math.h>
#include "BusSpd2k.h"


// variables used by assembly code

int * xx;
int   xaddress;
int   result1;
int   xoffset = 0;
int   mempasses;
int   sumCheck[8];
int   outerLoop;
int   passbytes;
int   mmxCheck[2];

//  ************** PROTOPTYPES *****************

inline void findmem();

inline void readmem64();
inline void readmem32();
inline void readmem16();
inline void readmem8();
inline void readmem4();
inline void readmem4b();
inline void checkmem2();
inline void checkmem2b();
inline void readmmx1(); 
inline void readmmx8();

inline void writemmx();
inline void mmxRun();
inline void errorcheck();


BOOL FAR PASCAL AboutDlgProc( HWND, UINT, WPARAM, LPARAM);
static BOOL InitApp(HINSTANCE, LPSTR, int);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);                  
static void CleanUpAndPostQuit(void);
void displayWhatever(HWND);

BOOL FAR PASCAL TestPanel( HWND, UINT, WPARAM, LPARAM);
BOOL FAR PASCAL RunPanel( HWND, UINT, WPARAM, LPARAM);

void checkData();
void local_time();
void end_time();
void start_time();
void checkTime();
BOOL runTests();
BOOL runOtherTests();
BOOL logErrors(int expected, int was, int memTested);


// ************* GLOBAL VARIABLES **********
 

char   version[30] = "Version 2.2a";

char    timeday[30];
LARGE_INTEGER starttime;
double  secs;
int     n1;
double  PrunSecs;
int     RrunSecs;
double  PtestTimes[20];
int     RtestTimes[20];
int     PtimeToDo;
int     RtimeToDo;
int     PmaxToDo;
int     RmaxToDo;
char    logfile[80] = "BusRead.txt";


BOOL bQuit = FALSE;

HWND   mainHWND;
HWND   testHwnd = NULL;
HWND   runHwnd = NULL;
HINSTANCE MyInstance;
char    windowText[256];
char    commandLine[1024] = "";

short     keyPress;
BOOL  autoRun = FALSE;
BOOL  oneTest = FALSE;
BOOL  doTesting = FALSE;
char   writeMsg[256];
double results[30][10];

int    memUsed[100];
int  passesDone;
BOOL  runDone = FALSE;
int  ramKBused;
int  ramKB;
int Pruns = 10; // 2 MB;
int Rrun = 10; // 2 MB;
int runsInit = 10;
int allocMem[50];
RECT     winRect;
int     screenWide;
int     screenHigh;
int    maxrows = 13;
int    userows;
char  startRam[200];
BOOL   errorFound = FALSE;
BOOL   speedTest = TRUE;
char  testmsg[30][256];
int useMemK = 2048; // 2048;
int i0Start;
int  errors;
int  errord;
int  errorp;
int usePattern1;
int usePattern2;
int  isdata[16];
int  sbdata[16];
int  errword[16];
char errormsg[64] = " ";
char patternIs[20];


void displayWhatever(HWND hwnd)
{
    sprintf(windowText, " Bus Speed And Reliability Tests");
    SetWindowText(mainHWND, windowText);        
        
    if (doTesting)
    {
        if (testHwnd)   DestroyWindow(testHwnd);
    }
    else
    {    
        if (runHwnd)    DestroyWindow(runHwnd);
        testHwnd = CreateDialog( MyInstance,"DIALOG_8", hwnd, (DLGPROC)TestPanel);
    }  
} // displayWhatever


// WinMain - initialization, message loop

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR cmdline, int cmdshow)
{
    MSG         msg;
    
    hPrevInstance = hPrevInstance;

    if (!InitApp(hInstance, cmdline, cmdshow))
         return FALSE;

    GetMessage( &msg, NULL, 0, 0 );

    if (autoRun)
    {
         if (speedTest)
         {
             runTests();
         }
         else
         {
             runOtherTests();
         }
         CleanUpAndPostQuit();
    }        
    while(!bQuit)
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) )
        {
            
           if (msg.message == WM_QUIT)
           {
                CleanUpAndPostQuit();
                break;
           }
   
           if( !GetMessage( &msg, NULL, 0, 0 ) ) return ((int)msg.wParam);
           TranslateMessage(&msg);
           DispatchMessage(&msg);
        }
        else
        {
           // make sure we go to sleep if we have nothing else to do
           WaitMessage();
        }
    }
    return ((int)msg.wParam);
    
} // WinMain

// ***************************************************************************
//                    Initialization and object creation                     *
// ***************************************************************************

// InitApp
// Creates window

static BOOL
InitApp(HINSTANCE hInstance, LPSTR cmdline, int cmdshow)
{
    HWND hwnd;
    WNDCLASS wc;
    int   i, j;
    char *delims = {" ,"};
    char commands[20][256];
    char *p;
    int  KBytes;
    int  bytes1;
    char buf[256] = "";
    HDC  hdc;
    int msecs = 0;
    int runSecs = 0;
    int offset = 0;
    BOOL isHere;
    int newPos =0;
  
    
    // set up and registers the window class
    
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(DWORD);
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, "GenericIcon");
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = "GenericMenu";
    wc.lpszClassName = NAME;
    if (!RegisterClass(&wc))
        return FALSE;

    // Create the window

    hwnd =
        CreateWindow(
            NAME,
            TITLE,
            WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL,
            0,
            0,
            640,
            480,
            NULL, 
            NULL, 
            hInstance, 
            NULL 
        );

    if (!hwnd) return FALSE;

    mainHWND = hwnd;
    strcpy(commandLine, strupr(cmdline));

    hdc = GetDC(mainHWND);
    screenWide = GetDeviceCaps(hdc, HORZRES);
    screenHigh = GetDeviceCaps(hdc, VERTRES);   
    ReleaseDC(mainHWND, hdc);
    winRect.left = 0;
    winRect.top = 0;
    winRect.right = screenWide;
    winRect.bottom = screenHigh;

    WhatConfig();
    strcpy(startRam, configData3);
    ramKB = ramsize / 1024;

    allocMem[0] = 4096;  
    for (i=1; i<19; i++)
    {
        allocMem[i] = allocMem[i-1] * 2;
    }
        
    if (ramKB >   14000) runsInit = 11;
    if (ramKB >   30000) runsInit = 12;
    if (ramKB >   60000) runsInit = 13;
    if (ramKB >  120000) runsInit = 14;
    if (ramKB >  250000) runsInit = 16;
    if (ramKB >  500000) runsInit = 17;
    if (ramKB > 1000000) runsInit = 18;
    if (ramKB > 2000000) runsInit = 19;
    Pruns = runsInit;
    Rrun  = runsInit;

    PtestTimes[0] = 0.01;
    PtestTimes[1] = 0.05;
    PtestTimes[2] = 0.1;
    PtestTimes[3] = 0.5;
    PtestTimes[4] = 1.0;
    PtestTimes[5] = 5.0;
    PtestTimes[6] = 10.0;
    PtimeToDo = 2;
    PrunSecs = PtestTimes[PtimeToDo];
    PmaxToDo = 7;

    RtestTimes[0] = 1;
    RtestTimes[1] = 5;
    RtestTimes[2] = 10;
    RtestTimes[3] = 50;
    RtestTimes[4] = 100;
    RtestTimes[5] = 500;
    RtestTimes[6] = 1000;
    RtimeToDo = 1;
    RrunSecs = RtestTimes[RtimeToDo];
    RmaxToDo = 7;

    i = 0;
    p = strtok(commandLine, delims);
    while (p != NULL)
    {
        strcpy(commands[i], p);
        strcat(buf, commands[i]);
        strcat(buf, " ");
        i = i + 1;
        if (i > 9) break;
        p = strtok(NULL, delims);
    }
    if (i > 0)
    {
        strcpy(commandLine, buf);
    }
    else
    {
        strcpy(commandLine, "None");
    }
    autoRun = FALSE;
    KBytes = 0;
       
    for (j=0; j<i; j++)
    {
        switch(commands[j][0])
        {            
            case 'A': // Auto Run
             autoRun = TRUE;
             break;            

            case 'P': // One Test Only for Paging
             oneTest = TRUE;
             break;            

            case 'R': // Reliability Test
             speedTest = FALSE;
             autoRun = TRUE;
             break;            

            case 'K': // KBytes
             if (j < i -1)
             {
                 sscanf(commands[j+1], "%d", &KBytes);
             }
             break;            
       
            case 'M': // millisecs
             if (j < i -1)
             {
                 sscanf(commands[j+1], "%d", &msecs);
             }
             break;

            case 'S': // seconds
             if (j < i -1)
             {
                 sscanf(commands[j+1], "%d", &runSecs);
             }
             break;
                          
            case 'O': // offset
             if (j < i -1)
             {
                 sscanf(commands[j+1], "%d", &offset);
             }
             break;

            case 'L': // log file
             if (j < i -1)
             {
                 sscanf(commands[j+1], "%s", logfile);
             }
             break;
        }            
    }
    if (KBytes > 0)
    {
        bytes1 = KBytes * 1024;
        isHere = FALSE;
        for (i=0; i<runsInit; i++)
        {
            if (bytes1 == allocMem[i])
            {
                isHere = TRUE;
                newPos = i;
            }            
        }    
        if (!isHere)
        {
            newPos = 0;
            for (i=0; i<runsInit; i++)
            {
                if (bytes1 > allocMem[i]) newPos = i + 1;
            }
            if (newPos != runsInit)
            {
                for (i=runsInit; i>newPos; i--)
                {
                    allocMem[i] = allocMem[i-1];
                }
            }
            allocMem[newPos] = bytes1;    
            runsInit = runsInit + 1;
        }
        Pruns = newPos+1; 
        Rrun = Pruns;
    }
    ramKBused = allocMem[Pruns-1] / 1024;    
    useMemK = ramKBused;
    if (!autoRun)
    {
        if (runsInit == 13)
        {
            allocMem[runsInit] = allocMem[runsInit-1] * 3/2;
            runsInit = runsInit + 1;
        }
        else if (runsInit == 14)
        {
            allocMem[runsInit] = allocMem[runsInit-1] * 2;
            runsInit = runsInit + 1;
        }
        else if (runsInit > 15)
        {
            allocMem[runsInit] = allocMem[runsInit-1] * 3/2;
            runsInit = runsInit + 1;
        }
    }
    if (msecs > 0) PrunSecs = ((double) msecs) / 1000;

    isHere = FALSE;
    for (i=0; i<PmaxToDo; i++)
    {
        if (PrunSecs == PtestTimes[i])
        {
            isHere = TRUE;
            newPos = i;
        }            
    }
    if (!isHere)
    {
        newPos = 0;
        for (i=0; i<PmaxToDo; i++)
        {
            if (PrunSecs > PtestTimes[i]) newPos = i + 1;
        }            
        if (newPos != PmaxToDo)
        {
            for (i=PmaxToDo; i>newPos; i--)
            {
                 PtestTimes[i] =  PtestTimes[i-1];
            }
        }
        PtestTimes[newPos] = PrunSecs;
        PmaxToDo = PmaxToDo + 1;
    }
    PtimeToDo = newPos;

    if (runSecs > 0) RrunSecs = runSecs; 

    isHere = FALSE;
    for (i=0; i<RmaxToDo; i++)
    {
        if (RrunSecs == RtestTimes[i])
        {
            isHere = TRUE;
            newPos = i;
        }            
    }
    if (!isHere)
    {
        newPos = 0;
        for (i=0; i<RmaxToDo; i++)
        {
            if (RrunSecs > RtestTimes[i]) newPos = i + 1;
        }            
        if (newPos != RmaxToDo)
        {
            for (i=RmaxToDo; i>newPos; i--)
            {
                 RtestTimes[i] =  RtestTimes[i-1];
            }
        }
        RtestTimes[newPos] = RrunSecs;
        RmaxToDo = RmaxToDo + 1;
    }
    RtimeToDo = newPos;
    
    if (offset > 0) xoffset = offset;
    if (xoffset > 31) xoffset = 31;
    
    keyPress = GetAsyncKeyState(VK_ESCAPE);

    // Display the window
    
    ShowWindow(hwnd, cmdshow);    
    UpdateWindow(hwnd);

    if (!autoRun) displayWhatever(mainHWND);
    
    return TRUE;
    
}  // InitApp



// WindowProc - handle messages for the main application window


LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg,
                            WPARAM wparam, LPARAM lparam)                  
{
           
    switch( msg )
    {
    case WM_ACTIVATEAPP:
        break;
        
    case WM_INITMENUPOPUP:
        break;
        
    case WM_CREATE:
        break;

    case WM_DESTROY:
        CleanUpAndPostQuit();
        break;

    case WM_COMMAND:
        switch( LOWORD( wparam ) )
        {
        case MENU_ABOUT:
            if (testHwnd)   DestroyWindow(testHwnd);
            DialogBox( MyInstance,"AboutBox", hwnd, (DLGPROC)AboutDlgProc );
            displayWhatever(mainHWND);                                      
            break;

        case MENU_PHELP:
            if (testHwnd)   DestroyWindow(testHwnd);
            DialogBox( MyInstance,"PerfHelp", hwnd, (DLGPROC)AboutDlgProc );
            displayWhatever(mainHWND);                                      
            break;

        case MENU_RHELP:
            if (testHwnd)   DestroyWindow(testHwnd);
            DialogBox( MyInstance,"RelHelp", hwnd, (DLGPROC)AboutDlgProc );
            displayWhatever(mainHWND);                                      
            break;

        case MENU_BHELP:
            if (testHwnd)   DestroyWindow(testHwnd);
            DialogBox( MyInstance,"BatchHelp", hwnd, (DLGPROC)AboutDlgProc );
            displayWhatever(mainHWND);                                      
            break;

       case MENU_RUNALL:
            doTesting = TRUE;
            displayWhatever(mainHWND);
            speedTest = TRUE;                                      
            runTests();
            break;

       case MENU_TEST:
            doTesting = TRUE;
            displayWhatever(mainHWND);                                      
            speedTest = FALSE;                                      
            runOtherTests();
            break;

        case MENU_DISPLAY:
            displayWhatever(mainHWND);                                      
            break;
        
        case MENU_EXIT:
            CleanUpAndPostQuit();
            break;
                
        }
        break;
   
        case WM_PAINT:
             break;
           
        case WM_KEYDOWN:
            break;

       case WM_ACTIVATE:
            break;
    } 
    return DefWindowProc( hwnd, msg, wparam, lparam );

} // WindowProc




// AboutDlgProc - processes messages for the about dialog.

BOOL FAR PASCAL AboutDlgProc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam )
{
    lparam = lparam;

    switch( msg ) {
    case WM_INITDIALOG:
        return( TRUE );

    case WM_COMMAND:
        if( LOWORD( wparam ) == IDOK ) {
            EndDialog( hwnd, TRUE );
            return( TRUE );
        }
        break;
    }
    return( FALSE );

} // AboutDlgProc



  
void local_time()
{
    time_t time_of_day;
    time_of_day = time( NULL ); 
    strcpy (timeday, ctime(&time_of_day)); // timeday = date and time
    return;
}




// CleanUpAndPostQuit
// Release all D3DRM objects, post a quit message and set the bQuit flag

void
CleanUpAndPostQuit(void)
{
    bQuit = TRUE;
    return;
}


BOOL FAR PASCAL RunPanel( HWND hdlg, UINT msg,
                                WPARAM wparam, LPARAM lparam )
{
    wparam = wparam;
    lparam = lparam;
    hdlg = hdlg;
    int  k;
    int  kk = 6;
//    int FAR  tabs[11] = {1, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300};
//    int FAR  tabs[11] = {1, 27, 54, 81, 108, 135, 162, 189, 216, 243, 270};
    int FAR  tabs[11] = {1, 33, 60, 87, 114, 141, 168, 195, 222, 249, 276};

     switch( msg )
     {
       case WM_INITDIALOG:
       
        SendDlgItemMessage(hdlg, RESULTS1, LB_SETTABSTOPS, (WPARAM) 11, (LPARAM) (int FAR*) tabs); 
        sprintf(writeMsg, "Maximum RAM size to be tested %d KB", ramKBused);
        SendDlgItemMessage(hdlg, NOTES1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
        sprintf(writeMsg, "Flashing disk light suggest insufficient RAM and paging activity "
                      "to/from RAM and disk.");
        SendDlgItemMessage(hdlg, NOTES1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
        sprintf(writeMsg, "Press ESC to cancel and exit program. It might take some time.");
        SendDlgItemMessage(hdlg, NOTES1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
        
        if (runDone)
        {
            if (speedTest)
            {
                SendDlgItemMessage(hdlg, RESULTS1, LB_SETHORIZONTALEXTENT, 700, 0L);
                sprintf(writeMsg, " Bus Speed Test %s by Roy Longbottom"
                                  "%10.3f seconds minimum per test", version, PrunSecs);
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, " ");
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                if (xoffset > 0)
                {
                    sprintf(writeMsg, " Data accessed %d bytes offset from word boundary", xoffset);
                    SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                    sprintf(writeMsg, " ");
                    SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                    kk = 8;
                }
                sprintf(writeMsg, "    %c Reg2%c Reg2%c Reg2%c Reg2%c Reg1%c Reg2%c Reg1%c Reg2%c Reg1%c Reg8",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);   
    
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "KBytes%c Inc64%c Inc32%c Inc16%c  Inc8%c  Inc4%c  Inc4%c  Inc4%c  Inc4%c  Inc8%c  Inc8",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);   
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "  Used%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);           
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, " ");
                SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
    
                for (k=0; k<passesDone; k++)
                {
                   sprintf(writeMsg, "%6d %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f",  
                                    memUsed[k], 9, results[k][0], 9, results[k][1], 9, results[k][2],
                                                     9, results[k][3], 9, results[k][4], 9, results[k][5],
                                                     9, results[k][6], 9, results[k][7], 9, results[k][8],
                                                     9, results[k][9]);
                   SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                   SendDlgItemMessage(hdlg, RESULTS1, LB_SETCURSEL, k+kk, 0L);
                }
            }
            else
            {
                for (k=6; k<12; k++)
                {
                   sprintf(writeMsg, "Wr %6dKB %6.0f MB/Sec %s", memUsed[0], results[k][0], testmsg[k]);
                   SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                }
                for (k=0; k<passesDone; k++)
                {
                   sprintf(writeMsg, "Rd %6dKB %6.0f MB/Sec %s", memUsed[0], results[k][0], testmsg[k]);
                   SendDlgItemMessage(hdlg, RESULTS1, LB_ADDSTRING, 0, (LPARAM) writeMsg);                   
                }
                SendDlgItemMessage(hdlg, RESULTS1, LB_SETCURSEL, 18, 0L);
            }
        }
        return( TRUE );              
     }
     return( FALSE );
    
} // runPanel

BOOL FAR PASCAL TestPanel( HWND hdlg, UINT msg,
                                WPARAM wparam, LPARAM lparam )
{
    wparam = wparam;
    lparam = lparam;
    hdlg = hdlg;
    int  k, index;
//    int FAR  tabs[11] = {1, 27, 54, 81, 108, 135, 162, 189, 216, 243, 270};
    int FAR  tabs[11] = {1, 33, 60, 87, 114, 141, 168, 195, 222, 249, 276};

     switch( msg )
     {
       case WM_INITDIALOG:
        SendDlgItemMessage(hdlg, RESULTS, LB_SETTABSTOPS, (WPARAM) 11, (LPARAM) (int FAR*) tabs);
        for (k=0; k<runsInit; k++)
        {
            sprintf(writeMsg, "%8d",  allocMem[k] / 1024);
            SendDlgItemMessage(hdlg, KB_USED, CB_ADDSTRING, 0, (LPARAM) writeMsg);
            SendDlgItemMessage(hdlg, AT_KB, CB_ADDSTRING, 0, (LPARAM) writeMsg);
        }
        SendDlgItemMessage(hdlg, KB_USED, CB_SETCURSEL, Pruns-1, 0L);
        SendDlgItemMessage(hdlg, AT_KB, CB_SETCURSEL, Rrun-1, 0L);

        for (k=0; k<PmaxToDo; k++)
        {
            sprintf(writeMsg, "%8d",  (int)(PtestTimes[k] * 1000));
            SendDlgItemMessage(hdlg, MSECS, CB_ADDSTRING, 0, (LPARAM) writeMsg);
        }
        SendDlgItemMessage(hdlg, MSECS, CB_SETCURSEL, PtimeToDo, 0L);

        for (k=0; k<32; k++)
        {
            sprintf(writeMsg, "%8d", k);
            SendDlgItemMessage(hdlg, OFFSET, CB_ADDSTRING, 0, (LPARAM) writeMsg);
        }
        SendDlgItemMessage(hdlg, OFFSET, CB_SETCURSEL, xoffset, 0L);

        for (k=0; k<RmaxToDo; k++)
        {
            sprintf(writeMsg, "%8d",  (int)(RtestTimes[k]));
            SendDlgItemMessage(hdlg, AT_SECS, CB_ADDSTRING, 0, (LPARAM) writeMsg);
        }
        SendDlgItemMessage(hdlg, AT_SECS, CB_SETCURSEL, RtimeToDo, 0L);
        
        SendDlgItemMessage(hdlg, RESULTS, LB_SETHORIZONTALEXTENT, 700, 0L);
        if (runDone)
        {
            if (speedTest)
            {
                sprintf(writeMsg, " Bus Speed Test %s by Roy Longbottom"
                                  "%10.3f seconds minimum per test", version, PrunSecs);
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);

                sprintf(writeMsg, " ");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "    %c MovI%c MovI%c MovI%c MovI%c MovI%c MovI%c AndI%c AndI%c MMXm%c MMXm",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);   
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "    %c Reg2%c Reg2%c Reg2%c Reg2%c Reg1%c Reg2%c Reg1%c Reg2%c Reg1%c Reg8",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);   
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "KBytes%c Inc64%c Inc32%c Inc16%c  Inc8%c  Inc4%c  Inc4%c  Inc4%c  Inc4%c  Inc8%c  Inc8",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);   
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, "  Used%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S%c MB/S",
                                         9, 9, 9, 9, 9, 9, 9, 9, 9, 9);           
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, " ");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
    
                for (k=0; k<passesDone; k++)
                {
                   sprintf(writeMsg, "%6d %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f %c%6.0f",  
                                    memUsed[k], 9, results[k][0], 9, results[k][1], 9, results[k][2],
                                                     9, results[k][3], 9, results[k][4], 9, results[k][5],
                                                     9, results[k][6], 9, results[k][7], 9, results[k][8],
                                                     9, results[k][9]);
                   SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                }
                sprintf(writeMsg, " ");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
    
                sprintf(writeMsg, " Maximum RAM size tested %d KB at %10.3f seconds per test.",
                                            ramKBused, PrunSecs);
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, " Data accessed %d bytes offset from word boundary", xoffset);
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                sprintf(writeMsg, " Results should be in file BusRead.txt");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
    
                SendDlgItemMessage(hdlg, RESULTS, LB_SETCURSEL, passesDone-1, 0L);
            }
            else
            {
                for (k=6; k<12; k++)
                {
                   sprintf(writeMsg, "Wr %6dKB %6.0f MB/Sec %s", memUsed[0], results[k][0], testmsg[k]);
                   SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                }
                for (k=0; k<passesDone; k++)
                {
                   sprintf(writeMsg, "Rd %6dKB %6.0f MB/Sec %s", memUsed[0], results[k][0], testmsg[k]);
                   SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);                   
                }
                SendDlgItemMessage(hdlg, RESULTS, LB_SETCURSEL, 20, 0L);

                if (strlen(errormsg) > 10)
                {               
                    sprintf(writeMsg, " ERRORS in test. See BusRead.txt log file");
                }
                else
                {
                    sprintf(writeMsg, " ");
                    SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                    sprintf(writeMsg, " Reliability Test Using 64 bits MMX Instructions ");
                }
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                if (hasMMX)
                {
                    sprintf(writeMsg, " Memory size %7d KB, %d seconds per test", useMemK, RrunSecs);
                    SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                    sprintf(writeMsg, " Results should be in file BusRead.txt");
                    SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                }
                else
                {
                    sprintf(writeMsg, " ");
                    SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                    sprintf(writeMsg, " Cannot Run - No MMX Facilities");
                    SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
                }
            }
        }
        else
        {
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) configData1);
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) configData2);
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) configData3);
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) " ");


            strcpy(writeMsg, " Batch Command ");
            strncat(writeMsg, commandLine, 200);
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            sprintf(writeMsg, " ");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            sprintf(writeMsg, " PERFORMANCE - Select maximum memory, run time per test and bytes offset");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            sprintf(writeMsg, "  from word boundary then Run Tests button");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            sprintf(writeMsg, " ");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            if (hasMMX)
            {
                sprintf(writeMsg, " RELIABILITY - Select memory size to test and run time then Run Tests button");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            }
            else
            {                
                sprintf(writeMsg, " RELIABILITY Tests - Cannot Run as no MMX Facilities in CPU");
                SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);    
            }
            sprintf(writeMsg, " ");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
            sprintf(writeMsg, " After running, results should be in file BusRead.txt");
            SendDlgItemMessage(hdlg, RESULTS, LB_ADDSTRING, 0, (LPARAM) writeMsg);
        }
        return( TRUE );
                    
        case WM_COMMAND:

        if( HIWORD( wparam ) == CBN_SELCHANGE)
        {
            switch (LOWORD (wparam))
            {
                case KB_USED:
                 index = (int)SendDlgItemMessage(hdlg, KB_USED, CB_GETCURSEL, 0, 0);
                 ramKBused = allocMem[index] / 1024;
                 Pruns = index + 1;
                 break;                

                case MSECS:
                 index = (int)SendDlgItemMessage(hdlg, MSECS, CB_GETCURSEL, 0, 0);
                 PtimeToDo = index;
                 PrunSecs = PtestTimes[PtimeToDo];
                 break;                
                 
                case OFFSET:
                 xoffset = (int)SendDlgItemMessage(hdlg, OFFSET, CB_GETCURSEL, 0, 0);
                 break;

                case AT_KB:
                 index = (int)SendDlgItemMessage(hdlg, AT_KB, CB_GETCURSEL, 0, 0);
                 useMemK = allocMem[index] / 1024;
                 Rrun = index + 1;
                 break;                

                case AT_SECS:
                 index = (int)SendDlgItemMessage(hdlg, AT_SECS, CB_GETCURSEL, 0, 0);
                 RtimeToDo = index;
                 RrunSecs = RtestTimes[RtimeToDo];
                 break;                
            }
            
        }
        else if( HIWORD( wparam ) == BN_CLICKED)
        {
            switch (LOWORD (wparam))
            {
                case RUN_ALL:
                  PostMessage(mainHWND, WM_COMMAND, MENU_RUNALL, 0);
                 break;

                case TEST_IT:
                  PostMessage(mainHWND, WM_COMMAND, MENU_TEST, 0);
                 break;
                 

                case EXIT_BUTTON:
                 PostMessage(mainHWND, WM_COMMAND, MENU_EXIT, 0);
                 break;
            }
        }
        return( TRUE );         
     }
     return( FALSE );
    
} // TestPanel


void start_time()
{
    QueryPerformanceCounter(&starttime);
}
 
void end_time()
{
    LARGE_INTEGER liDiff;
    LARGE_INTEGER liFreq;

    QueryPerformanceCounter(&liDiff);

    liDiff.QuadPart -= starttime.QuadPart;

    (void)QueryPerformanceFrequency(&liFreq);
    
    secs = (double)liDiff.QuadPart / (double) liFreq.QuadPart;
}

BOOL logErrors(int expected, int was, int memTested)
{
    FILE    *errfile;

    errfile = fopen("ERRORLog.txt","a+");
    if (errfile == NULL)
    {
        sprintf(writeMsg, "Cannot open error log file");
        if (!autoRun) MessageBox(NULL, writeMsg, "ERROR WILL EXIT", MB_ICONWARNING | MB_OK);
        CleanUpAndPostQuit();
        return FALSE;
    }

    local_time();
    fprintf(errfile, " ERROR on checking data %s", timeday);
    fprintf(errfile, " Expected 0x%8.8lx Obtained 0x%8.8lx at %d KB\n\n", expected, was, memTested);
    fflush(errfile);
    fclose(errfile);
    return true;
}

BOOL runOtherTests()
{
    int i, j, j1, j2;
    int pattern1[16];
    int pattern2[16];
    int tempPattern;
    double n1Count;
    double timeCount;
    double millionBytes;
    char patternSB[20];
    char testmsgOld[256];
    double endSecs0; 
    double endSecs3; 
    FILE    *outfile;
    HDC  hdc;

    pattern1[0] = 0x00000000;
    pattern1[1] = 0xFFFFFFFF;
    pattern1[2] = 0xA5A5A5A5;
    pattern1[3] = 0x55555555;
    pattern1[4] = 0x33333333;
    pattern1[5] = 0xF0F0F0F0;
    pattern1[6] = 0x00000000;
    pattern1[7] = 0xFFFFFFFF;
    pattern1[8] = 0xA5A5A5A5;
    pattern1[9] = 0x55555555;
    pattern1[10] = 0x33333333;
    pattern1[11] = 0xF0F0F0F0;

    pattern2[0] = 0x00000000;
    pattern2[1] = 0xFFFFFFFF;
    pattern2[2] = 0x5A5A5A5A;
    pattern2[3] = 0xAAAAAAAA;
    pattern2[4] = 0xCCCCCCCC;
    pattern2[5] = 0x0F0F0F0F;
    pattern2[6] = 0xFFFFFFFF;
    pattern2[7] = 0x00000000;
    pattern2[8] = 0x5A5A5A5A;
    pattern2[9] = 0xAAAAAAAA;
    pattern2[10] = 0xCCCCCCCC;
    pattern2[11] = 0x0F0F0F0F;

    mmxCheck[0] = 0;
    mmxCheck[1] = 0;

    outfile = fopen(logfile,"a+");
    if (outfile == NULL)
    {
        sprintf(writeMsg, "Cannot open results file");
        if (!autoRun) MessageBox(NULL, writeMsg, "ERROR WILL EXIT", MB_ICONWARNING | MB_OK);
        CleanUpAndPostQuit();
        return FALSE;
    }
    hdc = GetDC(mainHWND);
    sprintf(writeMsg, "                          Allocating Memory  ");
    TextOut(hdc, 100, 100, writeMsg, lstrlen(writeMsg));
    ReleaseDC(mainHWND, hdc);
    GdiFlush();    

    local_time();

    fprintf(outfile, "\n #########################################################################\n");
    fprintf(outfile, "                  32 Bit Reliability Test %s\n\n", version);
    fprintf(outfile, "                   Copyright (C) Roy Longbottom 2007\n\n");
    strcpy(writeMsg, " Batch Command ");
    strncat(writeMsg, commandLine, 200);
    fprintf(outfile, " %s\n\n", writeMsg);
    fprintf(outfile, " Test %7d KB, %d seconds per test, %s\n", useMemK, RrunSecs, timeday);

    sprintf(errormsg, " ");   
    xx = (int *)VirtualAlloc(NULL, useMemK*1024+256, MEM_COMMIT, PAGE_READWRITE);
    if (xx == NULL)
    {
        sprintf(writeMsg, "Cannot allocate memory");
        if (!autoRun) MessageBox(NULL, writeMsg, "ERROR WILL EXIT", MB_ICONWARNING | MB_OK);
        fprintf(outfile,"Cannot allocate memory\n\n");
        fflush(outfile);
        fclose(outfile);
        CleanUpAndPostQuit();
        return FALSE;
    }
    findmem();
    runDone = TRUE;    
    passesDone = 0;
    sprintf(testmsgOld, " ");

    if (hasMMX)
    {
        errorp = 0;
        i0Start = 0;
        if (oneTest)
        {
            fprintf(outfile, "  Write/Read ");
        }
        else
        {
            fprintf(outfile, "  Write/Read\n");
        }
        fflush(outfile);
        j1 = 6;
        j2 = 12;
        if (oneTest)
        {
            j1 = 9;
            j2 = 10;
        }
        for (j=j1; j<j2; j++)
        {
            if (runHwnd)    DestroyWindow(runHwnd);
            
            usePattern1 = pattern2[j];   
            usePattern2 = pattern1[j];   
    
            memUsed[0] = useMemK;
            millionBytes = (double) useMemK * 1.024 / 1000;
    
            mempasses = useMemK * 8; // 1024 / 128;
            sprintf(writeMsg, " Write Reliability Test Using 64 bits MMX Instructions");                

            hdc = GetDC(mainHWND);
            TextOut(hdc, 120, 50, writeMsg, lstrlen(writeMsg));

            if (oneTest)
            {
               sprintf(writeMsg, "  One Test Only, Testing %7.1f MB, Pattern  %8.8X              ",
                                     millionBytes, usePattern2);
            }
            else
            {
                sprintf(writeMsg, "  Test %2d of 6, Testing %dKB, Pattern  %8.8X, %d Seconds     ",
                                     j-5, useMemK, usePattern1, RrunSecs);                   
            }
            TextOut(hdc, 80, 100, writeMsg, lstrlen(writeMsg));
            TextOut(hdc, 10, 200, testmsgOld, lstrlen(testmsgOld));
            TextOut(hdc, 120, 300, errormsg, lstrlen(errormsg));
            ReleaseDC(mainHWND, hdc);

            GdiFlush();
            results[j][0] = 0;

            n1Count = 0;
            timeCount = 0;
            do
            {
                n1 = 0;
                start_time();
                do
                {
                    tempPattern = usePattern1;
                    usePattern1 = usePattern2;
                    usePattern2 = tempPattern;
                    xx[0]   = usePattern1;
                    xx[1]   = usePattern1;
                    xx[2]   = usePattern1;
                    xx[3]   = usePattern1;
                    xx[4]   = usePattern1;
                    xx[5]   = usePattern1;
                    xx[6]   = usePattern1;
                    xx[7]   = usePattern1;
                    xx[8]   = usePattern2;
                    xx[9]   = usePattern2;
                    xx[10]  = usePattern2;
                    xx[11]  = usePattern2;
                    xx[12]  = usePattern2;
                    xx[13]  = usePattern2;
                    xx[14]  = usePattern2;
                    xx[15]  = usePattern2;
                    writemmx();
                    checkData();
                    n1 = n1 + 1;
                    end_time();
                }
                while (secs < 1.0 && errors == 0);
                n1Count = n1Count + (double)n1;
                timeCount = timeCount + secs;
                sprintf(writeMsg, "  Running %6.1f Seconds, %6.0f MB/Second                 ",
                            timeCount, (millionBytes * 2 * (double)n1 / secs));

                hdc = GetDC(mainHWND);
                TextOut(hdc, 130, 150, writeMsg, lstrlen(writeMsg));
                sprintf(writeMsg, "  Press ESC to exit program");
                TextOut(hdc, 160, 250, writeMsg, lstrlen(writeMsg));
                ReleaseDC(mainHWND, hdc);
                GdiFlush();

                if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
                {
                    fprintf(outfile, "\nESCAPE Pressed\n\n");
                    VirtualFree(xx, 0, MEM_RELEASE);
                    fflush(outfile);
                    fclose(outfile);
                    CleanUpAndPostQuit();
                    return FALSE;
                }
            }
            while (timeCount < (double)RrunSecs && errors == 0);
            results[j][0] = millionBytes * 2 * n1Count / timeCount;
            sprintf(patternSB, "%8.8X%8.8X", usePattern1, usePattern1);
            if (errors == 0)
            {
                 sprintf(testmsg[j], " Pattern %s %c Result OK %9.0f passes", patternSB, 9, n1Count);
            }
            else
            {
                sprintf(testmsg[j], " Pattern %s %c ERROR            ", patternSB);
            }
            sprintf(testmsgOld, " Last test %s %6.0f MB/sec                              ",
                                    testmsg[j], results[j][0]);
            if (oneTest)
            {
                fprintf(outfile, " %7.1f Seconds %7.1f MB x %d passes x 2 (M = 1,000,000)\n", timeCount, millionBytes, (int)n1Count);
                fprintf(outfile, " %7.0f MB/sec %s\n", results[j][0], testmsg[j]);
            }
            else
            {
                fprintf(outfile, " %2d %6.0f MB/sec %s\n", j-5, results[j][0], testmsg[j]);
            }
            if (errors > 0)
            {
                fprintf(outfile, " %dK 4 byte words checked and %d errors found\n", useMemK/4, errors);
                if (errors < 12)
                {
                    fprintf(outfile, " %d errors\n", errord);
                }
                else
                {
                    fprintf(outfile, " First 12 errors\n");
                } 
                for (i=0; i<errord; i++)
                {
                    fprintf(outfile, " Pattern %8.8X Was %8.8X Word %d\n", sbdata[i], isdata[i], errword[i]);
                }
                sprintf(errormsg, "      ERRORS - See %s logfile ", logfile);
            }
        }
        endSecs3 = 9999999;
        endSecs0 = 9999999;
        passesDone = 0;
        j1 = 0;
        j2 = 6;
        if (oneTest)
        {
            j1 = 7;
        }
        else
        {
            fprintf(outfile, " Read\n");
        }
        for (j=j1; j<j2; j++)
        {
            if (runHwnd)    DestroyWindow(runHwnd);
            
            usePattern1 = pattern1[j];   
            usePattern2 = pattern2[j];   
            
            memUsed[0] = useMemK;
            millionBytes = (double) useMemK * 1.024 / 1000;
    
            sprintf(writeMsg, "                             Loading Pattern           "
                              "                                                       ");
            hdc = GetDC(mainHWND);
            TextOut(hdc, 80, 100, writeMsg, lstrlen(writeMsg));
            ReleaseDC(mainHWND, hdc);
            GdiFlush();
    
            start_time();

            xx[0]   = usePattern1;
            xx[1]   = usePattern1;
            xx[2]   = usePattern1;
            xx[3]   = usePattern1;
            xx[4]   = usePattern1;
            xx[5]   = usePattern1;
            xx[6]   = usePattern1;
            xx[7]   = usePattern1;
            xx[8]   = usePattern2;
            xx[9]   = usePattern2;
            xx[10]  = usePattern2;
            xx[11]  = usePattern2;
            xx[12]  = usePattern2;
            xx[13]  = usePattern2;
            xx[14]  = usePattern2;
            xx[15]  = usePattern2;

            mempasses = useMemK * 8; // 1024 / 128;
            writemmx();
            checkData();

            end_time();
            if (secs < endSecs3) endSecs3 = secs;

            if (errors > 0)
            {
                fprintf(outfile, "    ERROR found checking data after generation - Test %d\n", j+1);
                fprintf(outfile, " %dK 4 byte words checked and %d errors found\n", useMemK/4, errors);
                if (errors < 12)
                {
                    fprintf(outfile, " %d errors\n", errord);
                }
                else
                {
                    fprintf(outfile, " First 12 errors\n");
                } 
                for (i=0; i<errord; i++)
                {
                    fprintf(outfile, " Pattern %8.8X Was %8.8X Word %d\n", sbdata[i], isdata[i], errword[i]);
                }
                sprintf(errormsg, "      ERRORS - See %s logfile ", logfile);
            }
            
            sprintf(writeMsg, " Read Reliability Test Using 64 bits MMX Instructions");                

            hdc = GetDC(mainHWND);
            TextOut(hdc, 120, 50, writeMsg, lstrlen(writeMsg));

            sprintf(writeMsg, "  Test %2d of 6, Testing %dKB, Pattern  %8.8X, %d Seconds     ",
                                 j+1, useMemK, usePattern1, RrunSecs);                   
            TextOut(hdc, 80, 100, writeMsg, lstrlen(writeMsg));
            TextOut(hdc, 10, 200, testmsgOld, lstrlen(testmsgOld));
            TextOut(hdc, 120, 300, errormsg, lstrlen(errormsg));
            ReleaseDC(mainHWND, hdc);
            GdiFlush();
    
            // 8 byte inc MMX 8 reg ADD & SUBTRACT ****************************  
    
            results[j][0] = 0;

            passbytes = 128;
            mempasses = useMemK * 1024 / passbytes;

            outerLoop = 1;
            start_time();
            mmxRun();
            end_time();
            outerLoop = 100;
            if (secs > 0.001) outerLoop = (int)(0.1/secs);
            if (outerLoop < 1) outerLoop = 1;

            n1Count = 0;
            timeCount = 0;
            do
            {
                n1 = 0;
                start_time();
                do
                {
                    mmxRun();
                    n1 = n1 + 1;
                    end_time();
                }
                while (secs < 1.0);
                n1Count = n1Count + (double)n1;
                timeCount = timeCount + secs;
                sprintf(writeMsg, "  Running %6.1f Seconds, %6.0f MB/Second                 ",
                            timeCount, (millionBytes * outerLoop * (double)n1 / secs));

                hdc = GetDC(mainHWND);
                TextOut(hdc, 130, 150, writeMsg, lstrlen(writeMsg));
                sprintf(writeMsg, "  Press ESC to exit program");
                TextOut(hdc, 160, 250, writeMsg, lstrlen(writeMsg));
                ReleaseDC(mainHWND, hdc);
                GdiFlush();

                if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
                {
                    fprintf(outfile, "\nESCAPE Pressed\n\n");
                    VirtualFree(xx, 0, MEM_RELEASE);
                    fflush(outfile);
                    fclose(outfile);
                    CleanUpAndPostQuit();
                    return FALSE;
                }
            }
            while (timeCount < (double)RrunSecs);
             
            results[j][0] = millionBytes * outerLoop * n1Count / timeCount;
            sprintf(patternSB, "%8.8X%8.8X", usePattern1, usePattern1);
            sprintf(testmsg[j], " Pattern %s %c Result OK %9.0f passes", patternSB, 9, n1Count * (double)outerLoop);
            if (strcmp(patternSB, patternIs) != 0)
            {
                sprintf(testmsg[j], " Pattern %s %c ERROR Was %s", patternSB, 9, patternIs);
                errorp = 1;
            }
            sprintf(testmsgOld, " Last test %s %6.0f MB/sec                              ",
                                    testmsg[j], results[j][0]);
            fprintf(outfile, " %2d %6.0f MB/sec %s\n", j+1, results[j][0], testmsg[j]);
            
            i0Start = 2;
            start_time();
            checkData();
            end_time();
            if (secs < endSecs0) endSecs0 = secs;
            if (errors == 0)
            {
                if (errorp > 0)
                {
                    fprintf(outfile, " %dK 4 byte words checked but no errors found\n", useMemK/4);
                }
            }
            else
            {
                if (errorp == 0)
                {
                    fprintf(outfile, " No Errors in Reliability/Speed Test FAILED ON END COMPARE\n");
                }
                fprintf(outfile, " %dK 4 byte words checked and %d errors found\n", useMemK/4, errors);
                if (errors < 12)
                {
                    fprintf(outfile, " %d errors\n", errord);
                }
                else
                {
                    fprintf(outfile, " First 12 errors\n");
                } 
                for (i=0; i<errord; i++)
                {
                    fprintf(outfile, " Pattern %8.8X Was %8.8X Word %d\n", sbdata[i], isdata[i], errword[i]);
                }
            }

            if (errors > 0)
            {
                sprintf(errormsg, "      ERRORS - See %s logfile ", logfile);
            }
            passesDone = j + 1;
    
//            if (runHwnd)    DestroyWindow(runHwnd);
//            runHwnd = CreateDialog( MyInstance,"DIALOG_9", mainHWND, (DLGPROC)RunPanel);        
        }
    }
    else
    {
        fprintf(outfile, " Cannot Run - No MMX Facilities\n");
    }
    if (!oneTest)
    {
        fprintf(outfile, "\n");
        fprintf(outfile, " Minimum seconds each test to generate/check data %7.3f, compare at end %7.3f\n", endSecs3, endSecs0);
    }
    fprintf(outfile, "\n");
    local_time();
    fprintf(outfile, "             Reliability Test Ended %s", timeday);
    fprintf(outfile, "\n");
    WhatConfig();
    fprintf(outfile," %s\n", configData1);
    fprintf(outfile," %s\n", configData2);
    fprintf(outfile," %s, at end %d KB\n", startRam, freesize / 1024);        
    fprintf(outfile, "\n");
    fflush(outfile);
    fclose(outfile);
    VirtualFree(xx, 0, MEM_RELEASE);
    doTesting = FALSE;
    if (!autoRun) displayWhatever(mainHWND);

    hdc = GetDC(mainHWND);
    Rectangle(hdc, winRect.left, winRect.top,
                   winRect.right, winRect.bottom);
    ReleaseDC(mainHWND, hdc);

    return TRUE;    
}

BOOL runTests()
{
    int useMem;   
    int i, m, j;
    double wordinc;
    int pattern1 = 0xA5A5A5A5;
    int pattern2 = 0x5A5A5A5A;
    int usePattern1;
    double millionBytes;

    HDC  hdc;
        
    FILE    *outfile;

    errorFound = FALSE;
    useMem = allocMem[Pruns - 1];    

    hdc = GetDC(mainHWND);
    sprintf(writeMsg, "                          Allocating Memory  ");
    TextOut(hdc, 100, 100, writeMsg, lstrlen(writeMsg));    
    ReleaseDC(mainHWND, hdc);


    outfile = fopen(logfile,"a+");
    if (outfile == NULL)
    {
        sprintf(writeMsg, "Cannot open results file");
        if (!autoRun) MessageBox(NULL, writeMsg, "ERROR WILL EXIT", MB_ICONWARNING | MB_OK);
        CleanUpAndPostQuit();
        return FALSE;
    }

    local_time();    
    fprintf(outfile, "\n #########################################################################\n");
    fprintf(outfile, "         Windows Bus Speed Test %s by Roy Longbottom\n", version);
    fprintf(outfile, "\n Mov/AND 4 bytes Integer words and 8 bytes MMX words from cache/RAM via CPU\n");        
    fprintf(outfile, " to 1, 2 or 8 registers. MovI address byte increments > Inc4 show effects\n");        
    fprintf(outfile, " of burst reads, Real data rate might be 2 to 16 times faster than shown.\n");
    fprintf(outfile, " Reg1 vs Reg2 can show pipeline effects as can MMX MovM move data to 1 vs 8\n");
    fprintf(outfile, " registers. MB/S = 1000000's bytes per second for comparison with CPU MHz.\n");

    fprintf(outfile, "\n  Minimum %10.3f seconds per test, Start %s\n", PrunSecs, timeday);
    if (xoffset > 0)
        fprintf(outfile, "  Data accessed %d bytes offset from word boundary\n\n", xoffset);

    fprintf(outfile, "          MovI  MovI  MovI  MovI  MovI  MovI  AndI  AndI  MovM  MovM\n");   
    fprintf(outfile, "  Memory  Reg2  Reg2  Reg2  Reg2  Reg1  Reg2  Reg1  Reg2  Reg1  Reg8\n");
    fprintf(outfile, "  KBytes Inc64 Inc32 Inc16  Inc8  Inc4  Inc4  Inc4  Inc4  Inc8  Inc8\n");
    fprintf(outfile, "   Used   MB/S  MB/S  MB/S  MB/S  MB/S  MB/S  MB/S  MB/S  MB/S  MB/S\n\n");

    xx = (int *)VirtualAlloc(NULL, useMem+256, MEM_COMMIT, PAGE_READWRITE);
    if (xx == NULL)
    {
        sprintf(writeMsg, "Cannot allocate memory");
        if (!autoRun) MessageBox(NULL, writeMsg, "ERROR WILL EXIT", MB_ICONWARNING | MB_OK);
        fprintf(outfile,"Cannot allocate memory\n\n");
        fflush(outfile);
        fclose(outfile);
        CleanUpAndPostQuit();
        return FALSE;
    }
    findmem();

    for (m=0; m<useMem/4+32; m++)
    {
       xx[m] = 0;
    }          

    runDone = TRUE;    
    passesDone = 0;
 
    sprintf(writeMsg, "                           Running Tests                    ");

    hdc = GetDC(mainHWND);
    TextOut(hdc, 100, 100, writeMsg, lstrlen(writeMsg));    
    ReleaseDC(mainHWND, hdc);

    if (runHwnd)    DestroyWindow(runHwnd);
    runHwnd = CreateDialog( MyInstance,"DIALOG_9", mainHWND, (DLGPROC)RunPanel);

    usePattern1 = pattern1;
           
    for (j=0; j<Pruns; j++)
    {   
        
        memUsed[j] = allocMem[j] / 1024;
        millionBytes = (double) allocMem[j] / 1000 / 1000;

        for (m=0; m<allocMem[j]/4+32; m++)
        {
           xx[m] = usePattern1;
        }                 

        // 64 byte inc *******************************  

        n1 = 1;
        wordinc = 16;
        passbytes = 4096;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem64();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][0] = millionBytes / wordinc * (double)n1 / secs;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 32 byte inc *******************************  

        n1 = 1;
        wordinc = 8;
        passbytes = 2048;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem32();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][1] = millionBytes / wordinc * (double)n1 / secs;;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 16 byte inc *******************************  

        n1 = 1;
        wordinc = 4;
        passbytes = 1024;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem16();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][2] = millionBytes / wordinc * (double)n1 / secs;;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 8 byte inc *******************************  

        n1 = 1;
        wordinc = 2;
        passbytes = 512;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem8();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][3] = millionBytes / wordinc * (double)n1 / secs;;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 4 byte inc mov 1 reg ****************************  

        n1 = 1;
        wordinc = 1;
        passbytes = 256;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem4();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][4] = millionBytes / wordinc * (double)n1 / secs;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 4 byte inc mov 2 reg ****************************  

        n1 = 1;
        wordinc = 1;
        passbytes = 256;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 readmem4b();
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][5] = millionBytes / wordinc * (double)n1 / secs;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }

        // 4 byte inc and 1 reg ****************************  

        n1 = 1;
        wordinc = 1;
        passbytes = 256;
        mempasses = allocMem[j] / passbytes;
        result1 = usePattern1;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 checkmem2();             
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][6] = millionBytes / wordinc * (double)n1 / secs;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }
        
        // 4 byte inc and 2 reg ****************************  

        n1 = 1;
        wordinc = 1;
        passbytes = 256;
        mempasses = allocMem[j] / passbytes;
        do
        {
            start_time();
            for (i=0; i<n1; i++)
            {
                 checkmem2b();             
            }
            end_time();
            checkTime();
        }
        while (secs < PrunSecs);
     
        results[j][7] = millionBytes / wordinc * (double)n1 / secs;
        if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
        {
            fprintf(outfile, "\n\n\n");
            VirtualFree(xx, 0, MEM_RELEASE);
            fflush(outfile);
            fclose(outfile);
            CleanUpAndPostQuit();
            return FALSE;
        }
        if (xoffset == 0)
        {
            if (result1 != usePattern1)
            {
               sprintf(writeMsg, "Expected 0x%8.8lx Obtained 0x%8.8lx", usePattern1, result1);
               if (!autoRun) MessageBox(NULL, writeMsg, "DATA READERROR", MB_ICONWARNING | MB_OK);
               logErrors(usePattern1, result1, memUsed[j]);
               errorFound = TRUE;
            }
        }
        
        // 8 byte inc MMX 1 reg ****************************  

        results[j][8] = 0;
        if (hasMMX)
        {
            n1 = 1;
            wordinc = 1;
            passbytes = 4096;
            mempasses = allocMem[j] / passbytes;
            do
            {
                start_time();
                for (i=0; i<n1; i++)
                {
                   readmmx1(); 
                }
                end_time();
                checkTime();
            }
            while (secs < PrunSecs);
         
            results[j][8] = millionBytes * (double)n1 / secs;
            if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
            {
                fprintf(outfile, "\n\n\n");
                VirtualFree(xx, 0, MEM_RELEASE);
                fflush(outfile);
                fclose(outfile);
                CleanUpAndPostQuit();
                return FALSE;
            }
        }
        
        // 8 byte inc MMX 8 reg ****************************  

        results[j][9] = 0;
        if (hasMMX)
        {
            n1 = 1;
            wordinc = 1;
            passbytes = 4096;
            mempasses = allocMem[j] / passbytes;
            do
            {
                start_time();
                for (i=0; i<n1; i++)
                {
                   readmmx8(); 
                }
                end_time();
                checkTime();
            }
            while (secs < PrunSecs);
         
            results[j][9] = millionBytes * (double)n1 / secs;
            if (GetAsyncKeyState(VK_ESCAPE) != keyPress)
            {
                fprintf(outfile, "\n\n\n");
                VirtualFree(xx, 0, MEM_RELEASE);
                fflush(outfile);
                fclose(outfile);
                CleanUpAndPostQuit();
                return FALSE;
            }
        }
        
        passesDone = j + 1;

        if (usePattern1 == pattern1)
        {
            usePattern1 = pattern2;
        }
        else
        {
            usePattern1 = pattern1;
        }

        if (runHwnd)    DestroyWindow(runHwnd);
        runHwnd = CreateDialog( MyInstance,"DIALOG_9", mainHWND, (DLGPROC)RunPanel);

        fprintf(outfile, "%7d %6.0f%6.0f%6.0f", memUsed[j],
                                              results[j][0], results[j][1], results[j][2]);
        fprintf(outfile, "%6.0f%6.0f%6.0f",   results[j][3], results[j][4], results[j][5]);
        fprintf(outfile, "%6.0f%6.0f%6.0f",   results[j][6], results[j][7], results[j][8]);
        fprintf(outfile, "%6.0f\n",           results[j][9]);
        fflush(outfile);
    }
    if (errorFound) fprintf(outfile, "\n\n ***************** ERRORS see ERRORLog.txt ******************\n\n"); 
    local_time();
    WhatConfig();
    if (autoRun) DestroyWindow(runHwnd);

    fprintf(outfile, "\n                  End of test %s\n", timeday);
    fprintf(outfile," %s\n", configData1);
    fprintf(outfile," %s\n", configData2);
    fprintf(outfile," %s, at end %d KB\n", startRam, freesize / 1024);        

    fprintf(outfile,"\n\n");

    fflush(outfile);
    fclose(outfile);
    VirtualFree(xx, 0, MEM_RELEASE);
    doTesting = FALSE;
    if (!autoRun) displayWhatever(mainHWND);                                      

    hdc = GetDC(mainHWND);
    Rectangle(hdc, winRect.left, winRect.top,
                   winRect.right, winRect.bottom);
    ReleaseDC(mainHWND, hdc);

    return TRUE;
    
} // runTests


void checkTime()
{
    if (secs < PrunSecs)
    {
          if (secs < PrunSecs / 8.0)
          {
                n1 = n1 * 10;
          }
          else
          {
                n1 = (int)(PrunSecs * 1.25 / secs * (double)n1 + 1);
          }
    }
}


void checkData()
{
    int i, m;

    sumCheck[0] = usePattern1;
    sumCheck[1] = usePattern1;
    sumCheck[2] = usePattern2;
    sumCheck[3] = usePattern2;

    mempasses = useMemK * 8; // 1024 / 128;            
    errorcheck();

    errors = 0;
    errord = 0;

    if (sumCheck[0] != usePattern1 || sumCheck[1] != usePattern1 ||
        sumCheck[2] != usePattern1 || sumCheck[3] != usePattern1 ||
        sumCheck[4] != usePattern2 || sumCheck[5] != usePattern2 ||
        sumCheck[6] != usePattern2 || sumCheck[7] != usePattern2 || errorp == 1)
    {
        for (m=0; m<useMemK*256; m=m+16)
        {
           if (sumCheck[0] != usePattern1 || sumCheck[1] != usePattern1 ||
               sumCheck[2] != usePattern1 || sumCheck[3] != usePattern1 || errorp == 1)
           {    
               for (i=i0Start; i<8; i++)
               {
                  if (xx[m+i] != usePattern1)
                  {
                      errors = errors + 1;
                      if (errors < 13)
                      {
                          isdata[errord] = xx[m+i];
                          sbdata[errord] = usePattern1;
                          errword[errord] = m+i;
                          errord = errord + 1;
                      }
                  }
               }
           }
           i0Start = 0;
           if (sumCheck[4] != usePattern2 || sumCheck[5] != usePattern2 ||
               sumCheck[6] != usePattern2 || sumCheck[7] != usePattern2 || errorp == 1) 
           {
               for (i=0; i<8; i++)
               {
                  if (xx[m+i+8] != usePattern2)
                  {
                      errors = errors + 1;
                      if (errors < 13)
                      {
                          isdata[errord] = xx[m+i+8];
                          sbdata[errord] = usePattern2;
                          errword[errord] = m+i+8;
                          errord = errord + 1;
                      }
                  }
               }
           }
        }
    }    
}

inline void findmem()
{
     __asm
    {
        lea   eax,xaddress
        mov   edx,xx
        lea   ebx,[edx]
        mov   [eax],ebx
    }
}                         

inline void readmmx1() 
{
  __asm
 {
    mov     eax,xx
    mov     edx,mempasses
    mov     ecx,xoffset
    add     eax,ecx   
 lp:movq    mm0,[eax]      
    movq    mm0,[eax+8]    
    movq    mm0,[eax+16]   
    movq    mm0,[eax+24]   
    movq    mm0,[eax+32]   
    movq    mm0,[eax+40]   
    movq    mm0,[eax+48]   
    movq    mm0,[eax+56]   
    movq    mm0,[eax+64]   
    movq    mm0,[eax+72]   
    movq    mm0,[eax+80]   
    movq    mm0,[eax+88]   
    movq    mm0,[eax+96]   
    movq    mm0,[eax+104]   
    movq    mm0,[eax+112]   
    movq    mm0,[eax+120]   
    movq    mm0,[eax+128]   
    movq    mm0,[eax+136]   
    movq    mm0,[eax+144]   
    movq    mm0,[eax+152]   
    movq    mm0,[eax+160]   
    movq    mm0,[eax+168]   
    movq    mm0,[eax+176]   
    movq    mm0,[eax+184]   
    movq    mm0,[eax+192]   
    movq    mm0,[eax+200]   
    movq    mm0,[eax+208]   
    movq    mm0,[eax+216]   
    movq    mm0,[eax+224]   
    movq    mm0,[eax+232]   
    movq    mm0,[eax+240]   
    movq    mm0,[eax+248]   
    movq    mm0,[eax+256]   
    movq    mm0,[eax+264]   
    movq    mm0,[eax+272]   
    movq    mm0,[eax+280]   
    movq    mm0,[eax+288]   
    movq    mm0,[eax+296]   
    movq    mm0,[eax+304]   
    movq    mm0,[eax+312]   
    movq    mm0,[eax+320]   
    movq    mm0,[eax+328]   
    movq    mm0,[eax+336]   
    movq    mm0,[eax+344]   
    movq    mm0,[eax+352]   
    movq    mm0,[eax+360]   
    movq    mm0,[eax+368]   
    movq    mm0,[eax+376]   
    movq    mm0,[eax+384]   
    movq    mm0,[eax+392]   
    movq    mm0,[eax+400]   
    movq    mm0,[eax+408]   
    movq    mm0,[eax+416]   
    movq    mm0,[eax+424]   
    movq    mm0,[eax+432]   
    movq    mm0,[eax+440]   
    movq    mm0,[eax+448]   
    movq    mm0,[eax+456]   
    movq    mm0,[eax+464]   
    movq    mm0,[eax+472]   
    movq    mm0,[eax+480]   
    movq    mm0,[eax+488]   
    movq    mm0,[eax+496]   
    movq    mm0,[eax+504]   
    movq    mm0,[eax+512]   
    movq    mm0,[eax+520]   
    movq    mm0,[eax+528]   
    movq    mm0,[eax+536]   
    movq    mm0,[eax+544]   
    movq    mm0,[eax+552]   
    movq    mm0,[eax+560]   
    movq    mm0,[eax+568]   
    movq    mm0,[eax+576]   
    movq    mm0,[eax+584]   
    movq    mm0,[eax+592]   
    movq    mm0,[eax+600]   
    movq    mm0,[eax+608]   
    movq    mm0,[eax+616]   
    movq    mm0,[eax+624]   
    movq    mm0,[eax+632]   
    movq    mm0,[eax+640]   
    movq    mm0,[eax+648]   
    movq    mm0,[eax+656]   
    movq    mm0,[eax+664]   
    movq    mm0,[eax+672]   
    movq    mm0,[eax+680]   
    movq    mm0,[eax+688]   
    movq    mm0,[eax+696]   
    movq    mm0,[eax+704]   
    movq    mm0,[eax+712]   
    movq    mm0,[eax+720]   
    movq    mm0,[eax+728]   
    movq    mm0,[eax+736]   
    movq    mm0,[eax+744]   
    movq    mm0,[eax+752]   
    movq    mm0,[eax+760]   
    movq    mm0,[eax+768]   
    movq    mm0,[eax+776]   
    movq    mm0,[eax+784]   
    movq    mm0,[eax+792]   
    movq    mm0,[eax+800]   
    movq    mm0,[eax+808]   
    movq    mm0,[eax+816]   
    movq    mm0,[eax+824]   
    movq    mm0,[eax+832]   
    movq    mm0,[eax+840]   
    movq    mm0,[eax+848]   
    movq    mm0,[eax+856]   
    movq    mm0,[eax+864]   
    movq    mm0,[eax+872]   
    movq    mm0,[eax+880]   
    movq    mm0,[eax+888]   
    movq    mm0,[eax+896]   
    movq    mm0,[eax+904]   
    movq    mm0,[eax+912]   
    movq    mm0,[eax+920]   
    movq    mm0,[eax+928]   
    movq    mm0,[eax+936]   
    movq    mm0,[eax+944]   
    movq    mm0,[eax+952]   
    movq    mm0,[eax+960]   
    movq    mm0,[eax+968]   
    movq    mm0,[eax+976]   
    movq    mm0,[eax+984]   
    movq    mm0,[eax+992]   
    movq    mm0,[eax+1000]   
    movq    mm0,[eax+1008]   
    movq    mm0,[eax+1016]    
    movq    mm0,[eax+1024]   
    movq    mm0,[eax+1032]   
    movq    mm0,[eax+1040]   
    movq    mm0,[eax+1048]   
    movq    mm0,[eax+1056]   
    movq    mm0,[eax+1064]   
    movq    mm0,[eax+1072]   
    movq    mm0,[eax+1080]   
    movq    mm0,[eax+1088]   
    movq    mm0,[eax+1096]   
    movq    mm0,[eax+1104]   
    movq    mm0,[eax+1112]   
    movq    mm0,[eax+1120]   
    movq    mm0,[eax+1128]   
    movq    mm0,[eax+1136]   
    movq    mm0,[eax+1144]   
    movq    mm0,[eax+1152]   
    movq    mm0,[eax+1160]   
    movq    mm0,[eax+1168]   
    movq    mm0,[eax+1176]   
    movq    mm0,[eax+1184]   
    movq    mm0,[eax+1192]   
    movq    mm0,[eax+1200]   
    movq    mm0,[eax+1208]   
    movq    mm0,[eax+1216]   
    movq    mm0,[eax+1224]   
    movq    mm0,[eax+1232]   
    movq    mm0,[eax+1240]   
    movq    mm0,[eax+1248]   
    movq    mm0,[eax+1256]   
    movq    mm0,[eax+1264]   
    movq    mm0,[eax+1272]   
    movq    mm0,[eax+1280]   
    movq    mm0,[eax+1288]   
    movq    mm0,[eax+1296]   
    movq    mm0,[eax+1304]   
    movq    mm0,[eax+1312]   
    movq    mm0,[eax+1320]   
    movq    mm0,[eax+1328]   
    movq    mm0,[eax+1336]   
    movq    mm0,[eax+1344]   
    movq    mm0,[eax+1352]   
    movq    mm0,[eax+1360]   
    movq    mm0,[eax+1368]   
    movq    mm0,[eax+1376]   
    movq    mm0,[eax+1384]   
    movq    mm0,[eax+1392]   
    movq    mm0,[eax+1400]   
    movq    mm0,[eax+1408]   
    movq    mm0,[eax+1416]   
    movq    mm0,[eax+1424]   
    movq    mm0,[eax+1432]   
    movq    mm0,[eax+1440]   
    movq    mm0,[eax+1448]   
    movq    mm0,[eax+1456]   
    movq    mm0,[eax+1464]   
    movq    mm0,[eax+1472]   
    movq    mm0,[eax+1480]   
    movq    mm0,[eax+1488]   
    movq    mm0,[eax+1496]   
    movq    mm0,[eax+1504]   
    movq    mm0,[eax+1512]   
    movq    mm0,[eax+1520]   
    movq    mm0,[eax+1528]   
    movq    mm0,[eax+1536]   
    movq    mm0,[eax+1544]   
    movq    mm0,[eax+1552]   
    movq    mm0,[eax+1560]   
    movq    mm0,[eax+1568]   
    movq    mm0,[eax+1576]   
    movq    mm0,[eax+1584]   
    movq    mm0,[eax+1592]   
    movq    mm0,[eax+1600]   
    movq    mm0,[eax+1608]   
    movq    mm0,[eax+1616]   
    movq    mm0,[eax+1624]   
    movq    mm0,[eax+1632]   
    movq    mm0,[eax+1640]   
    movq    mm0,[eax+1648]   
    movq    mm0,[eax+1656]   
    movq    mm0,[eax+1664]   
    movq    mm0,[eax+1672]   
    movq    mm0,[eax+1680]   
    movq    mm0,[eax+1688]   
    movq    mm0,[eax+1696]   
    movq    mm0,[eax+1704]   
    movq    mm0,[eax+1712]   
    movq    mm0,[eax+1720]   
    movq    mm0,[eax+1728]   
    movq    mm0,[eax+1736]   
    movq    mm0,[eax+1744]   
    movq    mm0,[eax+1752]   
    movq    mm0,[eax+1760]   
    movq    mm0,[eax+1768]   
    movq    mm0,[eax+1776]   
    movq    mm0,[eax+1784]   
    movq    mm0,[eax+1792]   
    movq    mm0,[eax+1800]   
    movq    mm0,[eax+1808]   
    movq    mm0,[eax+1816]   
    movq    mm0,[eax+1824]   
    movq    mm0,[eax+1832]   
    movq    mm0,[eax+1840]   
    movq    mm0,[eax+1848]   
    movq    mm0,[eax+1856]   
    movq    mm0,[eax+1864]   
    movq    mm0,[eax+1872]   
    movq    mm0,[eax+1880]   
    movq    mm0,[eax+1888]   
    movq    mm0,[eax+1896]   
    movq    mm0,[eax+1904]   
    movq    mm0,[eax+1912]   
    movq    mm0,[eax+1920]   
    movq    mm0,[eax+1928]   
    movq    mm0,[eax+1936]   
    movq    mm0,[eax+1944]   
    movq    mm0,[eax+1952]   
    movq    mm0,[eax+1960]   
    movq    mm0,[eax+1968]   
    movq    mm0,[eax+1976]   
    movq    mm0,[eax+1984]   
    movq    mm0,[eax+1992]   
    movq    mm0,[eax+2000]   
    movq    mm0,[eax+2008]   
    movq    mm0,[eax+2016]   
    movq    mm0,[eax+2024]   
    movq    mm0,[eax+2032]   
    movq    mm0,[eax+2040]   
    movq    mm0,[eax+2048]   
    movq    mm0,[eax+2056]   
    movq    mm0,[eax+2064]   
    movq    mm0,[eax+2072]   
    movq    mm0,[eax+2080]   
    movq    mm0,[eax+2088]   
    movq    mm0,[eax+2096]   
    movq    mm0,[eax+2104]   
    movq    mm0,[eax+2112]   
    movq    mm0,[eax+2120]   
    movq    mm0,[eax+2128]   
    movq    mm0,[eax+2136]   
    movq    mm0,[eax+2144]   
    movq    mm0,[eax+2152]   
    movq    mm0,[eax+2160]   
    movq    mm0,[eax+2168]   
    movq    mm0,[eax+2176]   
    movq    mm0,[eax+2184]   
    movq    mm0,[eax+2192]   
    movq    mm0,[eax+2200]   
    movq    mm0,[eax+2208]   
    movq    mm0,[eax+2216]   
    movq    mm0,[eax+2224]   
    movq    mm0,[eax+2232]   
    movq    mm0,[eax+2240]   
    movq    mm0,[eax+2248]   
    movq    mm0,[eax+2256]   
    movq    mm0,[eax+2264]   
    movq    mm0,[eax+2272]   
    movq    mm0,[eax+2280]   
    movq    mm0,[eax+2288]   
    movq    mm0,[eax+2296]   
    movq    mm0,[eax+2304]   
    movq    mm0,[eax+2312]   
    movq    mm0,[eax+2320]   
    movq    mm0,[eax+2328]   
    movq    mm0,[eax+2336]   
    movq    mm0,[eax+2344]   
    movq    mm0,[eax+2352]   
    movq    mm0,[eax+2360]   
    movq    mm0,[eax+2368]   
    movq    mm0,[eax+2376]   
    movq    mm0,[eax+2384]   
    movq    mm0,[eax+2392]   
    movq    mm0,[eax+2400]   
    movq    mm0,[eax+2408]   
    movq    mm0,[eax+2416]   
    movq    mm0,[eax+2424]   
    movq    mm0,[eax+2432]   
    movq    mm0,[eax+2440]   
    movq    mm0,[eax+2448]   
    movq    mm0,[eax+2456]   
    movq    mm0,[eax+2464]   
    movq    mm0,[eax+2472]   
    movq    mm0,[eax+2480]   
    movq    mm0,[eax+2488]   
    movq    mm0,[eax+2496]   
    movq    mm0,[eax+2504]   
    movq    mm0,[eax+2512]   
    movq    mm0,[eax+2520]   
    movq    mm0,[eax+2528]   
    movq    mm0,[eax+2536]   
    movq    mm0,[eax+2544]   
    movq    mm0,[eax+2552]   
    movq    mm0,[eax+2560]   
    movq    mm0,[eax+2568]   
    movq    mm0,[eax+2576]   
    movq    mm0,[eax+2584]   
    movq    mm0,[eax+2592]   
    movq    mm0,[eax+2600]   
    movq    mm0,[eax+2608]   
    movq    mm0,[eax+2616]   
    movq    mm0,[eax+2624]   
    movq    mm0,[eax+2632]   
    movq    mm0,[eax+2640]   
    movq    mm0,[eax+2648]   
    movq    mm0,[eax+2656]   
    movq    mm0,[eax+2664]   
    movq    mm0,[eax+2672]   
    movq    mm0,[eax+2680]   
    movq    mm0,[eax+2688]   
    movq    mm0,[eax+2696]   
    movq    mm0,[eax+2704]   
    movq    mm0,[eax+2712]   
    movq    mm0,[eax+2720]   
    movq    mm0,[eax+2728]   
    movq    mm0,[eax+2736]   
    movq    mm0,[eax+2744]   
    movq    mm0,[eax+2752]   
    movq    mm0,[eax+2760]   
    movq    mm0,[eax+2768]   
    movq    mm0,[eax+2776]   
    movq    mm0,[eax+2784]   
    movq    mm0,[eax+2792]   
    movq    mm0,[eax+2800]   
    movq    mm0,[eax+2808]   
    movq    mm0,[eax+2816]   
    movq    mm0,[eax+2824]   
    movq    mm0,[eax+2832]   
    movq    mm0,[eax+2840]   
    movq    mm0,[eax+2848]   
    movq    mm0,[eax+2856]   
    movq    mm0,[eax+2864]   
    movq    mm0,[eax+2872]   
    movq    mm0,[eax+2880]   
    movq    mm0,[eax+2888]   
    movq    mm0,[eax+2896]   
    movq    mm0,[eax+2904]   
    movq    mm0,[eax+2912]   
    movq    mm0,[eax+2920]   
    movq    mm0,[eax+2928]   
    movq    mm0,[eax+2936]   
    movq    mm0,[eax+2944]   
    movq    mm0,[eax+2952]   
    movq    mm0,[eax+2960]   
    movq    mm0,[eax+2968]   
    movq    mm0,[eax+2976]   
    movq    mm0,[eax+2984]   
    movq    mm0,[eax+2992]   
    movq    mm0,[eax+3000]   
    movq    mm0,[eax+3008]   
    movq    mm0,[eax+3016]   
    movq    mm0,[eax+3024]   
    movq    mm0,[eax+3032]   
    movq    mm0,[eax+3040]   
    movq    mm0,[eax+3048]   
    movq    mm0,[eax+3056]   
    movq    mm0,[eax+3064]   
    movq    mm0,[eax+3072]   
    movq    mm0,[eax+3080]   
    movq    mm0,[eax+3088]   
    movq    mm0,[eax+3096]   
    movq    mm0,[eax+3104]   
    movq    mm0,[eax+3112]   
    movq    mm0,[eax+3120]   
    movq    mm0,[eax+3128]   
    movq    mm0,[eax+3136]   
    movq    mm0,[eax+3144]   
    movq    mm0,[eax+3152]   
    movq    mm0,[eax+3160]   
    movq    mm0,[eax+3168]   
    movq    mm0,[eax+3176]   
    movq    mm0,[eax+3184]   
    movq    mm0,[eax+3192]   
    movq    mm0,[eax+3200]       
    movq    mm0,[eax+3208]   
    movq    mm0,[eax+3216]   
    movq    mm0,[eax+3224]   
    movq    mm0,[eax+3232]   
    movq    mm0,[eax+3240]   
    movq    mm0,[eax+3248]   
    movq    mm0,[eax+3256]   
    movq    mm0,[eax+3264]   
    movq    mm0,[eax+3272]   
    movq    mm0,[eax+3280]   
    movq    mm0,[eax+3288]   
    movq    mm0,[eax+3296]   
    movq    mm0,[eax+3304]   
    movq    mm0,[eax+3312]   
    movq    mm0,[eax+3320]   
    movq    mm0,[eax+3328]   
    movq    mm0,[eax+3336]   
    movq    mm0,[eax+3344]   
    movq    mm0,[eax+3352]   
    movq    mm0,[eax+3360]   
    movq    mm0,[eax+3368]   
    movq    mm0,[eax+3376]   
    movq    mm0,[eax+3384]   
    movq    mm0,[eax+3392]   
    movq    mm0,[eax+3400]   
    movq    mm0,[eax+3408]   
    movq    mm0,[eax+3416]   
    movq    mm0,[eax+3424]   
    movq    mm0,[eax+3432]   
    movq    mm0,[eax+3440]   
    movq    mm0,[eax+3448]   
    movq    mm0,[eax+3456]   
    movq    mm0,[eax+3464]   
    movq    mm0,[eax+3472]   
    movq    mm0,[eax+3480]   
    movq    mm0,[eax+3488]   
    movq    mm0,[eax+3496]   
    movq    mm0,[eax+3504]   
    movq    mm0,[eax+3512]   
    movq    mm0,[eax+3520]   
    movq    mm0,[eax+3528]   
    movq    mm0,[eax+3536]   
    movq    mm0,[eax+3544]   
    movq    mm0,[eax+3552]   
    movq    mm0,[eax+3560]   
    movq    mm0,[eax+3568]   
    movq    mm0,[eax+3576]   
    movq    mm0,[eax+3584]   
    movq    mm0,[eax+3592]   
    movq    mm0,[eax+3600]   
    movq    mm0,[eax+3608]   
    movq    mm0,[eax+3616]   
    movq    mm0,[eax+3624]   
    movq    mm0,[eax+3632]   
    movq    mm0,[eax+3640]   
    movq    mm0,[eax+3648]   
    movq    mm0,[eax+3656]   
    movq    mm0,[eax+3664]   
    movq    mm0,[eax+3672]   
    movq    mm0,[eax+3680]   
    movq    mm0,[eax+3688]   
    movq    mm0,[eax+3696]   
    movq    mm0,[eax+3704]   
    movq    mm0,[eax+3712]   
    movq    mm0,[eax+3720]   
    movq    mm0,[eax+3728]   
    movq    mm0,[eax+3736]   
    movq    mm0,[eax+3744]   
    movq    mm0,[eax+3752]   
    movq    mm0,[eax+3760]   
    movq    mm0,[eax+3768]   
    movq    mm0,[eax+3776]   
    movq    mm0,[eax+3784]   
    movq    mm0,[eax+3792]   
    movq    mm0,[eax+3800]   
    movq    mm0,[eax+3808]   
    movq    mm0,[eax+3816]   
    movq    mm0,[eax+3824]   
    movq    mm0,[eax+3832]       
    movq    mm0,[eax+3840]   
    movq    mm0,[eax+3848]   
    movq    mm0,[eax+3856]   
    movq    mm0,[eax+3864]   
    movq    mm0,[eax+3872]   
    movq    mm0,[eax+3880]   
    movq    mm0,[eax+3888]   
    movq    mm0,[eax+3896]   
    movq    mm0,[eax+3904]   
    movq    mm0,[eax+3912]   
    movq    mm0,[eax+3920]   
    movq    mm0,[eax+3928]   
    movq    mm0,[eax+3936]   
    movq    mm0,[eax+3944]   
    movq    mm0,[eax+3952]   
    movq    mm0,[eax+3960]   
    movq    mm0,[eax+3968]   
    movq    mm0,[eax+3976]   
    movq    mm0,[eax+3984]   
    movq    mm0,[eax+3992]   
    movq    mm0,[eax+4000]   
    movq    mm0,[eax+4008]   
    movq    mm0,[eax+4016]   
    movq    mm0,[eax+4024]   
    movq    mm0,[eax+4032]   
    movq    mm0,[eax+4040]   
    movq    mm0,[eax+4048]   
    movq    mm0,[eax+4056]   
    movq    mm0,[eax+4064]   
    movq    mm0,[eax+4072]   
    movq    mm0,[eax+4080]   
    movq    mm0,[eax+4088]   
    add     eax,4096     
    dec     edx         
    jnz     lp
    emms                       
 }
}

inline void readmmx8()
{
  __asm
 {
    mov     eax,xx
    mov     edx,mempasses
    mov     ecx,xoffset
    add     eax,ecx   
 lp:movq    mm0,[eax]      
    movq    mm1,[eax+8]    
    movq    mm2,[eax+16]   
    movq    mm3,[eax+24]   
    movq    mm4,[eax+32]   
    movq    mm5,[eax+40]   
    movq    mm6,[eax+48]   
    movq    mm7,[eax+56]   
    movq    mm0,[eax+64]   
    movq    mm1,[eax+72]   
    movq    mm2,[eax+80]   
    movq    mm3,[eax+88]   
    movq    mm4,[eax+96]   
    movq    mm5,[eax+104]   
    movq    mm6,[eax+112]   
    movq    mm7,[eax+120]   
    movq    mm0,[eax+128]   
    movq    mm1,[eax+136]   
    movq    mm2,[eax+144]   
    movq    mm3,[eax+152]   
    movq    mm4,[eax+160]   
    movq    mm5,[eax+168]   
    movq    mm6,[eax+176]   
    movq    mm7,[eax+184]   
    movq    mm0,[eax+192]   
    movq    mm1,[eax+200]   
    movq    mm2,[eax+208]   
    movq    mm3,[eax+216]   
    movq    mm4,[eax+224]   
    movq    mm5,[eax+232]   
    movq    mm6,[eax+240]   
    movq    mm7,[eax+248]   
    movq    mm0,[eax+256]   
    movq    mm1,[eax+264]   
    movq    mm2,[eax+272]   
    movq    mm3,[eax+280]   
    movq    mm4,[eax+288]   
    movq    mm5,[eax+296]   
    movq    mm6,[eax+304]   
    movq    mm7,[eax+312]   
    movq    mm0,[eax+320]   
    movq    mm1,[eax+328]   
    movq    mm2,[eax+336]   
    movq    mm3,[eax+344]   
    movq    mm4,[eax+352]   
    movq    mm5,[eax+360]   
    movq    mm6,[eax+368]   
    movq    mm7,[eax+376]   
    movq    mm0,[eax+384]   
    movq    mm1,[eax+392]   
    movq    mm2,[eax+400]   
    movq    mm3,[eax+408]   
    movq    mm4,[eax+416]   
    movq    mm5,[eax+424]   
    movq    mm6,[eax+432]   
    movq    mm7,[eax+440]   
    movq    mm0,[eax+448]   
    movq    mm1,[eax+456]   
    movq    mm2,[eax+464]   
    movq    mm3,[eax+472]   
    movq    mm4,[eax+480]   
    movq    mm5,[eax+488]   
    movq    mm6,[eax+496]   
    movq    mm7,[eax+504]   
    movq    mm0,[eax+512]   
    movq    mm1,[eax+520]   
    movq    mm2,[eax+528]   
    movq    mm3,[eax+536]   
    movq    mm4,[eax+544]   
    movq    mm5,[eax+552]   
    movq    mm6,[eax+560]   
    movq    mm7,[eax+568]   
    movq    mm0,[eax+576]   
    movq    mm1,[eax+584]   
    movq    mm2,[eax+592]   
    movq    mm3,[eax+600]   
    movq    mm4,[eax+608]   
    movq    mm5,[eax+616]   
    movq    mm6,[eax+624]   
    movq    mm7,[eax+632]   
    movq    mm0,[eax+640]   
    movq    mm1,[eax+648]   
    movq    mm2,[eax+656]   
    movq    mm3,[eax+664]   
    movq    mm4,[eax+672]   
    movq    mm5,[eax+680]   
    movq    mm6,[eax+688]   
    movq    mm7,[eax+696]   
    movq    mm0,[eax+704]   
    movq    mm1,[eax+712]   
    movq    mm2,[eax+720]   
    movq    mm3,[eax+728]   
    movq    mm4,[eax+736]   
    movq    mm5,[eax+744]   
    movq    mm6,[eax+752]   
    movq    mm7,[eax+760]   
    movq    mm0,[eax+768]   
    movq    mm1,[eax+776]   
    movq    mm2,[eax+784]   
    movq    mm3,[eax+792]   
    movq    mm4,[eax+800]   
    movq    mm5,[eax+808]   
    movq    mm6,[eax+816]   
    movq    mm7,[eax+824]   
    movq    mm0,[eax+832]   
    movq    mm1,[eax+840]   
    movq    mm2,[eax+848]   
    movq    mm3,[eax+856]   
    movq    mm4,[eax+864]   
    movq    mm5,[eax+872]   
    movq    mm6,[eax+880]   
    movq    mm7,[eax+888]   
    movq    mm0,[eax+896]   
    movq    mm1,[eax+904]   
    movq    mm2,[eax+912]   
    movq    mm3,[eax+920]   
    movq    mm4,[eax+928]   
    movq    mm5,[eax+936]   
    movq    mm6,[eax+944]   
    movq    mm7,[eax+952]   
    movq    mm0,[eax+960]   
    movq    mm1,[eax+968]   
    movq    mm2,[eax+976]   
    movq    mm3,[eax+984]   
    movq    mm4,[eax+992]   
    movq    mm5,[eax+1000]   
    movq    mm6,[eax+1008]   
    movq    mm7,[eax+1016]    
    movq    mm0,[eax+1024]   
    movq    mm1,[eax+1032]   
    movq    mm2,[eax+1040]   
    movq    mm3,[eax+1048]   
    movq    mm4,[eax+1056]   
    movq    mm5,[eax+1064]   
    movq    mm6,[eax+1072]   
    movq    mm7,[eax+1080]   
    movq    mm0,[eax+1088]   
    movq    mm1,[eax+1096]   
    movq    mm2,[eax+1104]   
    movq    mm3,[eax+1112]   
    movq    mm4,[eax+1120]   
    movq    mm5,[eax+1128]   
    movq    mm6,[eax+1136]   
    movq    mm7,[eax+1144]   
    movq    mm0,[eax+1152]   
    movq    mm1,[eax+1160]   
    movq    mm2,[eax+1168]   
    movq    mm3,[eax+1176]   
    movq    mm4,[eax+1184]   
    movq    mm5,[eax+1192]   
    movq    mm6,[eax+1200]   
    movq    mm7,[eax+1208]   
    movq    mm0,[eax+1216]   
    movq    mm1,[eax+1224]   
    movq    mm2,[eax+1232]   
    movq    mm3,[eax+1240]   
    movq    mm4,[eax+1248]   
    movq    mm5,[eax+1256]   
    movq    mm6,[eax+1264]   
    movq    mm7,[eax+1272]   
    movq    mm0,[eax+1280]   
    movq    mm1,[eax+1288]   
    movq    mm2,[eax+1296]   
    movq    mm3,[eax+1304]   
    movq    mm4,[eax+1312]   
    movq    mm5,[eax+1320]   
    movq    mm6,[eax+1328]   
    movq    mm7,[eax+1336]   
    movq    mm0,[eax+1344]   
    movq    mm1,[eax+1352]   
    movq    mm2,[eax+1360]   
    movq    mm3,[eax+1368]   
    movq    mm4,[eax+1376]   
    movq    mm5,[eax+1384]   
    movq    mm6,[eax+1392]   
    movq    mm7,[eax+1400]   
    movq    mm0,[eax+1408]   
    movq    mm1,[eax+1416]   
    movq    mm2,[eax+1424]   
    movq    mm3,[eax+1432]   
    movq    mm4,[eax+1440]   
    movq    mm5,[eax+1448]   
    movq    mm6,[eax+1456]   
    movq    mm7,[eax+1464]   
    movq    mm0,[eax+1472]   
    movq    mm1,[eax+1480]   
    movq    mm2,[eax+1488]   
    movq    mm3,[eax+1496]   
    movq    mm4,[eax+1504]   
    movq    mm5,[eax+1512]   
    movq    mm6,[eax+1520]   
    movq    mm7,[eax+1528]   
    movq    mm0,[eax+1536]   
    movq    mm1,[eax+1544]   
    movq    mm2,[eax+1552]   
    movq    mm3,[eax+1560]   
    movq    mm4,[eax+1568]   
    movq    mm5,[eax+1576]   
    movq    mm6,[eax+1584]   
    movq    mm7,[eax+1592]   
    movq    mm0,[eax+1600]   
    movq    mm1,[eax+1608]   
    movq    mm2,[eax+1616]   
    movq    mm3,[eax+1624]   
    movq    mm4,[eax+1632]   
    movq    mm5,[eax+1640]   
    movq    mm6,[eax+1648]   
    movq    mm7,[eax+1656]   
    movq    mm0,[eax+1664]   
    movq    mm1,[eax+1672]   
    movq    mm2,[eax+1680]   
    movq    mm3,[eax+1688]   
    movq    mm4,[eax+1696]   
    movq    mm5,[eax+1704]   
    movq    mm6,[eax+1712]   
    movq    mm7,[eax+1720]   
    movq    mm0,[eax+1728]   
    movq    mm1,[eax+1736]   
    movq    mm2,[eax+1744]   
    movq    mm3,[eax+1752]   
    movq    mm4,[eax+1760]   
    movq    mm5,[eax+1768]   
    movq    mm6,[eax+1776]   
    movq    mm7,[eax+1784]   
    movq    mm0,[eax+1792]   
    movq    mm1,[eax+1800]   
    movq    mm2,[eax+1808]   
    movq    mm3,[eax+1816]   
    movq    mm4,[eax+1824]   
    movq    mm5,[eax+1832]   
    movq    mm6,[eax+1840]   
    movq    mm7,[eax+1848]   
    movq    mm0,[eax+1856]   
    movq    mm1,[eax+1864]   
    movq    mm2,[eax+1872]   
    movq    mm3,[eax+1880]   
    movq    mm4,[eax+1888]   
    movq    mm5,[eax+1896]   
    movq    mm6,[eax+1904]   
    movq    mm7,[eax+1912]   
    movq    mm0,[eax+1920]   
    movq    mm1,[eax+1928]   
    movq    mm2,[eax+1936]   
    movq    mm3,[eax+1944]   
    movq    mm4,[eax+1952]   
    movq    mm5,[eax+1960]   
    movq    mm6,[eax+1968]   
    movq    mm7,[eax+1976]   
    movq    mm0,[eax+1984]   
    movq    mm1,[eax+1992]   
    movq    mm2,[eax+2000]   
    movq    mm3,[eax+2008]   
    movq    mm4,[eax+2016]   
    movq    mm5,[eax+2024]   
    movq    mm6,[eax+2032]   
    movq    mm7,[eax+2040]   
    movq    mm0,[eax+2048]   
    movq    mm1,[eax+2056]   
    movq    mm2,[eax+2064]   
    movq    mm3,[eax+2072]   
    movq    mm4,[eax+2080]   
    movq    mm5,[eax+2088]   
    movq    mm6,[eax+2096]   
    movq    mm7,[eax+2104]   
    movq    mm0,[eax+2112]   
    movq    mm1,[eax+2120]   
    movq    mm2,[eax+2128]   
    movq    mm3,[eax+2136]   
    movq    mm4,[eax+2144]   
    movq    mm5,[eax+2152]   
    movq    mm6,[eax+2160]   
    movq    mm7,[eax+2168]   
    movq    mm0,[eax+2176]   
    movq    mm1,[eax+2184]   
    movq    mm2,[eax+2192]   
    movq    mm3,[eax+2200]   
    movq    mm4,[eax+2208]   
    movq    mm5,[eax+2216]   
    movq    mm6,[eax+2224]   
    movq    mm7,[eax+2232]   
    movq    mm0,[eax+2240]   
    movq    mm1,[eax+2248]   
    movq    mm2,[eax+2256]   
    movq    mm3,[eax+2264]   
    movq    mm4,[eax+2272]   
    movq    mm5,[eax+2280]   
    movq    mm6,[eax+2288]   
    movq    mm7,[eax+2296]   
    movq    mm0,[eax+2304]   
    movq    mm1,[eax+2312]   
    movq    mm2,[eax+2320]   
    movq    mm3,[eax+2328]   
    movq    mm4,[eax+2336]   
    movq    mm5,[eax+2344]   
    movq    mm6,[eax+2352]   
    movq    mm7,[eax+2360]   
    movq    mm0,[eax+2368]   
    movq    mm1,[eax+2376]   
    movq    mm2,[eax+2384]   
    movq    mm3,[eax+2392]   
    movq    mm4,[eax+2400]   
    movq    mm5,[eax+2408]   
    movq    mm6,[eax+2416]   
    movq    mm7,[eax+2424]   
    movq    mm0,[eax+2432]   
    movq    mm1,[eax+2440]   
    movq    mm2,[eax+2448]   
    movq    mm3,[eax+2456]   
    movq    mm4,[eax+2464]   
    movq    mm5,[eax+2472]   
    movq    mm6,[eax+2480]   
    movq    mm7,[eax+2488]   
    movq    mm0,[eax+2496]   
    movq    mm1,[eax+2504]   
    movq    mm2,[eax+2512]   
    movq    mm3,[eax+2520]   
    movq    mm4,[eax+2528]   
    movq    mm5,[eax+2536]   
    movq    mm6,[eax+2544]   
    movq    mm7,[eax+2552]   
    movq    mm0,[eax+2560]   
    movq    mm1,[eax+2568]   
    movq    mm2,[eax+2576]   
    movq    mm3,[eax+2584]   
    movq    mm4,[eax+2592]   
    movq    mm5,[eax+2600]   
    movq    mm6,[eax+2608]   
    movq    mm7,[eax+2616]   
    movq    mm0,[eax+2624]   
    movq    mm1,[eax+2632]   
    movq    mm2,[eax+2640]   
    movq    mm3,[eax+2648]   
    movq    mm4,[eax+2656]   
    movq    mm5,[eax+2664]   
    movq    mm6,[eax+2672]   
    movq    mm7,[eax+2680]   
    movq    mm0,[eax+2688]   
    movq    mm1,[eax+2696]   
    movq    mm2,[eax+2704]   
    movq    mm3,[eax+2712]   
    movq    mm4,[eax+2720]   
    movq    mm5,[eax+2728]   
    movq    mm6,[eax+2736]   
    movq    mm7,[eax+2744]   
    movq    mm0,[eax+2752]   
    movq    mm1,[eax+2760]   
    movq    mm2,[eax+2768]   
    movq    mm3,[eax+2776]   
    movq    mm4,[eax+2784]   
    movq    mm5,[eax+2792]   
    movq    mm6,[eax+2800]   
    movq    mm7,[eax+2808]   
    movq    mm0,[eax+2816]   
    movq    mm1,[eax+2824]   
    movq    mm2,[eax+2832]   
    movq    mm3,[eax+2840]   
    movq    mm4,[eax+2848]   
    movq    mm5,[eax+2856]   
    movq    mm6,[eax+2864]   
    movq    mm7,[eax+2872]   
    movq    mm0,[eax+2880]   
    movq    mm1,[eax+2888]   
    movq    mm2,[eax+2896]   
    movq    mm3,[eax+2904]   
    movq    mm4,[eax+2912]   
    movq    mm5,[eax+2920]   
    movq    mm6,[eax+2928]   
    movq    mm7,[eax+2936]   
    movq    mm0,[eax+2944]   
    movq    mm1,[eax+2952]   
    movq    mm2,[eax+2960]   
    movq    mm3,[eax+2968]   
    movq    mm4,[eax+2976]   
    movq    mm5,[eax+2984]   
    movq    mm6,[eax+2992]   
    movq    mm7,[eax+3000]   
    movq    mm0,[eax+3008]   
    movq    mm1,[eax+3016]   
    movq    mm2,[eax+3024]   
    movq    mm3,[eax+3032]   
    movq    mm4,[eax+3040]   
    movq    mm5,[eax+3048]   
    movq    mm6,[eax+3056]   
    movq    mm7,[eax+3064]   
    movq    mm0,[eax+3072]   
    movq    mm1,[eax+3080]   
    movq    mm2,[eax+3088]   
    movq    mm3,[eax+3096]   
    movq    mm4,[eax+3104]   
    movq    mm5,[eax+3112]   
    movq    mm6,[eax+3120]   
    movq    mm7,[eax+3128]   
    movq    mm0,[eax+3136]   
    movq    mm1,[eax+3144]   
    movq    mm2,[eax+3152]   
    movq    mm3,[eax+3160]   
    movq    mm4,[eax+3168]   
    movq    mm5,[eax+3176]   
    movq    mm6,[eax+3184]   
    movq    mm7,[eax+3192]   
    movq    mm0,[eax+3200]       
    movq    mm1,[eax+3208]   
    movq    mm2,[eax+3216]   
    movq    mm3,[eax+3224]   
    movq    mm4,[eax+3232]   
    movq    mm5,[eax+3240]   
    movq    mm6,[eax+3248]   
    movq    mm7,[eax+3256]   
    movq    mm0,[eax+3264]   
    movq    mm1,[eax+3272]   
    movq    mm2,[eax+3280]   
    movq    mm3,[eax+3288]   
    movq    mm4,[eax+3296]   
    movq    mm5,[eax+3304]   
    movq    mm6,[eax+3312]   
    movq    mm7,[eax+3320]   
    movq    mm0,[eax+3328]   
    movq    mm1,[eax+3336]   
    movq    mm2,[eax+3344]   
    movq    mm3,[eax+3352]   
    movq    mm4,[eax+3360]   
    movq    mm5,[eax+3368]   
    movq    mm6,[eax+3376]   
    movq    mm7,[eax+3384]   
    movq    mm0,[eax+3392]   
    movq    mm1,[eax+3400]   
    movq    mm2,[eax+3408]   
    movq    mm3,[eax+3416]   
    movq    mm4,[eax+3424]   
    movq    mm5,[eax+3432]   
    movq    mm6,[eax+3440]   
    movq    mm7,[eax+3448]   
    movq    mm0,[eax+3456]   
    movq    mm1,[eax+3464]   
    movq    mm2,[eax+3472]   
    movq    mm3,[eax+3480]   
    movq    mm4,[eax+3488]   
    movq    mm5,[eax+3496]   
    movq    mm6,[eax+3504]   
    movq    mm7,[eax+3512]   
    movq    mm0,[eax+3520]   
    movq    mm1,[eax+3528]   
    movq    mm2,[eax+3536]   
    movq    mm3,[eax+3544]   
    movq    mm4,[eax+3552]   
    movq    mm5,[eax+3560]   
    movq    mm6,[eax+3568]   
    movq    mm7,[eax+3576]   
    movq    mm0,[eax+3584]   
    movq    mm1,[eax+3592]   
    movq    mm2,[eax+3600]   
    movq    mm3,[eax+3608]   
    movq    mm4,[eax+3616]   
    movq    mm5,[eax+3624]   
    movq    mm6,[eax+3632]   
    movq    mm7,[eax+3640]   
    movq    mm0,[eax+3648]   
    movq    mm1,[eax+3656]   
    movq    mm2,[eax+3664]   
    movq    mm3,[eax+3672]   
    movq    mm4,[eax+3680]   
    movq    mm5,[eax+3688]   
    movq    mm6,[eax+3696]   
    movq    mm7,[eax+3704]   
    movq    mm0,[eax+3712]   
    movq    mm1,[eax+3720]   
    movq    mm2,[eax+3728]   
    movq    mm3,[eax+3736]   
    movq    mm4,[eax+3744]   
    movq    mm5,[eax+3752]   
    movq    mm6,[eax+3760]   
    movq    mm7,[eax+3768]   
    movq    mm0,[eax+3776]   
    movq    mm1,[eax+3784]   
    movq    mm2,[eax+3792]   
    movq    mm3,[eax+3800]   
    movq    mm4,[eax+3808]   
    movq    mm5,[eax+3816]   
    movq    mm6,[eax+3824]   
    movq    mm7,[eax+3832]       
    movq    mm0,[eax+3840]   
    movq    mm1,[eax+3848]   
    movq    mm2,[eax+3856]   
    movq    mm3,[eax+3864]   
    movq    mm4,[eax+3872]   
    movq    mm5,[eax+3880]   
    movq    mm6,[eax+3888]   
    movq    mm7,[eax+3896]   
    movq    mm0,[eax+3904]   
    movq    mm1,[eax+3912]   
    movq    mm2,[eax+3920]   
    movq    mm3,[eax+3928]   
    movq    mm4,[eax+3936]   
    movq    mm5,[eax+3944]   
    movq    mm6,[eax+3952]   
    movq    mm7,[eax+3960]   
    movq    mm0,[eax+3968]   
    movq    mm1,[eax+3976]   
    movq    mm2,[eax+3984]   
    movq    mm3,[eax+3992]   
    movq    mm4,[eax+4000]   
    movq    mm5,[eax+4008]   
    movq    mm6,[eax+4016]   
    movq    mm7,[eax+4024]   
    movq    mm0,[eax+4032]   
    movq    mm1,[eax+4040]   
    movq    mm2,[eax+4048]   
    movq    mm3,[eax+4056]   
    movq    mm4,[eax+4064]   
    movq    mm5,[eax+4072]   
    movq    mm6,[eax+4080]   
    movq    mm7,[eax+4088]   
    add     eax,4096     
    dec     edx         
    jnz     lp
    emms                       
 }
}

inline void checkmem2b()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     ecx,xoffset
       add     edx,ecx
       mov     ebx,result1     
       mov     ecx,ebx     
   lp: and     ebx,[edx]   
       and     ecx,[edx+4]   
       and     ebx,[edx+8]   
       and     ecx,[edx+12]   
       and     ebx,[edx+16]   
       and     ecx,[edx+20]   
       and     ebx,[edx+24]   
       and     ecx,[edx+28]   
       and     ebx,[edx+32]   
       and     ecx,[edx+36]   
       and     ebx,[edx+40]   
       and     ecx,[edx+44]   
       and     ebx,[edx+48]   
       and     ecx,[edx+52]   
       and     ebx,[edx+56]   
       and     ecx,[edx+60]   
       and     ebx,[edx+64]   
       and     ecx,[edx+68]   
       and     ebx,[edx+72]   
       and     ecx,[edx+76]   
       and     ebx,[edx+80]   
       and     ecx,[edx+84]   
       and     ebx,[edx+88]   
       and     ecx,[edx+92]   
       and     ebx,[edx+96]   
       and     ecx,[edx+100]   
       and     ebx,[edx+104]   
       and     ecx,[edx+108]   
       and     ebx,[edx+112]   
       and     ecx,[edx+116]   
       and     ebx,[edx+120]   
       and     ecx,[edx+124]   
       and     ebx,[edx+128]   
       and     ecx,[edx+132]   
       and     ebx,[edx+136]   
       and     ecx,[edx+140]   
       and     ebx,[edx+144]   
       and     ecx,[edx+148]   
       and     ebx,[edx+152]   
       and     ecx,[edx+156]   
       and     ebx,[edx+160]   
       and     ecx,[edx+164]   
       and     ebx,[edx+168]   
       and     ecx,[edx+172]   
       and     ebx,[edx+176]   
       and     ecx,[edx+180]   
       and     ebx,[edx+184]   
       and     ecx,[edx+188]   
       and     ebx,[edx+192]   
       and     ecx,[edx+196]   
       and     ebx,[edx+200]   
       and     ecx,[edx+204]   
       and     ebx,[edx+208]   
       and     ecx,[edx+212]   
       and     ebx,[edx+216]   
       and     ecx,[edx+220]   
       and     ebx,[edx+224]   
       and     ecx,[edx+228]   
       and     ebx,[edx+232]   
       and     ecx,[edx+236]   
       and     ebx,[edx+240]   
       and     ecx,[edx+244]   
       and     ebx,[edx+248]   
       and     ecx,[edx+252]   
       add     edx,256     
       dec     eax         
       jnz     lp          
       and     ebx,ecx     
       mov     result1,ebx                  
 }
}


inline void checkmem2()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     ecx,xoffset
       add     edx,ecx     
       mov     ebx,result1   
   lp: and     ebx,[edx]   
       and     ebx,[edx+4]   
       and     ebx,[edx+8]   
       and     ebx,[edx+12]   
       and     ebx,[edx+16]   
       and     ebx,[edx+20]   
       and     ebx,[edx+24]   
       and     ebx,[edx+28]   
       and     ebx,[edx+32]   
       and     ebx,[edx+36]   
       and     ebx,[edx+40]   
       and     ebx,[edx+44]   
       and     ebx,[edx+48]   
       and     ebx,[edx+52]   
       and     ebx,[edx+56]   
       and     ebx,[edx+60]   
       and     ebx,[edx+64]   
       and     ebx,[edx+68]   
       and     ebx,[edx+72]   
       and     ebx,[edx+76]   
       and     ebx,[edx+80]   
       and     ebx,[edx+84]   
       and     ebx,[edx+88]   
       and     ebx,[edx+92]   
       and     ebx,[edx+96]   
       and     ebx,[edx+100]   
       and     ebx,[edx+104]   
       and     ebx,[edx+108]   
       and     ebx,[edx+112]   
       and     ebx,[edx+116]   
       and     ebx,[edx+120]   
       and     ebx,[edx+124]   
       and     ebx,[edx+128]   
       and     ebx,[edx+132]   
       and     ebx,[edx+136]   
       and     ebx,[edx+140]   
       and     ebx,[edx+144]   
       and     ebx,[edx+148]   
       and     ebx,[edx+152]   
       and     ebx,[edx+156]   
       and     ebx,[edx+160]   
       and     ebx,[edx+164]   
       and     ebx,[edx+168]   
       and     ebx,[edx+172]   
       and     ebx,[edx+176]   
       and     ebx,[edx+180]   
       and     ebx,[edx+184]   
       and     ebx,[edx+188]   
       and     ebx,[edx+192]   
       and     ebx,[edx+196]   
       and     ebx,[edx+200]   
       and     ebx,[edx+204]   
       and     ebx,[edx+208]   
       and     ebx,[edx+212]   
       and     ebx,[edx+216]   
       and     ebx,[edx+220]   
       and     ebx,[edx+224]   
       and     ebx,[edx+228]   
       and     ebx,[edx+232]   
       and     ebx,[edx+236]   
       and     ebx,[edx+240]   
       and     ebx,[edx+244]   
       and     ebx,[edx+248]   
       and     ebx,[edx+252]   
       add     edx,256     
       dec     eax         
       jnz     lp          
       mov     result1,ebx                  
 }
}

inline void readmem4b()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     ecx,xoffset
       add     edx,ecx   
   lp: mov     ebx,[edx]   
       mov     ecx,[edx+4]   
       mov     ebx,[edx+8]   
       mov     ecx,[edx+12]   
       mov     ebx,[edx+16]   
       mov     ecx,[edx+20]   
       mov     ebx,[edx+24]   
       mov     ecx,[edx+28]   
       mov     ebx,[edx+32]   
       mov     ecx,[edx+36]   
       mov     ebx,[edx+40]   
       mov     ecx,[edx+44]   
       mov     ebx,[edx+48]   
       mov     ecx,[edx+52]   
       mov     ebx,[edx+56]   
       mov     ecx,[edx+60]   
       mov     ebx,[edx+64]   
       mov     ecx,[edx+68]   
       mov     ebx,[edx+72]   
       mov     ecx,[edx+76]   
       mov     ebx,[edx+80]   
       mov     ecx,[edx+84]   
       mov     ebx,[edx+88]   
       mov     ecx,[edx+92]   
       mov     ebx,[edx+96]   
       mov     ecx,[edx+100]   
       mov     ebx,[edx+104]   
       mov     ecx,[edx+108]   
       mov     ebx,[edx+112]   
       mov     ecx,[edx+116]   
       mov     ebx,[edx+120]   
       mov     ecx,[edx+124]   
       mov     ebx,[edx+128]   
       mov     ecx,[edx+132]   
       mov     ebx,[edx+136]   
       mov     ecx,[edx+140]   
       mov     ebx,[edx+144]   
       mov     ecx,[edx+148]   
       mov     ebx,[edx+152]   
       mov     ecx,[edx+156]   
       mov     ebx,[edx+160]   
       mov     ecx,[edx+164]   
       mov     ebx,[edx+168]   
       mov     ecx,[edx+172]   
       mov     ebx,[edx+176]   
       mov     ecx,[edx+180]   
       mov     ebx,[edx+184]   
       mov     ecx,[edx+188]   
       mov     ebx,[edx+192]   
       mov     ecx,[edx+196]   
       mov     ebx,[edx+200]   
       mov     ecx,[edx+204]   
       mov     ebx,[edx+208]   
       mov     ecx,[edx+212]   
       mov     ebx,[edx+216]   
       mov     ecx,[edx+220]   
       mov     ebx,[edx+224]   
       mov     ecx,[edx+228]   
       mov     ebx,[edx+232]   
       mov     ecx,[edx+236]   
       mov     ebx,[edx+240]   
       mov     ecx,[edx+244]   
       mov     ebx,[edx+248]   
       mov     ecx,[edx+252]   
       add     edx,256     
       dec     eax         
       jnz     lp                       
 }
}

inline void readmem4()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     ecx,xoffset
       add     edx,ecx   
   lp: mov     ebx,[edx]   
       mov     ebx,[edx+4]   
       mov     ebx,[edx+8]   
       mov     ebx,[edx+12]   
       mov     ebx,[edx+16]   
       mov     ebx,[edx+20]   
       mov     ebx,[edx+24]   
       mov     ebx,[edx+28]   
       mov     ebx,[edx+32]   
       mov     ebx,[edx+36]   
       mov     ebx,[edx+40]   
       mov     ebx,[edx+44]   
       mov     ebx,[edx+48]   
       mov     ebx,[edx+52]   
       mov     ebx,[edx+56]   
       mov     ebx,[edx+60]   
       mov     ebx,[edx+64]   
       mov     ebx,[edx+68]   
       mov     ebx,[edx+72]   
       mov     ebx,[edx+76]   
       mov     ebx,[edx+80]   
       mov     ebx,[edx+84]   
       mov     ebx,[edx+88]   
       mov     ebx,[edx+92]   
       mov     ebx,[edx+96]   
       mov     ebx,[edx+100]   
       mov     ebx,[edx+104]   
       mov     ebx,[edx+108]   
       mov     ebx,[edx+112]   
       mov     ebx,[edx+116]   
       mov     ebx,[edx+120]   
       mov     ebx,[edx+124]   
       mov     ebx,[edx+128]   
       mov     ebx,[edx+132]   
       mov     ebx,[edx+136]   
       mov     ebx,[edx+140]   
       mov     ebx,[edx+144]   
       mov     ebx,[edx+148]   
       mov     ebx,[edx+152]   
       mov     ebx,[edx+156]   
       mov     ebx,[edx+160]   
       mov     ebx,[edx+164]   
       mov     ebx,[edx+168]   
       mov     ebx,[edx+172]   
       mov     ebx,[edx+176]   
       mov     ebx,[edx+180]   
       mov     ebx,[edx+184]   
       mov     ebx,[edx+188]   
       mov     ebx,[edx+192]   
       mov     ebx,[edx+196]   
       mov     ebx,[edx+200]   
       mov     ebx,[edx+204]   
       mov     ebx,[edx+208]   
       mov     ebx,[edx+212]   
       mov     ebx,[edx+216]   
       mov     ebx,[edx+220]   
       mov     ebx,[edx+224]   
       mov     ebx,[edx+228]   
       mov     ebx,[edx+232]   
       mov     ebx,[edx+236]   
       mov     ebx,[edx+240]   
       mov     ebx,[edx+244]   
       mov     ebx,[edx+248]   
       mov     ebx,[edx+252]   
       add     edx,256     
       dec     eax         
       jnz     lp                       
 }
}


inline void readmem64()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     edi,xoffset
       add     edx,edi     
   lp: mov     ebx,[edx]   
       mov     ecx,[edx+64]   
       mov     ebx,[edx+128]   
       mov     ecx,[edx+192]   
       mov     ebx,[edx+256]   
       mov     ecx,[edx+320]   
       mov     ebx,[edx+384]   
       mov     ecx,[edx+448]   
       mov     ebx,[edx+512]   
       mov     ecx,[edx+576]   
       mov     ebx,[edx+640]   
       mov     ecx,[edx+704]   
       mov     ebx,[edx+768]   
       mov     ecx,[edx+832]   
       mov     ebx,[edx+896]   
       mov     ecx,[edx+960]   
       mov     ebx,[edx+1024]   
       mov     ecx,[edx+1088]   
       mov     ebx,[edx+1152]   
       mov     ecx,[edx+1216]   
       mov     ebx,[edx+1280]   
       mov     ecx,[edx+1344]   
       mov     ebx,[edx+1408]   
       mov     ecx,[edx+1472]   
       mov     ebx,[edx+1536]   
       mov     ecx,[edx+1600]   
       mov     ebx,[edx+1664]   
       mov     ecx,[edx+1728]   
       mov     ebx,[edx+1792]   
       mov     ecx,[edx+1856]   
       mov     ebx,[edx+1920]   
       mov     ecx,[edx+1984]   
       mov     ebx,[edx+2048]   
       mov     ecx,[edx+2112]   
       mov     ebx,[edx+2176]   
       mov     ecx,[edx+2240]   
       mov     ebx,[edx+2304]   
       mov     ecx,[edx+2368]   
       mov     ebx,[edx+2432]   
       mov     ecx,[edx+2496]   
       mov     ebx,[edx+2560]   
       mov     ecx,[edx+2624]   
       mov     ebx,[edx+2688]   
       mov     ecx,[edx+2752]   
       mov     ebx,[edx+2816]   
       mov     ecx,[edx+2880]   
       mov     ebx,[edx+2944]   
       mov     ecx,[edx+3008]   
       mov     ebx,[edx+3072]   
       mov     ecx,[edx+3136]   
       mov     ebx,[edx+3200]   
       mov     ecx,[edx+3264]   
       mov     ebx,[edx+3328]   
       mov     ecx,[edx+3392]   
       mov     ebx,[edx+3456]   
       mov     ecx,[edx+3520]   
       mov     ebx,[edx+3584]   
       mov     ecx,[edx+3648]   
       mov     ebx,[edx+3712]   
       mov     ecx,[edx+3776]   
       mov     ebx,[edx+3840]   
       mov     ecx,[edx+3904]   
       mov     ebx,[edx+3968]   
       mov     ecx,[edx+4032]   
       add     edx,4096         
       dec     eax         
       jnz     lp                       
 }
}


inline void readmem32()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     edi,xoffset
       add     edx,edi     
   lp: mov     ebx,[edx]   
       mov     ecx,[edx+32]   
       mov     ebx,[edx+64]   
       mov     ecx,[edx+96]   
       mov     ebx,[edx+128]   
       mov     ecx,[edx+160]   
       mov     ebx,[edx+192]   
       mov     ecx,[edx+224]   
       mov     ebx,[edx+256]   
       mov     ecx,[edx+288]   
       mov     ebx,[edx+320]   
       mov     ecx,[edx+352]   
       mov     ebx,[edx+384]   
       mov     ecx,[edx+416]   
       mov     ebx,[edx+448]   
       mov     ecx,[edx+480]   
       mov     ebx,[edx+512]   
       mov     ecx,[edx+544]   
       mov     ebx,[edx+576]   
       mov     ecx,[edx+608]   
       mov     ebx,[edx+640]   
       mov     ecx,[edx+672]   
       mov     ebx,[edx+704]   
       mov     ecx,[edx+736]   
       mov     ebx,[edx+768]   
       mov     ecx,[edx+800]   
       mov     ebx,[edx+832]   
       mov     ecx,[edx+864]   
       mov     ebx,[edx+896]   
       mov     ecx,[edx+928]   
       mov     ebx,[edx+960]   
       mov     ecx,[edx+992]   
       mov     ebx,[edx+1024]   
       mov     ecx,[edx+1056]   
       mov     ebx,[edx+1088]   
       mov     ecx,[edx+1120]   
       mov     ebx,[edx+1152]   
       mov     ecx,[edx+1184]   
       mov     ebx,[edx+1216]   
       mov     ecx,[edx+1248]   
       mov     ebx,[edx+1280]   
       mov     ecx,[edx+1312]   
       mov     ebx,[edx+1344]   
       mov     ecx,[edx+1376]   
       mov     ebx,[edx+1408]   
       mov     ecx,[edx+1440]   
       mov     ebx,[edx+1472]   
       mov     ecx,[edx+1504]   
       mov     ebx,[edx+1536]   
       mov     ecx,[edx+1568]   
       mov     ebx,[edx+1600]   
       mov     ecx,[edx+1632]   
       mov     ebx,[edx+1664]   
       mov     ecx,[edx+1696]   
       mov     ebx,[edx+1728]   
       mov     ecx,[edx+1760]   
       mov     ebx,[edx+1792]   
       mov     ecx,[edx+1824]   
       mov     ebx,[edx+1856]   
       mov     ecx,[edx+1888]   
       mov     ebx,[edx+1920]   
       mov     ecx,[edx+1952]   
       mov     ebx,[edx+1984]   
       mov     ecx,[edx+2016]   
       add     edx,2048     
       dec     eax         
       jnz     lp                       
 }
}

inline void readmem16()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     edi,xoffset
       add     edx,edi     
   lp: mov     ebx,[edx]   
       mov     ecx,[edx+16]   
       mov     ebx,[edx+32]   
       mov     ecx,[edx+48]   
       mov     ebx,[edx+64]   
       mov     ecx,[edx+80]   
       mov     ebx,[edx+96]   
       mov     ecx,[edx+112]   
       mov     ebx,[edx+128]   
       mov     ecx,[edx+144]   
       mov     ebx,[edx+160]   
       mov     ecx,[edx+176]   
       mov     ebx,[edx+192]   
       mov     ecx,[edx+208]   
       mov     ebx,[edx+224]   
       mov     ecx,[edx+240]   
       mov     ebx,[edx+256]   
       mov     ecx,[edx+272]   
       mov     ebx,[edx+288]   
       mov     ecx,[edx+304]   
       mov     ebx,[edx+320]   
       mov     ecx,[edx+336]   
       mov     ebx,[edx+352]   
       mov     ecx,[edx+368]   
       mov     ebx,[edx+384]   
       mov     ecx,[edx+400]   
       mov     ebx,[edx+416]   
       mov     ecx,[edx+432]   
       mov     ebx,[edx+448]   
       mov     ecx,[edx+464]   
       mov     ebx,[edx+480]   
       mov     ecx,[edx+496]   
       mov     ebx,[edx+512]   
       mov     ecx,[edx+528]   
       mov     ebx,[edx+544]   
       mov     ecx,[edx+560]   
       mov     ebx,[edx+576]   
       mov     ecx,[edx+592]   
       mov     ebx,[edx+608]   
       mov     ecx,[edx+624]   
       mov     ebx,[edx+640]   
       mov     ecx,[edx+656]   
       mov     ebx,[edx+672]   
       mov     ecx,[edx+688]   
       mov     ebx,[edx+704]   
       mov     ecx,[edx+720]   
       mov     ebx,[edx+736]   
       mov     ecx,[edx+752]   
       mov     ebx,[edx+768]   
       mov     ecx,[edx+784]   
       mov     ebx,[edx+800]   
       mov     ecx,[edx+816]   
       mov     ebx,[edx+832]   
       mov     ecx,[edx+848]   
       mov     ebx,[edx+864]   
       mov     ecx,[edx+880]   
       mov     ebx,[edx+896]   
       mov     ecx,[edx+912]   
       mov     ebx,[edx+928]   
       mov     ecx,[edx+944]   
       mov     ebx,[edx+960]   
       mov     ecx,[edx+976]   
       mov     ebx,[edx+992]   
       mov     ecx,[edx+1008]  
       add     edx,1024     
       dec     eax         
       jnz     lp                       
 }
}

inline void readmem8()
{
  __asm
 {
       mov     edx,xx
       mov     eax,mempasses
       mov     edi,xoffset
       add     edx,edi     
   lp: mov     ebx,[edx]      
       mov     ecx,[edx+8]    
       mov     ebx,[edx+16]   
       mov     ecx,[edx+24]   
       mov     ebx,[edx+32]   
       mov     ecx,[edx+40]   
       mov     ebx,[edx+48]   
       mov     ecx,[edx+56]   
       mov     ebx,[edx+64]   
       mov     ecx,[edx+72]   
       mov     ebx,[edx+80]   
       mov     ecx,[edx+88]   
       mov     ebx,[edx+96]   
       mov     ecx,[edx+104]  
       mov     ebx,[edx+112]   
       mov     ecx,[edx+120]   
       mov     ebx,[edx+128]   
       mov     ecx,[edx+136]   
       mov     ebx,[edx+144]   
       mov     ecx,[edx+152]   
       mov     ebx,[edx+160]   
       mov     ecx,[edx+168]   
       mov     ebx,[edx+176]   
       mov     ecx,[edx+184]   
       mov     ebx,[edx+192]   
       mov     ecx,[edx+200]   
       mov     ebx,[edx+208]   
       mov     ecx,[edx+216]   
       mov     ebx,[edx+224]   
       mov     ecx,[edx+232]   
       mov     ebx,[edx+240]   
       mov     ecx,[edx+248]   
       mov     ebx,[edx+256]   
       mov     ecx,[edx+264]   
       mov     ebx,[edx+272]   
       mov     ecx,[edx+280]   
       mov     ebx,[edx+288]   
       mov     ecx,[edx+296]   
       mov     ebx,[edx+304]   
       mov     ecx,[edx+312]   
       mov     ebx,[edx+320]   
       mov     ecx,[edx+328]   
       mov     ebx,[edx+336]   
       mov     ecx,[edx+344]   
       mov     ebx,[edx+352]   
       mov     ecx,[edx+360]   
       mov     ebx,[edx+368]   
       mov     ecx,[edx+376]   
       mov     ebx,[edx+384]   
       mov     ecx,[edx+392]   
       mov     ebx,[edx+400]   
       mov     ecx,[edx+408]   
       mov     ebx,[edx+416]   
       mov     ecx,[edx+424]   
       mov     ebx,[edx+432]   
       mov     ecx,[edx+440]   
       mov     ebx,[edx+448]   
       mov     ecx,[edx+456]   
       mov     ebx,[edx+464]   
       mov     ecx,[edx+472]   
       mov     ebx,[edx+480]   
       mov     ecx,[edx+488]   
       mov     ebx,[edx+496]   
       mov     ecx,[edx+504]   
       add     edx,512     
       dec     eax         
       jnz     lp                       
 }
}


inline void writemmx()
{
  __asm
 {
    mov     eax,xx
    mov     edx,mempasses
    movq    mm0,[eax]      
    movq    mm1,[eax+32]   
    add     eax,64         
 lp:movq    [eax],mm0      
    movq    [eax+8],mm0    
    movq    [eax+16],mm0    
    movq    [eax+24],mm0    
    movq    [eax+32],mm1    
    movq    [eax+40],mm1    
    movq    [eax+48],mm1    
    movq    [eax+56],mm1    
    movq    [eax+64],mm0    
    movq    [eax+72],mm0    
    movq    [eax+80],mm0    
    movq    [eax+88],mm0    
    movq    [eax+96],mm1    
    movq    [eax+104],mm1    
    movq    [eax+112],mm1    
    movq    [eax+120],mm1    
    add     eax,128      
    dec     edx          
    jnz     lp
    emms
 }
}

inline void mmxRun()
{
    __asm
    {
        mov     ecx, outerLoop
        mov     eax, xaddress
        movq    mm0, [eax] 
        movq    mm1, mm0
        movq    mm2, mm0
        movq    mm3, mm0
        movq    mm4, mm0
        movq    mm5, mm0
        movq    mm6, mm0
        movq    mm7, mm0
   lp1: mov     eax, xaddress
        mov     edx, mempasses
   lp2: psubd   mm0, [eax]
        psubd   mm1, [eax+8]
        psubd   mm2, [eax+16]
        psubd   mm3, [eax+24]
        psubd   mm4, [eax+32]
        psubd   mm5, [eax+40]
        psubd   mm6, [eax+48]
        psubd   mm7, [eax+56]
        paddd   mm0, [eax+64]
        paddd   mm1, [eax+72]
        paddd   mm2, [eax+80]
        paddd   mm3, [eax+88]
        paddd   mm4, [eax+96]
        paddd   mm5, [eax+104]
        paddd   mm6, [eax+112]
        paddd   mm7, [eax+120]
        add     eax, passbytes
        dec     edx
        jnz     lp2
        dec     ecx
        jnz     lp1
        psubd   mm0, mm1         
        paddd   mm0, mm2
        psubd   mm0, mm3           
        paddd   mm0, mm4     
        psubd   mm0, mm5           
        paddd   mm0, mm6 
        psubd   mm0, mm7
        paddd   mm0, mm2
        movq    mmxCheck, mm0
        mov     eax, xaddress
        movq    [eax], mm0
        emms
    }       
    sprintf(patternIs, "%8.8X%8.8X", mmxCheck[0], mmxCheck[1]);
}

     
inline void errorcheck()
{
  __asm
 {
    mov     eax,xx
    mov     edx,mempasses
    lea     ecx,sumCheck
    movq    mm0,[ecx]     
    movq    mm1,[ecx]     
    movq    mm2,[ecx+8]   
    movq    mm3,[ecx+8]   
 lp:por     mm0,[eax]     
    por     mm0,[eax+8]   
    por     mm0,[eax+16]   
    por     mm0,[eax+24]   
    por     mm2,[eax+32]   
    por     mm2,[eax+40]   
    por     mm2,[eax+48]   
    por     mm2,[eax+56]   
    por     mm0,[eax+64]   
    por     mm0,[eax+72]   
    por     mm0,[eax+80]   
    por     mm0,[eax+88]   
    por     mm2,[eax+96]   
    por     mm2,[eax+104]  
    por     mm2,[eax+112]  
    por     mm2,[eax+120]  
    pand    mm1,[eax]      
    pand    mm1,[eax+8]    
    pand    mm1,[eax+16]   
    pand    mm1,[eax+24]   
    pand    mm3,[eax+32]   
    pand    mm3,[eax+40]   
    pand    mm3,[eax+48]   
    pand    mm3,[eax+56]   
    pand    mm1,[eax+64]   
    pand    mm1,[eax+72]   
    pand    mm1,[eax+80]   
    pand    mm1,[eax+88]   
    pand    mm3,[eax+96]   
    pand    mm3,[eax+104]  
    pand    mm3,[eax+112]  
    pand    mm3,[eax+120]      
    add     eax,128      
    dec     edx          
    jnz     lp           
    movq    [ecx],mm0    
    movq    [ecx+8],mm1  
    movq    [ecx+16],mm2 
    movq    [ecx+24],mm3
    emms 
 }
}


