/*
 * rbcNsUtil.h --
 *
 * Copyright 1993-1998 Lucent Technologies, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and warranty
 * disclaimer appear in supporting documentation, and that the names
 * of Lucent Technologies any of their entities not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * Lucent Technologies disclaims all warranties with regard to this
 * software, including all implied warranties of merchantability and
 * fitness.  In no event shall Lucent Technologies be liable for any
 * special, indirect or consequential damages or any damages
 * whatsoever resulting from loss of use, data or profits, whether in
 * an action of contract, negligence or other tortuous action, arising
 * out of or in connection with the use or performance of this
 * software.
 */

#ifndef RBC_NS_UTIL_H
#define RBC_NS_UTIL_H 1

#ifndef TCL_NAMESPACE_ONLY
#define TCL_NAMESPACE_ONLY TCL_GLOBAL_ONLY
#endif

#define NS_SEARCH_NONE		(0)
#define NS_SEARCH_CURRENT	(1<<0)
#define NS_SEARCH_GLOBAL	(1<<1)
#define NS_SEARCH_BOTH		(NS_SEARCH_GLOBAL | NS_SEARCH_CURRENT)

/*
 * Namespace procedures not prototyped defined in Tcl.h 
 */

/*
EXTERN Tcl_Command Tcl_FindCommand _ANSI_ARGS_((Tcl_Interp *interp,
	const char *name, Tcl_Namespace *nsPtr, int flags));
EXTERN Tcl_Namespace *Tcl_GetCurrentNamespace _ANSI_ARGS_((Tcl_Interp *interp));

EXTERN Tcl_Namespace *Tcl_GetGlobalNamespace _ANSI_ARGS_((Tcl_Interp *interp));

EXTERN Tcl_Namespace *Tcl_CreateNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	const char *name, ClientData clientData, Tcl_NamespaceDeleteProc *nsDelProc));

EXTERN void Tcl_DeleteNamespace _ANSI_ARGS_((Tcl_Namespace *nsPtr));

EXTERN Tcl_Namespace *Tcl_FindNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	const char *name, Tcl_Namespace *context, int flags));

EXTERN int Tcl_Export _ANSI_ARGS_((Tcl_Interp *interp, Tcl_Namespace *nsPtr,
	const char *name, int resetFlag));

EXTERN Tcl_Var Tcl_FindNamespaceVar _ANSI_ARGS_((Tcl_Interp *interp, char *name,
	Tcl_Namespace *contextNsPtr, int flags));

EXTERN void Tcl_PopCallFrame _ANSI_ARGS_((Tcl_Interp *interp));

EXTERN int Tcl_PushCallFrame _ANSI_ARGS_((Tcl_Interp *interp,
	Tcl_CallFrame * framePtr, Tcl_Namespace *nsPtr, int isProcCallFrame));
*/

/* 
 * Auxillary procedures 
 */

// EXTERN TclVarHashTable *Rbc_GetArrayVariableTable _ANSI_ARGS_((
//	Tcl_Interp *interp, CONST char *varName, int flags));

/*
EXTERN Tcl_Namespace *Rbc_GetVariableNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	CONST char *varName));

EXTERN Tcl_CallFrame *Rbc_EnterNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	Tcl_Namespace *nsPtr));

EXTERN void Rbc_LeaveNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	Tcl_CallFrame * framePtr));

EXTERN Tcl_Command Rbc_CreateCommand _ANSI_ARGS_((Tcl_Interp *interp,
	CONST char *cmdName, Tcl_CmdProc *proc, ClientData clientData,
	Tcl_CmdDeleteProc *deleteProc));
*/

EXTERN Tcl_Namespace *Rbc_GetCommandNamespace _ANSI_ARGS_((Tcl_Interp *interp,
	Tcl_Command cmdToken));

EXTERN char *Rbc_GetQualifiedName _ANSI_ARGS_((Tcl_Namespace *nsPtr, 
	CONST char *name, Tcl_DString *resultPtr));

EXTERN int Rbc_ParseQualifiedName _ANSI_ARGS_((Tcl_Interp *interp, 
	CONST char *name, Tcl_Namespace **nsPtrPtr, CONST char **namePtr));

#endif /* RBC_NS_UTIL_H */
