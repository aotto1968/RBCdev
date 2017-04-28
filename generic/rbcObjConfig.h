/* 
 * rbcObjConfig.h --
 *
 *	This file contains the Tcl_Obj based versions of the old
 *	Tk_ConfigureWidget procedures. 
 *
 * Copyright (c) 1990-1994 The Regents of the University of California.
 * Copyright (c) 1994-1997 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef RBC_OBJCONFIG_H
#define RBC_OBJCONFIG_H

/*
 * This is a Tcl_Obj based replacement for the widget configuration
 * functions in Tk.  
 *
 * What not use the new Tk_Option interface?
 *
 *	There were design changes in the new Tk_Option interface that
 *	make it unwieldy.  
 *
 *	o You have to dynamically allocate, store, and deallocate
 *	  your option table.  
 *      o The Tk_FreeConfigOptions routine requires a tkwin argument.
 *	  Unfortunately, most widgets save the display pointer and 
 *	  deference their tkwin when the window is destroyed.  
 *	o There's no TK_CONFIG_CUSTOM functionality.  This means that
 *	  save special options must be saved as strings by 
 *	  Tk_ConfigureWidget and processed later, thus losing the 
 *	  benefits of Tcl_Objs.  It also make error handling 
 *	  problematic, since you don't pick up certain errors like 
 *	  
 *	    .widget configure -myoption bad -myoption good
 *        
 *	  You will never see the first "bad" value.
 *	o Especially compared to the former Tk_ConfigureWidget calls,
 *	  the new interface is overly complex.  If there was a big
 *	  performance win, it might be worth the effort.  But let's 
 *	  face it, this biggest wins are in processing custom options
 *	  values with thousands of elements.  Most common resources 
 *	  (font, color, etc) have string tokens anyways.
 *
 *	On the other hand, the replacement functions in this file fell
 *	into place quite easily both from the aspect of API writer and
 *	user.  The biggest benefit is that you don't need to change lots
 *	of working code just to get the benefits of Tcl_Objs.
 * 
 */
#define SIDE_LEFT		(0)
#define SIDE_TOP		(1)
#define SIDE_RIGHT		(2)
#define SIDE_BOTTOM		(3)

#define SIDE_HORIZONTAL(s)	(!((s) & 0x1))
#define SIDE_VERTICAL(s)	((s) & 0x1)

#ifndef Rbc_Offset
#ifdef offsetof
#define Rbc_Offset(type, field) ((int) offsetof(type, field))
#else
#define Rbc_Offset(type, field) ((int) ((char *) &((type *) 0)->field))
#endif
#endif /* Rbc_Offset */
#define Ot_Offset(item) Rbc_Offset(OTOFFSET,item)

typedef int (Rbc_OptionParseProc) _ANSI_ARGS_((ClientData clientData,
	Tcl_Interp *interp, Tk_Window tkwin, Tcl_Obj *objPtr, char *widgRec, 
	int offset));					       
typedef Tcl_Obj *(Rbc_OptionPrintProc) _ANSI_ARGS_((ClientData clientData, 
	Tcl_Interp *interp, Tk_Window tkwin, char *widgRec, int offset));
typedef void (Rbc_OptionFreeProc) _ANSI_ARGS_((ClientData clientData,
	Display *display, char *widgRec, int offset));

typedef struct Rbc_CustomOption {
    Rbc_OptionParseProc *parseProc;	/* Procedure to call to parse an
					 * option and store it in converted
					 * form. */
    Rbc_OptionPrintProc *printProc;	/* Procedure to return a printable
					 * string describing an existing
					 * option. */
    Rbc_OptionFreeProc *freeProc;	/* Procedure to free the value. */

    ClientData clientData;		/* Arbitrary one-word value used by
					 * option parser:  passed to
					 * parseProc and printProc. */
} Rbc_CustomOption;

/*
 * Structure used to specify information for Tk_ConfigureWidget.  Each
 * structure gives complete information for one option, including
 * how the option is specified on the command line, where it appears
 * in the option database, etc.
 */

typedef struct {
    int type;			/* Type of option, such as RBC_CONFIG_COLOR;
				 * see definitions below.  Last option in
				 * table must have type RBC_CONFIG_END. */
    char *switchName;		/* Switch used to specify option in argv.
				 * NULL means this spec is part of a group. */
    Tk_Uid dbName;		/* Name for option in option database. */
    Tk_Uid dbClass;		/* Class for option in database. */
    Tk_Uid defValue;		/* Default value for option if not
				 * specified in command line or database. */
    int offset;			/* Where in widget record to store value;
				 * use Tk_Offset macro to generate values
				 * for this. */
    int specFlags;		/* Any combination of the values defined
				 * below;  other bits are used internally
				 * by tkConfig.c. */
    Rbc_CustomOption *customPtr; /* If type is RBC_CONFIG_CUSTOM then this is
				 * a pointer to info about how to parse and
				 * print the option.  Otherwise it is
				 * irrelevant. */
} Rbc_ConfigSpec;

/*
 * Type values for Rbc_ConfigSpec structures.  See the user
 * documentation for details.
 */

typedef enum {
    RBC_CONFIG_ACTIVE_CURSOR, 
    RBC_CONFIG_ANCHOR, 
    RBC_CONFIG_BITMAP,
    RBC_CONFIG_BOOLEAN, 
    RBC_CONFIG_BORDER, 
    RBC_CONFIG_CAP_STYLE, 
    RBC_CONFIG_COLOR, 
    RBC_CONFIG_CURSOR, 
    RBC_CONFIG_CUSTOM, 
    RBC_CONFIG_DOUBLE, 
    RBC_CONFIG_FONT, 
    RBC_CONFIG_INT, 
    RBC_CONFIG_JOIN_STYLE,
    RBC_CONFIG_JUSTIFY, 
    RBC_CONFIG_MM, 
    RBC_CONFIG_PIXELS, 
    RBC_CONFIG_RELIEF, 
    RBC_CONFIG_STRING,
    RBC_CONFIG_SYNONYM, 
    RBC_CONFIG_UID, 
    RBC_CONFIG_WINDOW, 

    RBC_CONFIG_BITFLAG,
    RBC_CONFIG_DASHES,
    RBC_CONFIG_DISTANCE,	/*  */
    RBC_CONFIG_FILL,
    RBC_CONFIG_FLOAT, 
    RBC_CONFIG_LIST,
    RBC_CONFIG_LISTOBJ,
    RBC_CONFIG_PAD,
    RBC_CONFIG_POS_DISTANCE,	/*  */
    RBC_CONFIG_SHADOW,		/*  */
    RBC_CONFIG_SIDE,
    RBC_CONFIG_STATE, 
    RBC_CONFIG_TILE,
    
    RBC_CONFIG_END
} Rbc_ConfigTypes;

/*
 * Possible values for flags argument to Tk_ConfigureWidget:
 */

#define RBC_CONFIG_OBJV_ONLY	1
#define RBC_CONFIG_OBJS		0x80

/*
 * Possible flag values for Rbc_ConfigSpec structures.  Any bits at
 * or above RBC_CONFIG_USER_BIT may be used by clients for selecting
 * certain entries.  Before changing any values here, coordinate with
 * tkOldConfig.c (internal-use-only flags are defined there).
 */

#define RBC_CONFIG_NULL_OK		1
#define RBC_CONFIG_COLOR_ONLY		2
#define RBC_CONFIG_MONO_ONLY		4
#define RBC_CONFIG_DONT_SET_DEFAULT	8
#define RBC_CONFIG_OPTION_SPECIFIED	0x10
#define RBC_CONFIG_USER_BIT		0x100

/*
 * Values for "flags" field of Rbc_ConfigSpec structures.  Be sure
 * to coordinate these values with those defined in tk.h
 * (RBC_CONFIG_COLOR_ONLY, etc.).  There must not be overlap!
 *
 * INIT -		Non-zero means (char *) things have been
 *			converted to Tk_Uid's.
 */

#define INIT		0x20

EXTERN int Rbc_ConfigureInfoFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Rbc_ConfigSpec *specs, char *widgRec, 
	Tcl_Obj *objPtr, int flags));
EXTERN int Rbc_ConfigureValueFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Rbc_ConfigSpec *specs, char * widgRec, 
	Tcl_Obj *objPtr, int flags));
EXTERN int Rbc_ConfigureWidgetFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Rbc_ConfigSpec *specs, int objc, Tcl_Obj *CONST *objv,
	char *widgRec, int flags));
EXTERN int Rbc_ConfigureComponentFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, char *name, char *className, Rbc_ConfigSpec *specs,
	int objc, Tcl_Obj *CONST *objv, char *widgRec, int flags));

EXTERN int Rbc_ObjConfigModified _ANSI_ARGS_(TCL_VARARGS(Rbc_ConfigSpec *, specs));
EXTERN void Rbc_FreeObjOptions _ANSI_ARGS_((Rbc_ConfigSpec *specs, 
	char *widgRec, Display *display, int needFlags));

EXTERN int Rbc_ObjIsOption _ANSI_ARGS_((Rbc_ConfigSpec *specs, Tcl_Obj *objPtr,
	int flags));

EXTERN int Rbc_GetPositionFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tcl_Obj *objPtr, int *indexPtr));

EXTERN int Rbc_GetPixelsFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Tcl_Obj *objPtr, int flags, int *valuePtr));

EXTERN int Rbc_GetPadFromObj  _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Tcl_Obj *objPtr, Rbc_Pad *padPtr));

EXTERN int Rbc_GetShadowFromObj _ANSI_ARGS_((Tcl_Interp *interp, 
	Tk_Window tkwin, Tcl_Obj *objPtr, Shadow *shadowPtr));

EXTERN int Rbc_GetStateFromObj  _ANSI_ARGS_((Tcl_Interp *interp, 
	Tcl_Obj *objPtr, int *statePtr));

EXTERN int Rbc_GetFillFromObj  _ANSI_ARGS_((Tcl_Interp *interp, 
	Tcl_Obj *objPtr, int *fillPtr));

EXTERN int Rbc_GetDashesFromObj  _ANSI_ARGS_((Tcl_Interp *interp, 
	Tcl_Obj *objPtr, Rbc_Dashes *dashesPtr));


#endif /* RBC_OBJCONFIG_H */
