/***************************************************************************
 *  NESHLA: The Nintendo Entertainment System High Level Assembler
 *  Copyright (C) 2003,2004,2005 Brian Provinciano, http://www.bripro.com
 *
 *  This program is free software. 
 *      You may use this code for anything you wish.
 *      It comes with no warranty.
 ***************************************************************************/

/******************************************************************************/
#include "../compiler.h"
/******************************************************************************
 * Handles the rest of the valid expressions
 ******************************************************************************/

/******************************************************************************/
BOOL FASTCALL comProc_General(U16 flags, S16 *brackCnt)
{
    if(!STRCMP(szTemp,"return")) {
        WriteReturn();
    } else {
        switch(*szTemp) {
        default:
            return FALSE;
        }
    }
    return TRUE;
}
/******************************************************************************/




