/* 
 * tkICM.c --
 *
 *      Extends the default version of the Tcl_AppInit procedure
 *      to include support for the ICM-API.
 *
 * Copyright (c) 1993 The Regents of the University of California.
 * Copyright (c) 1994 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#include "icm_support.h"
#include "tcl.h"
#include "tk.h"
#include <unistd.h>

/*
 * The following variable is a special hack that is needed in order for
 * Sun shared libraries to be used for Tcl.
 */

extern int matherr();
int *tclDummyMathPtr = (int *) matherr;

#ifdef TK_TEST
EXTERN int		Tktest_Init _ANSI_ARGS_((Tcl_Interp *interp));
#endif /* TK_TEST */

/*
 *----------------------------------------------------------------------
 *
 * main --
 *
 *	This is the main program for the application.
 *
 * Results:
 *	None: Tk_Main never returns here, so this procedure never
 *	returns either.
 *
 * Side effects:
 *	Whatever the application does.
 *
 *----------------------------------------------------------------------
 */


int
main(int argc, char **argv)
{
    Tk_Main(argc, argv, Tcl_AppInit);
    return 0;			/* Needed only to prevent compiler warning. */
}

/*
 *----------------------------------------------------------------------
 *
 * Tcl_AppInit --
 *
 *	This procedure performs application-specific initialization.
 *	Most applications, especially those that incorporate additional
 *	packages, will have their own version of this procedure.
 *
 * Results:
 *	Returns a standard Tcl completion code, and leaves an error
 *	message in interp->result if an error occurs.
 *
 * Side effects:
 *	Depends on the startup script.
 *
 *----------------------------------------------------------------------
 */

int
Tcl_AppInit(Tcl_Interp *interp)
{
    if (Tcl_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    if (Tk_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    Tcl_StaticPackage(interp, "Tk", Tk_Init, (Tcl_PackageInitProc *) NULL);
#ifdef TK_TEST
    if (Tktest_Init(interp) == TCL_ERROR) {
	return TCL_ERROR;
    }
    Tcl_StaticPackage(interp, "Tktest", Tktest_Init,
            (Tcl_PackageInitProc *) NULL);
#endif /* TK_TEST */


    /*
     * Call the init procedures for included packages.  Each call should
     * look like this:
     *
     * if (Mod_Init(interp) == TCL_ERROR) {
     *     return TCL_ERROR;
     * }
     *
     * where "Mod" is the name of the module.
     */

    /*
     * Call Tcl_CreateCommand for application-specific commands, if
     * they weren't already created by the init procedures called above.
     */

     Tcl_CreateCommand(interp, "icmInitComms", c_icmInitComms,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
     Tcl_CreateCommand(interp, "icmRegisterAgent", c_icmRegisterAgent,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
     Tcl_CreateCommand(interp, "icmDeregisterAgent", c_icmDeregisterAgent,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
     Tcl_CreateCommand(interp, "icmGetMsg", c_icmGetMsg,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL); 
     Tcl_CreateCommand(interp, "icmMsgAvail", c_icmMsgAvail,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);  
     Tcl_CreateCommand(interp, "icmFmtSendMsg", c_icmFmtSendMsg,
                       (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);     

    /*
     * Specify a user-specific startup file to invoke if the application
     * is run interactively.  Typically the startup file is "~/.apprc"
     * where "app" is the name of the application.  If this line is deleted
     * then no user-specific startup file will be run under any conditions.
     */

    Tcl_SetVar(interp, "tcl_rcFileName", "~/.wishrc", TCL_GLOBAL_ONLY);
    return TCL_OK;
}
