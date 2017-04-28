/*
 * rbcInt.c --
 *
 *      This file constructs the basic functionality of the
 *      rbc commands.
 *
 * Copyright (c) 2009 Samuel Green, Nicholas Hudson, Stanton Sievers, Jarrod Stormo
 * All rights reserved.
 *
 * See "license.terms" for details.
 */

#include "rbcInt.h"

Tcl_Obj *rbcEmptyStringObjPtr;

#ifdef WIN32
/*
 *----------------------------------------------------------------------
 *
 * DllMain --
 *
 *      This wrapper function is used by Windows to invoke the
 *      initialization code for the DLL.
 *
 * Results:
 *      Returns TRUE;
 *
 * Side effects:
 *      None.
 *
 *----------------------------------------------------------------------
 */
BOOL APIENTRY
DllMain(
    HINSTANCE hInst,      	/* Library instance handle. */
    DWORD reason,		    /* Reason this function is being called. */
    LPVOID reserved)		/* Not used. */
{
    return TRUE;
}

/*
 *----------------------------------------------------------------------
 *
 * DllEntryPoint --
 *
 *      TODO: Description
 *
 * Results:
 *      Returns the result from DllMain.
 *
 * Side effects:
 *      None.
 *
 *----------------------------------------------------------------------
 */
BOOL APIENTRY
DllEntryPoint(hInst, reason, reserved)
    HINSTANCE hInst;            /* Library instance handle. */
    DWORD reason;               /* Reason this function is being called. */
    LPVOID reserved;            /* Not used. */
{
    return DllMain(hInst, reason, reserved);
}
#endif /* WIN32 */

/*
 * -----------------------------------------------------------------------
 *
 * Rbc_Init --
 *
 *      This procedure is invoked to initialize the "rbc" commands.
 *
 * Results:
 *      None.
 *
 * Side effects:
 *      Creates the new commands and adds a new entry into a global Tcl
 *      associative array.
 *
 * ------------------------------------------------------------------------
 */
int DLLEXPORT
Rbc_Init (interp)
    Tcl_Interp *interp; /* Base interpreter to return results to. */
{
    if (Tcl_InitStubs(interp, MIN_VERSION, 0) == NULL) {
        return TCL_ERROR;
    }

    if (Tk_InitStubs(interp, MIN_VERSION, 0) == NULL) {
        return TCL_ERROR;
    }

    rbcEmptyStringObjPtr = Tcl_NewStringObj("", -1);
    Tcl_IncrRefCount(rbcEmptyStringObjPtr);

    if (Tcl_PkgProvide(interp, "rbc", "0.2") == TCL_ERROR) {
        return TCL_ERROR;
    }

    Rbc_RegisterArrayObj(interp);

    Tcl_Namespace *nsPtr;
    nsPtr = Tcl_FindNamespace(interp, "rbc", NULL, TCL_GLOBAL_ONLY);
    if (nsPtr == NULL) {
      nsPtr = Tcl_CreateNamespace(interp, "rbc", NULL, NULL);
      if (nsPtr == NULL) {
        return TCL_ERROR;
      }
    }

    if (Tcl_Export(interp, nsPtr, "vector", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "graph", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "stripchart", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "barchart", 0) != TCL_OK) {
        return TCL_ERROR;
    }
/*
    if (Tcl_Export(interp, nsPtr, "busy", 0) != TCL_OK) {
        return TCL_ERROR;
    }
*/

    if (Tcl_Export(interp, nsPtr, "winop", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "htext", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "bitmap", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "table", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "bgexec", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "container", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "hierbox", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "tree", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "treeview", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "hiertable", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "spline", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "tabnotebook", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "tabset", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "drag&drop", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    if (Tcl_Export(interp, nsPtr, "dnd", 0) != TCL_OK) {
        return TCL_ERROR;
    }

    Rbc_VectorInit(interp);
    Rbc_GraphInit(interp);
    Rbc_InitEpsCanvasItem(interp);
    // Rbc_BusyInit(interp);
    Rbc_HtextInit(interp);
    Rbc_BitmapInit(interp);
    Rbc_TableInit(interp);
    Rbc_BgexecInit(interp);
    Rbc_ContainerInit(interp);
    Rbc_HierboxInit(interp);
    Rbc_TreeInit(interp);
    Rbc_TreeViewInit(interp);
    Rbc_SplineInit(interp);
    Rbc_TabnotebookInit(interp);
    Rbc_TabsetInit(interp);
    Rbc_WinopInit(interp);
    Rbc_DragDropInit(interp);
    Rbc_DndInit(interp);

    return TCL_OK;
}
