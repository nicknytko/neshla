/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *      You may use this code for anything you wish.
 *      It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/

#include <time.h>
#include <unistd.h>
#include "compiler.h"

/******************************************************************************/

void PrintTime(void);
/******************************************************************************/
int main(int argc, char* argv[])
{
    int l;
    char *s;

    clock_t start;
    start = clock();

    message(0,"Nintendo NES High Level Assembler");
    message(0,"Version %s, %s",SZ_VERSION,SZ_BUILD_DATE);
    message(0,"By Brian Provinciano :: http://www.bripro.com");
    message(0,"");

    if(argc < 1)
        return 3;

    s = argv[0];
    if(strlen(s) > 0) {
        strcpy(szprogdir,argv[0]);
        l = strlen(szprogdir)-1;
        s = szprogdir+l;
        while(l>0) {
            if(*s == '/' || *s == '\\') {
                *s = '\0';
                break;
            }
            s--;
        }
    } else {
        if(!getcwd(szprogdir, sizeof(szprogdir)-1))
            return 3;
    }

    l = strlen(szprogdir);
    if(l && szprogdir[l-1]!='/') {
        szprogdir[l]    = '/';
        szprogdir[l+1]  = '\0';
    }
                
    if(!InitConfig()) return 4;
    ParseCommandLine(argc, argv);


    sysDirList          =
        includeDirList  =
        libDirList              = NULL;

    l = strlen(szoutdir);
    if(l && szoutdir[l-1]!='/') {
        szoutdir[l] = '/';
        szoutdir[l+1] = '\0';
    }
    strcpy(outDir,szoutdir);

    sprintf(szTemp,"%s",szprogdir);
    AddDirList(&sysDirList, szTemp);
    sprintf(szTemp,"%sinclude/",szprogdir);
    printf("Standard includes: %s\n", szTemp);
    AddDirList(&includeDirList, szTemp);
    sprintf(szTemp,"%slib/",szprogdir);
    printf("Standard libs: %s\n", szTemp);
    AddDirList(&libDirList, szTemp);

    if(InitializeCompiler()) {
        message(0,"Compiling file: %s ... \n", szfilename);
        DoCompile(szfilename);
    }

    {
        float fl = (float)(clock() - start) / CLOCKS_PER_SEC;
        printf("Compilation time: %f seconds.\n", fl);
    }


    if(COMPILE_SUCCESS) {
        ShutDownCompiler();   
        PrintTime();
        message(MSG_COMPSUCCESS);
        //if(warnCnt)
        //      getch();
    } else // automatically shuts down
        fatal(FTL_COMPFAIL);
    message(0,"");

    return 0;
}
/******************************************************************************/
BOOL DoCompile(char *szFilename)
{
    BOOL result;

    result = CompileScript(szFilename, NULL, NULL);

    if(cfg.list.sourcesize && fSrcList) {
        CloseFile(fSrcList);
    }
    return result;
}
/******************************************************************************/
void PrintTime()
{
    time_t t;
    char *s;

    time(&t);
    s = ctime(&t);

    message(0,"");
    message(0,"%s", s);
}
/******************************************************************************/
