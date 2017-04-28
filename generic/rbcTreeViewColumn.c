
/*
 * rbcTreeViewColumn.c --
 *
 *	This module implements an hierarchy widget for the RBC toolkit.
 *
 * Copyright 1998-1999 Lucent Technologies, Inc.
 *
 * Permission to use, copy, modify, and distribute this software and
 * its documentation for any purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that the copyright notice and warranty
 * disclaimer appear in supporting documentation, and that the names
 * of Lucent Technologies or any of their entities not be used in
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
 *
 *	The "treeview" widget was created by George A. Howlett.
 */

/*
 * TODO:
 *
 * BUGS:
 *   1.  "open" operation should change scroll offset so that as many
 *	 new entries (up to half a screen) can be seen.
 *   2.  "open" needs to adjust the scrolloffset so that the same entry
 *	 is seen at the same place.
 */
#include "rbcInt.h"

#include "rbcTreeView.h"
#include <X11/Xutil.h>

#define RULE_AREA		(8)

static Rbc_OptionParseProc ObjToColumn;
static Rbc_OptionPrintProc ColumnToObj;
static Rbc_OptionParseProc ObjToData;
static Rbc_OptionPrintProc DataToObj;

static char *sortTypeStrings[] = {
    "dictionary", "ascii", "integer", "real", "command", "none", NULL
};

enum SortTypeValues { 
    SORT_TYPE_DICTIONARY, SORT_TYPE_ASCII, SORT_TYPE_INTEGER, 
    SORT_TYPE_REAL, SORT_TYPE_COMMAND, SORT_TYPE_NONE
};

#define DEF_SORT_COLUMN		(char *)NULL
#define DEF_SORT_COMMAND	(char *)NULL
#define DEF_SORT_DECREASING	"no"
#define DEF_SORT_TYPE		"dictionary"

#ifdef WIN32
#define DEF_COLUMN_ACTIVE_TITLE_BG	RGB_GREY85
#else
#define DEF_COLUMN_ACTIVE_TITLE_BG	RGB_GREY90
#endif
#define DEF_COLUMN_ACTIVE_TITLE_FG	STD_ACTIVE_FOREGROUND
#define DEF_COLUMN_BACKGROUND		(char *)NULL
#define DEF_COLUMN_BIND_TAGS		"all"
#define DEF_COLUMN_BORDERWIDTH		STD_BORDERWIDTH
#define DEF_COLUMN_COLOR		RGB_BLACK
#define DEF_COLUMN_EDIT			"yes"
#define DEF_COLUMN_FONT			STD_FONT
#define DEF_COLUMN_COMMAND		(char *)NULL
#define DEF_COLUMN_FOREGROUND		(char *)NULL
#define DEF_COLUMN_FORMAT_COMMAND	(char *)NULL
#define DEF_COLUMN_HIDE			"no"
#define DEF_COLUMN_JUSTIFY		"center"
#define DEF_COLUMN_MAX			"0"
#define DEF_COLUMN_MIN			"0"
#define DEF_COLUMN_PAD			"2"
#define DEF_COLUMN_RELIEF		"flat"
#define DEF_COLUMN_STATE		"normal"
#define DEF_COLUMN_STYLE		"text"
#define DEF_COLUMN_TITLE_BACKGROUND	STD_NORMAL_BACKGROUND
#define DEF_COLUMN_TITLE_BORDERWIDTH	STD_BORDERWIDTH
#define DEF_COLUMN_TITLE_FONT		STD_TITLE_FONT
#define DEF_COLUMN_TITLE_FOREGROUND	STD_NORMAL_FOREGROUND
#define DEF_COLUMN_TITLE_RELIEF		"raised"
#define DEF_COLUMN_WEIGHT		"1.0"
#define DEF_COLUMN_WIDTH		"0"
#define DEF_COLUMN_RULE_DASHES		"dot"

extern Rbc_OptionParseProc Rbc_ObjToEnum;
extern Rbc_OptionPrintProc Rbc_EnumToObj;

static Rbc_CustomOption typeOption =
{
    Rbc_ObjToEnum, Rbc_EnumToObj, NULL, (ClientData)sortTypeStrings
};

static Rbc_CustomOption columnOption =
{
    ObjToColumn, ColumnToObj, NULL, (ClientData)0
};

Rbc_CustomOption rbcTreeViewDataOption =
{
    ObjToData, DataToObj, NULL, (ClientData)0,
};

static Rbc_OptionParseProc ObjToStyle;
static Rbc_OptionPrintProc StyleToObj;
static Rbc_OptionFreeProc FreeStyle;
static Rbc_CustomOption styleOption =
{
    /* Contains a pointer to the widget that's currently being
     * configured.  This is used in the custom configuration parse
     * routine for icons.  */
    ObjToStyle, StyleToObj, FreeStyle, NULL,
};

extern Rbc_CustomOption rbcTreeViewUidOption;
extern Rbc_CustomOption rbcTreeViewIconOption;
static Rbc_TreeApplyProc SortApplyProc;

#define OTOFFSET TreeViewColumn

static Rbc_ConfigSpec columnSpecs[] =
{
    {RBC_CONFIG_BORDER  , "-activetitlebackground", "activeTitleBackground", "Background"      , DEF_COLUMN_ACTIVE_TITLE_BG  , Ot_Offset(activeTitleBorder) , 0}                                               ,
    {RBC_CONFIG_COLOR   , "-activetitleforeground", "activeTitleForeground", "Foreground"      , DEF_COLUMN_ACTIVE_TITLE_FG  , Ot_Offset(activeTitleFgColor), 0}                                               ,
    {RBC_CONFIG_BORDER  , "-background"           , "background"           , "Background"      , DEF_COLUMN_BACKGROUND       , Ot_Offset(border)            , RBC_CONFIG_NULL_OK}                              ,
    {RBC_CONFIG_SYNONYM , "-bd"                   , "borderWidth"          , (char *)NULL      , (char *)NULL                , 0                            , 0}                                               ,
    {RBC_CONFIG_SYNONYM , "-bg"                   , "background"           , (char *)NULL      , (char *)NULL                , 0                            , 0}                                               ,
    {RBC_CONFIG_CUSTOM  , "-bindtags"             , "bindTags"             , "BindTags"        , DEF_COLUMN_BIND_TAGS        , Ot_Offset(tagsUid)           , RBC_CONFIG_NULL_OK                               , &rbcTreeViewUidOption} ,
    {RBC_CONFIG_DISTANCE, "-borderwidth"          , "borderWidth"          , "BorderWidth"     , DEF_COLUMN_BORDERWIDTH      , Ot_Offset(borderWidth)       , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_STRING  , "-command"              , "command"              , "Command"         , DEF_COLUMN_COMMAND          , Ot_Offset(titleCmd)          , RBC_CONFIG_DONT_SET_DEFAULT | RBC_CONFIG_NULL_OK}, 
    {RBC_CONFIG_BOOLEAN , "-edit"                 , "edit"                 , "Edit"            , DEF_COLUMN_STATE            , Ot_Offset(editable)          , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_BOOLEAN , "-hide"                 , "hide"                 , "Hide"            , DEF_COLUMN_HIDE             , Ot_Offset(hidden)            , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_CUSTOM  , "-icon"                 , "icon"                 , "icon"            , (char *)NULL                , Ot_Offset(titleIcon)         , RBC_CONFIG_DONT_SET_DEFAULT                      , &rbcTreeViewIconOption},
    {RBC_CONFIG_JUSTIFY , "-justify"              , "justify"              , "Justify"         , DEF_COLUMN_JUSTIFY          , Ot_Offset(justify)           , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_DISTANCE, "-max"                  , "max"                  , "Max"             , DEF_COLUMN_MAX              , Ot_Offset(reqMax)            , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_DISTANCE, "-min"                  , "min"                  , "Min"             , DEF_COLUMN_MIN              , Ot_Offset(reqMin)            , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_PAD     , "-pad"                  , "pad"                  , "Pad"             , DEF_COLUMN_PAD              , Ot_Offset(pad)               , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_RELIEF  , "-relief"               , "relief"               , "Relief"          , DEF_COLUMN_RELIEF           , Ot_Offset(relief)            , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_DASHES  , "-ruledashes"           , "ruleDashes"           , "RuleDashes"      , DEF_COLUMN_RULE_DASHES      , Ot_Offset(ruleDashes)        , RBC_CONFIG_NULL_OK}                              ,
    {RBC_CONFIG_STRING  , "-sortcommand"          , "sortCommand"          , "SortCommand"     , DEF_SORT_COMMAND            , Ot_Offset(sortCmd)           , RBC_CONFIG_NULL_OK}                              , 
    {RBC_CONFIG_STATE   , "-state"                , "state"                , "State"           , DEF_COLUMN_STATE            , Ot_Offset(state)             , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_CUSTOM  , "-style"                , "style"                , "Style"           , DEF_COLUMN_STYLE            , Ot_Offset(stylePtr)          , 0                                                , &styleOption}          ,
    {RBC_CONFIG_STRING  , "-text"                 , "text"                 , "Text"            , (char *)NULL                , Ot_Offset(title)             , 0}                                               , 
    {RBC_CONFIG_STRING  , "-title"                , "title"                , "Title"           , (char *)NULL                , Ot_Offset(title)             , 0}                                               ,
    {RBC_CONFIG_BORDER  , "-titlebackground"      , "titleBackground"      , "TitleBackground" , DEF_COLUMN_TITLE_BACKGROUND , Ot_Offset(titleBorder)       , 0}                                               ,
    {RBC_CONFIG_DISTANCE, "-titleborderwidth"     , "BorderWidth"          , "TitleBorderWidth", DEF_COLUMN_TITLE_BORDERWIDTH, Ot_Offset(titleBorderWidth)  , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_FONT    , "-titlefont"            , "titleFont"            , "Font"            , DEF_COLUMN_TITLE_FONT       , Ot_Offset(titleFont)         , 0}                                               ,
    {RBC_CONFIG_COLOR   , "-titleforeground"      , "titleForeground"      , "TitleForeground" , DEF_COLUMN_TITLE_FOREGROUND , Ot_Offset(titleFgColor)      , 0}                                               ,
    {RBC_CONFIG_RELIEF  , "-titlerelief"          , "titleRelief"          , "TitleRelief"     , DEF_COLUMN_TITLE_RELIEF     , Ot_Offset(titleRelief)       , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_SHADOW  , "-titleshadow"          , "titleShadow"          , "TitleShadow"     , (char *)NULL                , Ot_Offset(titleShadow)       , 0}                                               ,
    {RBC_CONFIG_DOUBLE  , "-weight"               , (char *)NULL           , (char *)NULL      , DEF_COLUMN_WEIGHT           , Ot_Offset(weight)            , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_DISTANCE, "-width"                , "width"                , "Width"           , DEF_COLUMN_WIDTH            , Ot_Offset(reqWidth)          , RBC_CONFIG_DONT_SET_DEFAULT}                     ,
    {RBC_CONFIG_END     , (char *)NULL            , (char *)NULL           , (char *)NULL      , (char *)NULL                , 0                            , 0}
};
#undef OTOFFSET

#define OTOFFSET TreeView
static Rbc_ConfigSpec sortSpecs[] =
{
    {RBC_CONFIG_STRING , "-command"   , "command"   , "Command"   , DEF_SORT_COMMAND   , Ot_Offset(sortCmd)       , RBC_CONFIG_DONT_SET_DEFAULT | RBC_CONFIG_NULL_OK},
    {RBC_CONFIG_CUSTOM , "-column"    , "column"    , "Column"    , DEF_SORT_COLUMN    , Ot_Offset(sortColumnPtr) , RBC_CONFIG_DONT_SET_DEFAULT                      , &columnOption},
    {RBC_CONFIG_BOOLEAN, "-decreasing", "decreasing", "Decreasing", DEF_SORT_DECREASING, Ot_Offset(sortDecreasing), RBC_CONFIG_DONT_SET_DEFAULT}                     , 
    {RBC_CONFIG_CUSTOM , "-mode"      , "mode"      , "Mode"      , DEF_SORT_TYPE      , Ot_Offset(sortType)      , 0                                                , &typeOption}  ,
    {RBC_CONFIG_END    , (char *)NULL , (char *)NULL, (char *)NULL, (char *)NULL       , 0                        , 0}
};
#undef OTOFFSET

static Rbc_TreeCompareNodesProc CompareNodes;
static Rbc_TreeApplyProc SortApplyProc;

/*
 *----------------------------------------------------------------------
 *
 * ObjToColumn --
 *
 *	Convert the string reprsenting a scroll mode, to its numeric
 *	form.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left
 *	in interpreter's result field.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToColumn(clientData, interp, tkwin, objPtr, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Interpreter to send results back to */
    Tk_Window tkwin;		/* Not used. */
    Tcl_Obj *objPtr;		/* New legend position string */
    char *widgRec;
    int offset;
{
    TreeViewColumn **columnPtrPtr = (TreeViewColumn **)(widgRec + offset);
    char *string;

    string = Tcl_GetString(objPtr);
    if (*string == '\0') {
	*columnPtrPtr = NULL;
    } else {
	TreeView *tvPtr = (TreeView *)widgRec;

	if (Rbc_TreeViewGetColumn(interp, tvPtr, objPtr, columnPtrPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnToString --
 *
 * Results:
 *	The string representation of the button boolean is returned.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
ColumnToObj(clientData, interp, tkwin, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;
    Tk_Window tkwin;		/* Not used. */
    char *widgRec;
    int offset;
{
    TreeViewColumn *columnPtr = *(TreeViewColumn **)(widgRec + offset);

    if (columnPtr == NULL) {
	return rbcEmptyStringObjPtr;
    }
    return Tcl_NewStringObj(columnPtr->key, -1);
}

/*
 *----------------------------------------------------------------------
 *
 * ObjToData --
 *
 *	Convert the string reprsenting a scroll mode, to its numeric
 *	form.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left
 *	in interpreter's result field.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToData(clientData, interp, tkwin, objPtr, widgRec, offset)
    ClientData clientData;	/* Node of entry. */
    Tcl_Interp *interp;		/* Interpreter to send results back to */
    Tk_Window tkwin;		/* Not used. */
    Tcl_Obj *objPtr;		/* Tcl_Obj representing new data. */
    char *widgRec;
    int offset;
{
    Tcl_Obj **objv;
    TreeViewColumn *columnPtr;
    TreeViewEntry *entryPtr = (TreeViewEntry *)widgRec;
    char *string;
    int objc;
    register int i;

    string = Tcl_GetString(objPtr);
    if (*string == '\0') {
	return TCL_OK;
    } 
    if (Tcl_ListObjGetElements(interp, objPtr, &objc, &objv) != TCL_OK) {
	return TCL_ERROR;
    }
    if (objc == 0) {
	return TCL_OK;
    }
    if (objc & 0x1) {
	Tcl_AppendResult(interp, "data \"", string, 
		 "\" must be in even name-value pairs", (char *)NULL);
	return TCL_ERROR;
    }
    for (i = 0; i < objc; i += 2) {
	TreeView *tvPtr = entryPtr->tvPtr;

	if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[i], &columnPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	if (Rbc_TreeSetValueByKey(tvPtr->interp, tvPtr->tree, entryPtr->node, 
		columnPtr->key, objv[i + 1]) != TCL_OK) {
	    return TCL_ERROR;
	}
	Rbc_TreeViewAddValue(entryPtr, columnPtr);
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * DataToObj --
 *
 * Results:
 *	The string representation of the data is returned.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
DataToObj(clientData, interp, tkwin, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;
    Tk_Window tkwin;		/* Not used. */
    char *widgRec;
    int offset;
{
    Tcl_Obj *listObjPtr, *objPtr;
    TreeViewEntry *entryPtr = (TreeViewEntry *)widgRec;
    TreeViewValue *valuePtr;

    /* Add the key-value pairs to a new Tcl_Obj */
    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for (valuePtr = entryPtr->values; valuePtr != NULL; 
	valuePtr = valuePtr->nextPtr) {
	objPtr = Tcl_NewStringObj(valuePtr->columnPtr->key, -1);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
	if (Rbc_TreeViewGetData(entryPtr, valuePtr->columnPtr->key, &objPtr)
	    != TCL_OK) {
	    objPtr = rbcEmptyStringObjPtr;
	} 
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
    }
    return listObjPtr;
}

int
Rbc_TreeViewGetColumn(interp, tvPtr, objPtr, columnPtrPtr)
    Tcl_Interp *interp;
    TreeView *tvPtr;
    Tcl_Obj *objPtr;
    TreeViewColumn **columnPtrPtr;
{
    char *string;

    string = Tcl_GetString(objPtr);
    if (strcmp(string, "treeView") == 0) {
	*columnPtrPtr = &tvPtr->treeColumn;
    } else {
	Tcl_HashEntry *hPtr;
    
	hPtr = Tcl_FindHashEntry(&tvPtr->columnTable, Rbc_TreeGetKey(string));
	if (hPtr == NULL) {
	    if (interp != NULL) {
		Tcl_AppendResult(interp, "can't find column \"", string, 
			"\" in \"", Tk_PathName(tvPtr->tkwin), "\"", 
			(char *)NULL);
	    }
	    return TCL_ERROR;
	} 
	*columnPtrPtr = Tcl_GetHashValue(hPtr);
    }
    return TCL_OK;
}


/*
 *----------------------------------------------------------------------
 *
 * ObjToStyle --
 *
 *	Convert the name of an icon into a treeview style.
 *
 * Results:
 *	If the string is successfully converted, TCL_OK is returned.
 *	Otherwise, TCL_ERROR is returned and an error message is left in
 *	interpreter's result field.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ObjToStyle(clientData, interp, tkwin, objPtr, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;		/* Interpreter to send results back to */
    Tk_Window tkwin;		/* Not used. */
    Tcl_Obj *objPtr;		/* Tcl_Obj representing the new value. */
    char *widgRec;
    int offset;
{
    TreeView *tvPtr = clientData;
    TreeViewStyle **stylePtrPtr = (TreeViewStyle **)(widgRec + offset);
    TreeViewStyle *stylePtr;

    if (Rbc_TreeViewGetStyle(interp, tvPtr, Tcl_GetString(objPtr), 
	     &stylePtr) != TCL_OK) {
	return TCL_ERROR;
    }
    stylePtr->flags |= STYLE_DIRTY;
    tvPtr->flags |= (TV_LAYOUT | TV_DIRTY);
    *stylePtrPtr = stylePtr;
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * IconToObj --
 *
 *	Converts the icon into its string representation (its name).
 *
 * Results:
 *	The name of the icon is returned.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static Tcl_Obj *
StyleToObj(clientData, interp, tkwin, widgRec, offset)
    ClientData clientData;	/* Not used. */
    Tcl_Interp *interp;
    Tk_Window tkwin;		/* Not used. */
    char *widgRec;
    int offset;
{
    TreeViewStyle *stylePtr = *(TreeViewStyle **)(widgRec + offset);

    if (stylePtr == NULL) {
	return rbcEmptyStringObjPtr;
    }
    return Tcl_NewStringObj(stylePtr->name, -1);
}

/*ARGSUSED*/
static void
FreeStyle(clientData, display, widgRec, offset)
    ClientData clientData;
    Display *display;		/* Not used. */
    char *widgRec;
    int offset;
{
    TreeView *tvPtr = clientData;
    TreeViewStyle *stylePtr = *(TreeViewStyle **)(widgRec + offset);

    Rbc_TreeViewFreeStyle(tvPtr, stylePtr);
}

void
Rbc_TreeViewUpdateColumnGCs(tvPtr, columnPtr)
    TreeView *tvPtr;
    TreeViewColumn *columnPtr;
{
    Drawable drawable;
    GC newGC;
    Tk_3DBorder border;
    XGCValues gcValues;
    int ruleDrawn;
    unsigned long gcMask;
    int iconWidth, iconHeight;
    int textWidth, textHeight;

    gcMask = GCForeground | GCFont;
    gcValues.font = Tk_FontId(columnPtr->titleFont);

    /* Normal title text */
    gcValues.foreground = columnPtr->titleFgColor->pixel;
    newGC = Tk_GetGC(tvPtr->tkwin, gcMask, &gcValues);
    if (columnPtr->titleGC != NULL) {
	Tk_FreeGC(tvPtr->display, columnPtr->titleGC);
    }
    columnPtr->titleGC = newGC;

    /* Active title text */
    gcValues.foreground = columnPtr->activeTitleFgColor->pixel;
    newGC = Tk_GetGC(tvPtr->tkwin, gcMask, &gcValues);
    if (columnPtr->activeTitleGC != NULL) {
	Tk_FreeGC(tvPtr->display, columnPtr->activeTitleGC);
    }
    columnPtr->activeTitleGC = newGC;

    columnPtr->titleWidth = 0;
    iconWidth = iconHeight = 0;
    if (columnPtr->titleIcon != NULL) {
	iconWidth = TreeViewIconWidth(columnPtr->titleIcon);
	iconHeight = TreeViewIconHeight(columnPtr->titleIcon);
	columnPtr->titleWidth += iconWidth;
    }
    if (columnPtr->titleTextPtr != NULL) {
	ckfree(columnPtr->titleTextPtr);
	columnPtr->titleTextPtr = NULL;
    }
    textWidth = textHeight = 0;
    if (columnPtr->title != NULL) {
	TextStyle ts;

	memset(&ts, 0, sizeof(TextStyle));
	ts.font = columnPtr->titleFont;
	ts.justify = TK_JUSTIFY_LEFT;
	ts.shadow.offset = columnPtr->titleShadow.offset;
	columnPtr->titleTextPtr = Rbc_GetTextLayout(columnPtr->title, &ts);
	textHeight = columnPtr->titleTextPtr->height;
	textWidth = columnPtr->titleTextPtr->width;
	columnPtr->titleWidth += textWidth;
    }
    if ((iconWidth > 0) && (textWidth > 0)) {
	columnPtr->titleWidth += 8;
    }
    columnPtr->titleWidth += STD_ARROW_HEIGHT;
    columnPtr->titleHeight = MAX(iconHeight, textHeight);

    gcMask = (GCFunction | GCLineWidth | GCLineStyle | GCForeground);

    /* 
     * If the rule is active, turn it off (i.e. draw again to erase
     * it) before changing the GC.  If the color changes, we won't be
     * able to erase the old line, since it will no longer be
     * correctly XOR-ed with the background.
     */
    drawable = Tk_WindowId(tvPtr->tkwin);
    ruleDrawn = ((tvPtr->flags & TV_RULE_ACTIVE) &&
		 (tvPtr->activeTitleColumnPtr == columnPtr) && 
		 (drawable != None));
    if (ruleDrawn) {
	Rbc_TreeViewDrawRule(tvPtr, columnPtr, drawable);
    }
    /* XOR-ed rule column divider */ 
    gcValues.line_width = LineWidth(columnPtr->ruleLineWidth);
    gcValues.foreground = 
	Rbc_TreeViewGetStyleFg(tvPtr, columnPtr->stylePtr)->pixel;
    if (LineIsDashed(columnPtr->ruleDashes)) {
	gcValues.line_style = LineOnOffDash;
    } else {
	gcValues.line_style = LineSolid;
    }
    gcValues.function = GXxor;

    border = CHOOSE(tvPtr->border, columnPtr->border);
    gcValues.foreground ^= Tk_3DBorderColor(border)->pixel; 
    newGC = Rbc_GetPrivateGC(tvPtr->tkwin, gcMask, &gcValues);
    if (columnPtr->ruleGC != NULL) {
	Rbc_FreePrivateGC(tvPtr->display, columnPtr->ruleGC);
    }
    if (LineIsDashed(columnPtr->ruleDashes)) {
	Rbc_SetDashes(tvPtr->display, newGC, &columnPtr->ruleDashes);
    }
    columnPtr->ruleGC = newGC;
    if (ruleDrawn) {
	Rbc_TreeViewDrawRule(tvPtr, columnPtr, drawable);
    }
    columnPtr->flags |= COLUMN_DIRTY;
    tvPtr->flags |= TV_UPDATE;
}

static void
DestroyColumn(tvPtr, columnPtr)
    TreeView *tvPtr;
    TreeViewColumn *columnPtr;
{
    Tcl_HashEntry *hPtr;

    rbcTreeViewUidOption.clientData = tvPtr;
    rbcTreeViewIconOption.clientData = tvPtr;
    styleOption.clientData = tvPtr;
    Rbc_FreeObjOptions(columnSpecs, (char *)columnPtr, tvPtr->display, 0);

    if (columnPtr->titleGC != NULL) {
	Tk_FreeGC(tvPtr->display, columnPtr->titleGC);
    }
    if (columnPtr->ruleGC != NULL) {
	Rbc_FreePrivateGC(tvPtr->display, columnPtr->ruleGC);
    }
    hPtr = Tcl_FindHashEntry(&tvPtr->columnTable, columnPtr->key);
    if (hPtr != NULL) {
	Tcl_DeleteHashEntry(hPtr);
    }
    if (columnPtr->linkPtr != NULL) {
	Rbc_ChainDeleteLink(tvPtr->colChainPtr, columnPtr->linkPtr);
    }
    if (columnPtr->title != NULL) {
	ckfree(columnPtr->title);
    }
    if (columnPtr->titleTextPtr != NULL) {
	ckfree(columnPtr->titleTextPtr);
    }
    if (columnPtr->stylePtr != NULL) {
	Rbc_TreeViewFreeStyle(tvPtr, columnPtr->stylePtr);
    }
    if (columnPtr != &tvPtr->treeColumn) {
	ckfree(columnPtr);
    }
}

void
Rbc_TreeViewDestroyColumns(tvPtr)
    TreeView *tvPtr;
{
    if (tvPtr->colChainPtr != NULL) {
	Rbc_ChainLink *linkPtr;
	TreeViewColumn *columnPtr;
	
	for (linkPtr = Rbc_ChainFirstLink(tvPtr->colChainPtr); linkPtr != NULL;
	     linkPtr = Rbc_ChainNextLink(linkPtr)) {
	    columnPtr = Rbc_ChainGetValue(linkPtr);
	    columnPtr->linkPtr = NULL;
	    DestroyColumn(tvPtr, columnPtr);
	}
	Rbc_ChainDestroy(tvPtr->colChainPtr);
	tvPtr->colChainPtr = NULL;
    }
    Tcl_DeleteHashTable(&tvPtr->columnTable);
}

int
Rbc_TreeViewCreateColumn(tvPtr, columnPtr, name, defTitle)
    TreeView *tvPtr;
    TreeViewColumn *columnPtr;
    char *name, *defTitle;
{
    Tcl_HashEntry *hPtr;
    int isNew;

    columnPtr->key = Rbc_TreeGetKey(name);
    columnPtr->title = RbcStrdup(defTitle);
    columnPtr->justify = TK_JUSTIFY_CENTER;
    columnPtr->relief = TK_RELIEF_FLAT;
    columnPtr->borderWidth = 1;
    columnPtr->pad.side1 = columnPtr->pad.side2 = 2;
    columnPtr->state = STATE_NORMAL;
    columnPtr->weight = 1.0;
    columnPtr->editable = FALSE;
    columnPtr->ruleLineWidth = 1;
    columnPtr->titleBorderWidth = 2;
    columnPtr->titleRelief = TK_RELIEF_RAISED;
    columnPtr->titleIcon = NULL;
    hPtr = Tcl_CreateHashEntry(&tvPtr->columnTable, columnPtr->key, &isNew);
    Tcl_SetHashValue(hPtr, columnPtr);

    rbcTreeViewUidOption.clientData = tvPtr;
    rbcTreeViewIconOption.clientData = tvPtr;
    styleOption.clientData = tvPtr;
    if (Rbc_ConfigureComponentFromObj(tvPtr->interp, tvPtr->tkwin, name, 
	"Column", columnSpecs, 0, (Tcl_Obj **)NULL, (char *)columnPtr, 0) 
	!= TCL_OK) {
	DestroyColumn(tvPtr, columnPtr);
	return TCL_ERROR;
    }
    return TCL_OK;
}

static TreeViewColumn *
CreateColumn(tvPtr, nameObjPtr, objc, objv)
    TreeView *tvPtr;
    Tcl_Obj *nameObjPtr;
    int objc;
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;

    columnPtr = RbcCalloc(1, sizeof(TreeViewColumn));
    assert(columnPtr);
    if (Rbc_TreeViewCreateColumn(tvPtr, columnPtr, Tcl_GetString(nameObjPtr), 
	Tcl_GetString(nameObjPtr)) != TCL_OK) {
	return NULL;
    }
    rbcTreeViewUidOption.clientData = tvPtr;
    rbcTreeViewIconOption.clientData = tvPtr;
    styleOption.clientData = tvPtr;
    if (Rbc_ConfigureComponentFromObj(tvPtr->interp, tvPtr->tkwin, 
	columnPtr->key, "Column", columnSpecs, objc, objv, (char *)columnPtr, 
	RBC_CONFIG_OBJV_ONLY) != TCL_OK) {
	DestroyColumn(tvPtr, columnPtr);
	return NULL;
    }
    Rbc_TreeViewUpdateColumnGCs(tvPtr, columnPtr);
    return columnPtr;
}

TreeViewColumn *
Rbc_TreeViewNearestColumn(tvPtr, x, y, contextPtr)
    TreeView *tvPtr;
    int x, y;
    ClientData *contextPtr;
{
    if (tvPtr->nVisible > 0) {
	Rbc_ChainLink *linkPtr;
	TreeViewColumn *columnPtr;
	int right;

	/*
	 * Determine if the pointer is over the rightmost portion of the
	 * column.  This activates the rule.
	 */
	x = WORLDX(tvPtr, x);
	for(linkPtr = Rbc_ChainFirstLink(tvPtr->colChainPtr); linkPtr != NULL;
	    linkPtr = Rbc_ChainNextLink(linkPtr)) {
	    columnPtr = Rbc_ChainGetValue(linkPtr);
	    right = columnPtr->worldX + columnPtr->width;
	    if ((x >= columnPtr->worldX) && (x <= right)) {
		if (contextPtr != NULL) {
		    *contextPtr = NULL;
		    if ((tvPtr->flags & TV_SHOW_COLUMN_TITLES) && 
			(y >= tvPtr->inset) &&
			(y < (tvPtr->titleHeight + tvPtr->inset))) {
			*contextPtr = (x >= (right - RULE_AREA)) 
			    ? ITEM_COLUMN_RULE : ITEM_COLUMN_TITLE;
		    } 
		}
		return columnPtr;
	    }
	}
    }
    return NULL;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnActivateOp --
 *
 *	Selects the button to appear active.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnActivateOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    if (objc == 4) {
	Drawable drawable;
	TreeViewColumn *columnPtr;
	char *string;

	string = Tcl_GetString(objv[3]);
	if (string[0] == '\0') {
	    columnPtr = NULL;
	} else {
	    if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[3], &columnPtr) 
		!= TCL_OK) {
		return TCL_ERROR;
	    }
	    if (((tvPtr->flags & TV_SHOW_COLUMN_TITLES) == 0) || 
		(columnPtr->hidden) || (columnPtr->state == STATE_DISABLED)) {
		columnPtr = NULL;
	    }
	}
	tvPtr->activeTitleColumnPtr = tvPtr->activeColumnPtr = columnPtr;
	drawable = Tk_WindowId(tvPtr->tkwin);
	if (drawable != None) {
	    Rbc_TreeViewDrawHeadings(tvPtr, drawable);
	    Rbc_TreeViewDrawOuterBorders(tvPtr, drawable);
	}
    }
    if (tvPtr->activeTitleColumnPtr != NULL) {
	Tcl_SetResult(interp, tvPtr->activeTitleColumnPtr->key, TCL_VOLATILE);
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnBindOp --
 *
 *	  .t bind tag sequence command
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnBindOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    ClientData object;
    TreeViewColumn *columnPtr;

    if (Rbc_TreeViewGetColumn(NULL, tvPtr, objv[3], &columnPtr) == TCL_OK) {
	object = Rbc_TreeViewColumnTag(tvPtr, columnPtr->key);
    } else {
	object = Rbc_TreeViewColumnTag(tvPtr, Tcl_GetString(objv[3]));
    }
    return Rbc_ConfigureBindingsFromObj(interp, tvPtr->bindTable, object,
	objc - 4, objv + 4);
}


/*
 *----------------------------------------------------------------------
 *
 * ColumnCgetOp --
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnCgetOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;

    if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[3], &columnPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    return Rbc_ConfigureValueFromObj(interp, tvPtr->tkwin, columnSpecs, 
	(char *)columnPtr, objv[4], 0);
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnConfigureOp --
 *
 * 	This procedure is called to process a list of configuration
 *	options database, in order to reconfigure the one of more
 *	entries in the widget.
 *
 *	  .h entryconfigure node node node node option value
 *
 * Results:
 *	A standard Tcl result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 * Side effects:
 *	Configuration information, such as text string, colors, font,
 *	etc. get set for tvPtr; old resources get freed, if there
 *	were any.  The hypertext is redisplayed.
 *
 *----------------------------------------------------------------------
 */
static int
ColumnConfigureOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;
    int nOptions, start;
    register int i;

    /* Figure out where the option value pairs begin */
    for(i = 3; i < objc; i++) {
	if (Rbc_ObjIsOption(columnSpecs, objv[i], 0)) {
	    break;
	}
	if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[i], &columnPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    start = i;
    nOptions = objc - start;
    
    rbcTreeViewUidOption.clientData = tvPtr;
    rbcTreeViewIconOption.clientData = tvPtr;
    styleOption.clientData = tvPtr;
    for (i = 3; i < start; i++) {
	if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[i], &columnPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	if (nOptions == 0) {
	    return Rbc_ConfigureInfoFromObj(interp, tvPtr->tkwin, columnSpecs, 
		(char *)columnPtr, (Tcl_Obj *)NULL, 0);
	} else if (nOptions == 1) {
	    return Rbc_ConfigureInfoFromObj(interp, tvPtr->tkwin, columnSpecs, 
		(char *)columnPtr, objv[start], 0);
	}
	if (Rbc_ConfigureWidgetFromObj(tvPtr->interp, tvPtr->tkwin, 
	       columnSpecs, nOptions, objv + start, (char *)columnPtr, 
		RBC_CONFIG_OBJV_ONLY) != TCL_OK) {
	    return TCL_ERROR;
	}
	Rbc_TreeViewUpdateColumnGCs(tvPtr, columnPtr);
    }
    /*FIXME: Makes every change redo everything. */
    tvPtr->flags |= (TV_LAYOUT | TV_DIRTY);
    Rbc_TreeViewEventuallyRedraw(tvPtr);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnDeleteOp --
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnDeleteOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;		/* Not used. */
    int objc;
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;
    TreeViewEntry *entryPtr;
    register int i;

    for(i = 3; i < objc; i++) {
	if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[i], &columnPtr) 
	    != TCL_OK) {
	    return TCL_ERROR;
	}
	/* Traverse the tree deleting values associated with the column.  */
	for(entryPtr = tvPtr->rootPtr; entryPtr != NULL;
	    entryPtr = Rbc_TreeViewNextEntry(entryPtr, 0)) {
	    if (entryPtr != NULL) {
		TreeViewValue *valuePtr, *lastPtr, *nextPtr;
		
		lastPtr = NULL;
		for (valuePtr = entryPtr->values; valuePtr != NULL; 
		     valuePtr = nextPtr) {
		    nextPtr = valuePtr->nextPtr;
		    if (valuePtr->columnPtr == columnPtr) {
			Rbc_TreeViewDestroyValue(tvPtr, valuePtr);
			if (lastPtr == NULL) {
			    entryPtr->values = nextPtr;
			} else {
			    lastPtr->nextPtr = nextPtr;
			}
			break;
		    }
		    lastPtr = valuePtr;
		}
	    }
	}
	DestroyColumn(tvPtr, columnPtr);
    }
    /* Deleting a column may affect the height of an entry. */
    tvPtr->flags |= (TV_LAYOUT | TV_DIRTY | TV_RESORT);
    Rbc_TreeViewEventuallyRedraw(tvPtr);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnInsertOp --
 *
 *	Add new columns to the tree.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnInsertOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
{
    Rbc_ChainLink *beforePtr;
    Tcl_Obj *CONST *options;
    TreeViewColumn *columnPtr;
    TreeViewEntry *entryPtr;
    int insertPos;
    int nOptions;
    int start;
    register int i;

    if (Rbc_GetPositionFromObj(tvPtr->interp, objv[3], &insertPos) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((insertPos == -1) || 
	(insertPos >= Rbc_ChainGetLength(tvPtr->colChainPtr))) {
	beforePtr = NULL;
    } else {
	beforePtr =  Rbc_ChainGetNthLink(tvPtr->colChainPtr, insertPos);
    }
    /*
     * Count the column names that follow.  Count the arguments until we
     * spot one that looks like a configuration option (i.e. starts
     * with a minus ("-")).
     */
    for (i = 4; i < objc; i++) {
	if (Rbc_ObjIsOption(columnSpecs, objv[i], 0)) {
	    break;
	}
    }
    start = i;
    nOptions = objc - i;
    options = objv + start;

    for (i = 4; i < start; i++) {
	if (Rbc_TreeViewGetColumn(NULL, tvPtr, objv[i], &columnPtr) == TCL_OK) {
	    Tcl_AppendResult(interp, "column \"", Tcl_GetString(objv[i]), 
		"\" already exists", (char *)NULL);
	    return TCL_ERROR;
	}
	columnPtr = CreateColumn(tvPtr, objv[i], nOptions, options);
	if (columnPtr == NULL) {
	    return TCL_ERROR;
	}
	if (beforePtr == NULL) {
	    columnPtr->linkPtr = Rbc_ChainAppend(tvPtr->colChainPtr, columnPtr);
	} else {
	    columnPtr->linkPtr = Rbc_ChainNewLink();
	    Rbc_ChainSetValue(columnPtr->linkPtr, columnPtr);
	    Rbc_ChainLinkBefore(tvPtr->colChainPtr, columnPtr->linkPtr, 
		beforePtr);
	}
	/* 
	 * Traverse the tree adding column entries where needed.
	 */
	for(entryPtr = tvPtr->rootPtr; entryPtr != NULL;
	    entryPtr = Rbc_TreeViewNextEntry(entryPtr, 0)) {
	    Rbc_TreeViewAddValue(entryPtr, columnPtr);
	}
	Rbc_TreeViewTraceColumn(tvPtr, columnPtr);
    }
    Rbc_TreeViewEventuallyRedraw(tvPtr);
    return TCL_OK;
}



/*
 *----------------------------------------------------------------------
 *
 * ColumnCurrentOp --
 *
 *	Make the rule to appear active.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnCurrentOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;	/* Not used. */
{
    ClientData context;
    TreeViewColumn *columnPtr;

    columnPtr = NULL;
    context = Rbc_GetCurrentContext(tvPtr->bindTable);
    if ((context == ITEM_COLUMN_TITLE) || (context == ITEM_COLUMN_RULE)) {
	columnPtr = Rbc_GetCurrentItem(tvPtr->bindTable);
    }
    if (context >= ITEM_STYLE) {
	TreeViewValue *valuePtr = context;
	
	columnPtr = valuePtr->columnPtr;
    }
    if (columnPtr != NULL) {
	Tcl_SetResult(interp, columnPtr->key, TCL_VOLATILE);
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnInvokeOp --
 *
 * 	This procedure is called to invoke a column command.
 *
 *	  .h column invoke columnName
 *
 * Results:
 *	A standard Tcl result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnInvokeOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;		/* Not used. */
    int objc;
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;
    char *string;

    string = Tcl_GetString(objv[3]);
    if (string[0] == '\0') {
	return TCL_OK;
    }
    if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[3], &columnPtr) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((columnPtr->state == STATE_NORMAL) && (columnPtr->titleCmd != NULL)) {
	int result;

	Tcl_Preserve(tvPtr);
	Tcl_Preserve(columnPtr);
	result = Tcl_GlobalEval(interp, columnPtr->titleCmd);
	Tcl_Release(columnPtr);
	Tcl_Release(tvPtr);
	return result;
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ColumnMoveOp --
 *
 *	Move a column.
 *
 * .h column move field1 position
 *----------------------------------------------------------------------
 */

/*
 *----------------------------------------------------------------------
 *
 * ColumnNamesOp --
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ColumnNamesOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;		/* Not used. */
{
    Rbc_ChainLink *linkPtr;
    Tcl_Obj *listObjPtr, *objPtr;
    TreeViewColumn *columnPtr;

    listObjPtr = Tcl_NewListObj(0, (Tcl_Obj **)NULL);
    for(linkPtr = Rbc_ChainFirstLink(tvPtr->colChainPtr); linkPtr != NULL;
	linkPtr = Rbc_ChainNextLink(linkPtr)) {
	columnPtr = Rbc_ChainGetValue(linkPtr);
	objPtr = Tcl_NewStringObj(columnPtr->key, -1);
	Tcl_ListObjAppendElement(interp, listObjPtr, objPtr);
    }
    Tcl_SetObjResult(interp, listObjPtr);
    return TCL_OK;
}

/*ARGSUSED*/
static int
ColumnNearestOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    int x, y;			/* Screen coordinates of the test point. */
    TreeViewColumn *columnPtr;
    ClientData context;
    int checkTitle;
#ifdef notdef
    int isRoot;

    isRoot = FALSE;
    string = Tcl_GetString(objv[3]);

    if (strcmp("-root", string) == 0) {
	isRoot = TRUE;
	objv++, objc--;
    }
    if (objc != 5) {
	Tcl_AppendResult(interp, "wrong # args: should be \"", 
		Tcl_GetString(objv[0]), " ", Tcl_GetString(objv[1]), 
		Tcl_GetString(objv[2]), " ?-root? x y\"", (char *)NULL);
	return TCL_ERROR;
			 
    }
#endif
    if (Tk_GetPixelsFromObj(interp, tvPtr->tkwin, objv[3], &x) != TCL_OK) {
	return TCL_ERROR;
    } 
    y = 0;
    checkTitle = FALSE;
    if (objc == 5) {
	if (Tk_GetPixelsFromObj(interp, tvPtr->tkwin, objv[4], &y) != TCL_OK) {
	    return TCL_ERROR;
	}
	checkTitle = TRUE;
    }
    columnPtr = Rbc_TreeViewNearestColumn(tvPtr, x, y, &context);
    if ((checkTitle) && (context == NULL)) {
	columnPtr = NULL;
    }
    if (columnPtr != NULL) {
	Tcl_SetResult(interp, columnPtr->key, TCL_VOLATILE);
    }
    return TCL_OK;
}

static void
UpdateMark(tvPtr, newMark)
    TreeView *tvPtr;
    int newMark;
{
    Drawable drawable;
    TreeViewColumn *columnPtr;
    int dx;
    int width;

    columnPtr = tvPtr->resizeColumnPtr;
    if (columnPtr == NULL) {
	return;
    }
    drawable = Tk_WindowId(tvPtr->tkwin);
    if (drawable == None) {
	return;
    }

    /* Erase any existing rule. */
    if (tvPtr->flags & TV_RULE_ACTIVE) { 
	Rbc_TreeViewDrawRule(tvPtr, columnPtr, drawable);
    }
    
    dx = newMark - tvPtr->ruleAnchor; 
    width = columnPtr->width - 
	(PADDING(columnPtr->pad) + 2 * columnPtr->borderWidth);
    if ((columnPtr->reqMin > 0) && ((width + dx) < columnPtr->reqMin)) {
	dx = columnPtr->reqMin - width;
    }
    if ((columnPtr->reqMax > 0) && ((width + dx) > columnPtr->reqMax)) {
	dx = columnPtr->reqMax - width;
    }
    if ((width + dx) < 4) {
	dx = 4 - width;
    }
    tvPtr->ruleMark = tvPtr->ruleAnchor + dx;

    /* Redraw the rule if required. */
    if (tvPtr->flags & TV_RULE_NEEDED) {
	Rbc_TreeViewDrawRule(tvPtr, columnPtr, drawable);
    }
}

/*
 *----------------------------------------------------------------------
 *
 * ResizeActivateOp --
 *
 *	Turns on/off the resize cursor.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ResizeActivateOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    TreeViewColumn *columnPtr;
    char *string;

    string = Tcl_GetString(objv[4]);
    if (string[0] == '\0') {
	if (tvPtr->cursor != None) {
	    Tk_DefineCursor(tvPtr->tkwin, tvPtr->cursor);
	} else {
	    Tk_UndefineCursor(tvPtr->tkwin);
	}
	tvPtr->resizeColumnPtr = NULL;
    } else if (Rbc_TreeViewGetColumn(interp, tvPtr, objv[4], &columnPtr) 
	       == TCL_OK) {
	if (tvPtr->resizeCursor != None) {
	    Tk_DefineCursor(tvPtr->tkwin, tvPtr->resizeCursor);
	} 
	tvPtr->resizeColumnPtr = columnPtr;
    } else {
	return TCL_ERROR;
    }
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ResizeAnchorOp --
 *
 *	Set the anchor for the resize.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ResizeAnchorOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    int x;

    if (Tcl_GetIntFromObj(NULL, objv[4], &x) != TCL_OK) {
	return TCL_ERROR;
    } 
    tvPtr->ruleAnchor = x;
    tvPtr->flags |= TV_RULE_NEEDED;
    UpdateMark(tvPtr, x);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ResizeMarkOp --
 *
 *	Sets the resize mark.  The distance between the mark and the anchor
 *	is the delta to change the width of the active column.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ResizeMarkOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    int x;

    if (Tcl_GetIntFromObj(NULL, objv[4], &x) != TCL_OK) {
	return TCL_ERROR;
    } 
    tvPtr->flags |= TV_RULE_NEEDED;
    UpdateMark(tvPtr, x);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * ResizeSetOp --
 *
 *	Returns the new width of the column including the resize delta.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
ResizeSetOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;	/* Not used. */
{
    tvPtr->flags &= ~TV_RULE_NEEDED;
    UpdateMark(tvPtr, tvPtr->ruleMark);
    if (tvPtr->resizeColumnPtr != NULL) {
	int width, delta;
	TreeViewColumn *columnPtr;

	columnPtr = tvPtr->resizeColumnPtr;
	delta = (tvPtr->ruleMark - tvPtr->ruleAnchor);
	width = tvPtr->resizeColumnPtr->width + delta - 
	    (PADDING(columnPtr->pad) + 2 * columnPtr->borderWidth) - 1;
	Tcl_SetObjResult(interp, Tcl_NewIntObj(width));
    }
    return TCL_OK;
}

static Rbc_OpSpec resizeOps[] =
{ 
    {"activate", 2, (Rbc_Op)ResizeActivateOp, 5, 5, "column"},
    {"anchor", 2, (Rbc_Op)ResizeAnchorOp, 5, 5, "x"},
    {"mark", 1, (Rbc_Op)ResizeMarkOp, 5, 5, "x"},
    {"set", 1, (Rbc_Op)ResizeSetOp, 4, 4, "",},
};

static int nResizeOps = sizeof(resizeOps) / sizeof(Rbc_OpSpec);

/*
 *----------------------------------------------------------------------
 *
 * ColumnResizeOp --
 *
 *----------------------------------------------------------------------
 */
static int
ColumnResizeOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
{
    Rbc_Op proc;
    int result;

    proc = Rbc_GetOpFromObj(interp, nResizeOps, resizeOps, RBC_OP_ARG3, 
	objc, objv,0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (tvPtr, interp, objc, objv);
    return result;
}


static Rbc_OpSpec columnOps[] =
{
    {"activate", 1, (Rbc_Op)ColumnActivateOp, 3, 4, "?field?",},
    {"bind", 1, (Rbc_Op)ColumnBindOp, 4, 6, "tagName ?sequence command?",},
    {"cget", 2, (Rbc_Op)ColumnCgetOp, 5, 5, "field option",},
    {"configure", 2, (Rbc_Op)ColumnConfigureOp, 4, 0, 
	"field ?option value?...",},
    {"current", 2, (Rbc_Op)ColumnCurrentOp, 3, 3, "",},
    {"delete", 1, (Rbc_Op)ColumnDeleteOp, 3, 0, "?field...?",},
    {"highlight", 1, (Rbc_Op)ColumnActivateOp, 3, 4, "?field?",},
    {"insert", 3, (Rbc_Op)ColumnInsertOp, 5, 0, 
	"position field ?field...? ?option value?...",},
    {"invoke", 3, (Rbc_Op)ColumnInvokeOp, 4, 4, "field",},
    {"names", 2, (Rbc_Op)ColumnNamesOp, 3, 3, "",},
    {"nearest", 2, (Rbc_Op)ColumnNearestOp, 4, 5, "x ?y?",},
    {"resize", 1, (Rbc_Op)ColumnResizeOp, 3, 0, "arg",},
};
static int nColumnOps = sizeof(columnOps) / sizeof(Rbc_OpSpec);

/*
 *----------------------------------------------------------------------
 *
 * Rbc_TreeViewColumnOp --
 *
 *----------------------------------------------------------------------
 */
int
Rbc_TreeViewColumnOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
{
    Rbc_Op proc;
    int result;

    proc = Rbc_GetOpFromObj(interp, nColumnOps, columnOps, RBC_OP_ARG2, 
	objc, objv,0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (tvPtr, interp, objc, objv);
    return result;
}


static int
InvokeCompare(tvPtr, e1Ptr, e2Ptr, command)
    TreeView *tvPtr;
    TreeViewEntry *e1Ptr, *e2Ptr;
    char *command;
{
    int result;
    Tcl_Obj *objv[8];
    int i;

    objv[0] = Tcl_NewStringObj(command, -1);
    objv[1] = Tcl_NewStringObj(Tk_PathName(tvPtr->tkwin), -1);
    objv[2] = Tcl_NewIntObj(Rbc_TreeNodeId(e1Ptr->node));
    objv[3] = Tcl_NewIntObj(Rbc_TreeNodeId(e2Ptr->node));
    objv[4] = Tcl_NewStringObj(tvPtr->sortColumnPtr->key, -1);
	     
    if (tvPtr->flatView) {
	objv[5] = Tcl_NewStringObj(e1Ptr->fullName, -1);
	objv[6] = Tcl_NewStringObj(e2Ptr->fullName, -1);
    } else {
	objv[5] = Tcl_NewStringObj(GETLABEL(e1Ptr), -1);
	objv[6] = Tcl_NewStringObj(GETLABEL(e2Ptr), -1);
    }
    for(i = 0; i < 7; i++) {
	Tcl_IncrRefCount(objv[i]);
    }
    objv[7] = NULL;
    result = Tcl_EvalObjv(tvPtr->interp, 7, objv, TCL_EVAL_GLOBAL);
    if ((result != TCL_OK) ||
	(Tcl_GetIntFromObj(tvPtr->interp, Tcl_GetObjResult(tvPtr->interp), 
			   &result) != TCL_OK)) {
	Tcl_BackgroundError(tvPtr->interp);
    }
    for(i = 0; i < 7; i++) {
	Tcl_DecrRefCount(objv[i]);
    }
    Tcl_ResetResult(tvPtr->interp);
    return result;
}

static TreeView *treeViewInstance;

static int
CompareEntries(a, b)
    CONST void *a, *b;
{
    TreeView *tvPtr;
    TreeViewEntry **e1PtrPtr = (TreeViewEntry **)a;
    TreeViewEntry **e2PtrPtr = (TreeViewEntry **)b;
    Tcl_Obj *obj1, *obj2;
    char *s1, *s2;
    int result;

    tvPtr = (*e1PtrPtr)->tvPtr;
    obj1 = (*e1PtrPtr)->dataObjPtr;
    obj2 = (*e2PtrPtr)->dataObjPtr;

    // MVvar("obj1<%p>, obj2<%p>",obj1,obj2);
    //  OTBUG: hiertable1.tcl→1.sorting "View" (multiple click), 2. sorting "nlink"
    //  ==64390== Invalid read of size 8
    //  ==64390==    at 0x5372D40: Tcl_GetString (tclObj.c:1642)
    //  ==64390==    by 0x7342187: CompareEntries (rbcTreeViewColumn.c:1587)
    //  ==64390==    by 0x62D95A0: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D92F1: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D92F1: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D92F1: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D92F1: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D92F1: msort_with_tmp.part.0 (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x62D984B: qsort_r (in /lib64/libc-2.22.so)
    //  ==64390==    by 0x734300D: Rbc_TreeViewSortFlatView (rbcTreeViewColumn.c:2013)
    //  ==64390==    by 0x732877D: ComputeFlatLayout (rbcTreeView.c:3572)
    //  ==64390==    by 0x73291C4: Rbc_TreeViewComputeLayout (rbcTreeView.c:3848)
    //  ==64390==  Address 0x18 is not stack'd, malloc'd or (recently) free'd
    //
    // solved… rbcEmptyStringObjPtr, initialized in Rbc_Init had no
    //         Tcl_IncrRefCount

    s1 = Tcl_GetString(obj1);
    s2 = Tcl_GetString(obj2);
    result = 0;
    switch (tvPtr->sortType) {
    case SORT_TYPE_ASCII:
	result = strcmp(s1, s2);
	break;

    case SORT_TYPE_COMMAND:
	{
	    char *cmd;

	    cmd = tvPtr->sortColumnPtr->sortCmd;
	    if (cmd == NULL) {
		cmd = tvPtr->sortCmd;
	    }
	    if (cmd == NULL) {
		result = Rbc_DictionaryCompare(s1, s2);
	    } else {
		result = InvokeCompare(tvPtr, *e1PtrPtr, *e2PtrPtr, cmd);
	    }
	}
	break;

    case SORT_TYPE_DICTIONARY:
	result = Rbc_DictionaryCompare(s1, s2);
	break;

    case SORT_TYPE_INTEGER:
	{
	    int i1, i2;

	    if (Tcl_GetIntFromObj(NULL, obj1, &i1)==TCL_OK) {
		if (Tcl_GetIntFromObj(NULL, obj2, &i2) == TCL_OK) {
		    result = i1 - i2;
		} else {
		    result = -1;
		} 
	    } else if (Tcl_GetIntFromObj(NULL, obj2, &i2) == TCL_OK) {
		result = 1;
	    } else {
		result = Rbc_DictionaryCompare(s1, s2);
	    }
	}
	break;

    case SORT_TYPE_REAL:
	{
	    double r1, r2;

	    if (Tcl_GetDoubleFromObj(NULL, obj1, &r1) == TCL_OK) {
		if (Tcl_GetDoubleFromObj(NULL, obj2, &r2) == TCL_OK) {
		    result = (r1 < r2) ? -1 : (r1 > r2) ? 1 : 0;
		} else {
		    result = -1;
		} 
	    } else if (Tcl_GetDoubleFromObj(NULL, obj2, &r2) == TCL_OK) {
		result = 1;
	    } else {
		result = Rbc_DictionaryCompare(s1, s2);
	    }
	}
	break;
    }
    if (tvPtr->sortDecreasing) {
	return -result;
    } 
    return result;
}


/*
 *----------------------------------------------------------------------
 *
 * CompareNodes --
 *
 *	Comparison routine (used by qsort) to sort a chain of subnodes.
 *
 * Results:
 *	1 is the first is greater, -1 is the second is greater, 0
 *	if equal.
 *
 *----------------------------------------------------------------------
 */
static int
CompareNodes(n1Ptr, n2Ptr)
    Rbc_TreeNode *n1Ptr, *n2Ptr;
{
    TreeView *tvPtr = treeViewInstance;
    TreeViewEntry *e1Ptr, *e2Ptr;

    e1Ptr = Rbc_NodeToEntry(tvPtr, *n1Ptr);
    e2Ptr = Rbc_NodeToEntry(tvPtr, *n2Ptr);

    /* Fetch the data for sorting. */
    if (tvPtr->sortType == SORT_TYPE_COMMAND) {
	e1Ptr->dataObjPtr = Tcl_NewIntObj(Rbc_TreeNodeId(*n1Ptr));
	e2Ptr->dataObjPtr = Tcl_NewIntObj(Rbc_TreeNodeId(*n2Ptr));
    } else if (tvPtr->sortColumnPtr == &tvPtr->treeColumn) {
	Tcl_DString dString;

	Tcl_DStringInit(&dString);
	if (e1Ptr->fullName == NULL) {
	    Rbc_TreeViewGetFullName(tvPtr, e1Ptr, TRUE, &dString);
	    e1Ptr->fullName = RbcStrdup(Tcl_DStringValue(&dString));
	}
	e1Ptr->dataObjPtr = Tcl_NewStringObj(e1Ptr->fullName, -1);
	if (e2Ptr->fullName == NULL) {
	    Rbc_TreeViewGetFullName(tvPtr, e2Ptr, TRUE, &dString);
	    e2Ptr->fullName = RbcStrdup(Tcl_DStringValue(&dString));
	}
	e2Ptr->dataObjPtr = Tcl_NewStringObj(e2Ptr->fullName, -1);
	Tcl_DStringFree(&dString);
    } else {
	Rbc_TreeKey key;
	Tcl_Obj *objPtr;

	key = tvPtr->sortColumnPtr->key;
	if (Rbc_TreeViewGetData(e1Ptr, key, &objPtr) != TCL_OK) {
	    e1Ptr->dataObjPtr = rbcEmptyStringObjPtr;
	} else {
	    e1Ptr->dataObjPtr = objPtr;
	}
	if (Rbc_TreeViewGetData(e2Ptr, key, &objPtr) != TCL_OK) {
	    e2Ptr->dataObjPtr = rbcEmptyStringObjPtr;
	} else {
	    e2Ptr->dataObjPtr = objPtr;
	}
    }
    return CompareEntries(&e1Ptr, &e2Ptr);
}

static int
SortAutoOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;		/* Not used. */
    int objc;
    Tcl_Obj *CONST *objv;
{

    if (objc == 4) {
	int bool;
	int isAuto;

	isAuto = ((tvPtr->flags & TV_SORT_AUTO) != 0);
	if (Tcl_GetBooleanFromObj(interp, objv[3], &bool) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (isAuto != bool) {
	    tvPtr->flags |= (TV_LAYOUT | TV_DIRTY | TV_RESORT);
	    Rbc_TreeViewEventuallyRedraw(tvPtr);
	}
	if (bool) {
	    tvPtr->flags |= TV_SORT_AUTO;
	} else {
	    tvPtr->flags &= ~TV_SORT_AUTO;
	}
    }
    Tcl_SetObjResult(interp, Tcl_NewBooleanObj(tvPtr->flags & TV_SORT_AUTO));
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * SortCgetOp --
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
SortCgetOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;			/* Not used. */
    Tcl_Obj *CONST *objv;
{
    return Rbc_ConfigureValueFromObj(interp, tvPtr->tkwin, sortSpecs, 
	(char *)tvPtr, objv[3], 0);
}

/*
 *----------------------------------------------------------------------
 *
 * SortConfigureOp --
 *
 * 	This procedure is called to process a list of configuration
 *	options database, in order to reconfigure the one of more
 *	entries in the widget.
 *
 *	  .h sort configure option value
 *
 * Results:
 *	A standard Tcl result.  If TCL_ERROR is returned, then
 *	interp->result contains an error message.
 *
 * Side effects:
 *	Configuration information, such as text string, colors, font,
 *	etc. get set for tvPtr; old resources get freed, if there
 *	were any.  The hypertext is redisplayed.
 *
 *----------------------------------------------------------------------
 */
static int
SortConfigureOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;
    int objc;
    Tcl_Obj *CONST *objv;
{
    int oldType;
    char *oldCommand;
    TreeViewColumn *oldColumn;

    if (objc == 3) {
	return Rbc_ConfigureInfoFromObj(interp, tvPtr->tkwin, sortSpecs, 
		(char *)tvPtr, (Tcl_Obj *)NULL, 0);
    } else if (objc == 4) {
	return Rbc_ConfigureInfoFromObj(interp, tvPtr->tkwin, sortSpecs, 
		(char *)tvPtr, objv[3], 0);
    }
    oldColumn = tvPtr->sortColumnPtr;
    oldType = tvPtr->sortType;
    oldCommand = tvPtr->sortCmd;
    if (Rbc_ConfigureWidgetFromObj(interp, tvPtr->tkwin, sortSpecs, 
	objc - 3, objv + 3, (char *)tvPtr, RBC_CONFIG_OBJV_ONLY) != TCL_OK) {
	return TCL_ERROR;
    }
    if ((oldColumn != tvPtr->sortColumnPtr) ||
	(oldType != tvPtr->sortType) ||
	(oldCommand != tvPtr->sortCmd)) {
	tvPtr->flags &= ~TV_SORTED;
	tvPtr->flags |= (TV_DIRTY | TV_RESORT);
    } 
    if (tvPtr->flags & TV_SORT_AUTO) {
	tvPtr->flags |= TV_SORT_PENDING;
    }
    Rbc_TreeViewEventuallyRedraw(tvPtr);
    return TCL_OK;
}

/*ARGSUSED*/
static int
SortOnceOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;		/* Not used. */
    int objc;
    Tcl_Obj *CONST *objv;
{
    TreeViewEntry *entryPtr;
    int recurse, result;
    register int i;

    recurse = FALSE;
    if (objc > 3) {
	char *string;
	int length;

	string = Tcl_GetStringFromObj(objv[3], &length);
	if ((string[0] == '-') && (length > 1) &&
	    (strncmp(string, "-recurse", length) == 0)) {
	    objv++, objc--;
	    recurse = TRUE;
	}
    }
    for (i = 3; i < objc; i++) {
	if (Rbc_TreeViewGetEntry(tvPtr, objv[i], &entryPtr) != TCL_OK) {
	    return TCL_ERROR;
	}
	if (recurse) {
	    result = Rbc_TreeApply(entryPtr->node, SortApplyProc, tvPtr);
	} else {
	    result = SortApplyProc(entryPtr->node, tvPtr, TREE_PREORDER);
	}
	if (result != TCL_OK) {
	    return TCL_ERROR;
	}
    }
    tvPtr->flags |= TV_LAYOUT;
    Rbc_TreeViewEventuallyRedraw(tvPtr);
    return TCL_OK;
}

/*
 *----------------------------------------------------------------------
 *
 * Rbc_TreeViewSortOp --
 *
 *	Comparison routine (used by qsort) to sort a chain of subnodes.
 *	A simple string comparison is performed on each node name.
 *
 *	.h sort auto
 *	.h sort once -recurse root
 *
 * Results:
 *	1 is the first is greater, -1 is the second is greater, 0
 *	if equal.
 *
 *----------------------------------------------------------------------
 */
static Rbc_OpSpec sortOps[] =
{
    {"auto", 1, (Rbc_Op)SortAutoOp, 3, 4, "?boolean?",},
    {"cget", 2, (Rbc_Op)SortCgetOp, 4, 4, "option",},
    {"configure", 2, (Rbc_Op)SortConfigureOp, 3, 0, "?option value?...",},
    {"once", 1, (Rbc_Op)SortOnceOp, 3, 0, "?-recurse? node...",},
};
static int nSortOps = sizeof(sortOps) / sizeof(Rbc_OpSpec);

/*ARGSUSED*/
int
Rbc_TreeViewSortOp(tvPtr, interp, objc, objv)
    TreeView *tvPtr;
    Tcl_Interp *interp;		/* Not used. */
    int objc;
    Tcl_Obj *CONST *objv;
{
    Rbc_Op proc;
    int result;

    proc = Rbc_GetOpFromObj(interp, nSortOps, sortOps, RBC_OP_ARG2, objc, 
	    objv, 0);
    if (proc == NULL) {
	return TCL_ERROR;
    }
    result = (*proc) (tvPtr, interp, objc, objv);
    return result;
}

/*
 *----------------------------------------------------------------------
 *
 * SortApplyProc --
 *
 *	Sorts the subnodes at a given node.
 *
 * Results:
 *	Always returns TCL_OK.
 *
 *----------------------------------------------------------------------
 */
/*ARGSUSED*/
static int
SortApplyProc(node, clientData, order)
    Rbc_TreeNode node;
    ClientData clientData;
    int order;			/* Not used. */
{
    TreeView *tvPtr = clientData;

    if (!Rbc_TreeIsLeaf(node)) {
	Rbc_TreeSortNode(tvPtr->tree, node, CompareNodes);
    }
    return TCL_OK;
}
 
/*
 *----------------------------------------------------------------------
 *
 * Rbc_TreeViewSortFlatView --
 *
 *	Sorts the flatten array of entries.
 *
 *----------------------------------------------------------------------
 */
void
Rbc_TreeViewSortFlatView(tvPtr)
    TreeView *tvPtr;
{
    TreeViewEntry *entryPtr, **p;

    tvPtr->flags &= ~TV_SORT_PENDING;
    if ((tvPtr->sortType == SORT_TYPE_NONE) || (tvPtr->sortColumnPtr == NULL) ||
	(tvPtr->nEntries == 1)) {
	return;
    }
    if (tvPtr->flags & TV_SORTED) {
	int first, last;
	TreeViewEntry *hold;

	if (tvPtr->sortDecreasing == tvPtr->viewIsDecreasing) {
	    return;
	}

	/* 
	 * The view is already sorted but in the wrong direction. 
	 * Reverse the entries in the array.
	 */
 	for (first = 0, last = tvPtr->nEntries - 1; last > first; 
	     first++, last--) {
	    hold = tvPtr->flatArr[first];
	    tvPtr->flatArr[first] = tvPtr->flatArr[last];
	    tvPtr->flatArr[last] = hold;
	}
	tvPtr->viewIsDecreasing = tvPtr->sortDecreasing;
	tvPtr->flags |= TV_SORTED | TV_LAYOUT;
	return;
    }
    /* Fetch each entry's data as Tcl_Objs for sorting. */
    if (tvPtr->sortColumnPtr == &tvPtr->treeColumn) {
	for(p = tvPtr->flatArr; *p != NULL; p++) {
	    entryPtr = *p;
	    if (entryPtr->fullName == NULL) {
		Tcl_DString dString;

		Rbc_TreeViewGetFullName(tvPtr, entryPtr, TRUE, &dString);
		entryPtr->fullName = RbcStrdup(Tcl_DStringValue(&dString));
		Tcl_DStringFree(&dString);
	    }
	    entryPtr->dataObjPtr = Tcl_NewStringObj(entryPtr->fullName, -1);
	    Tcl_IncrRefCount(entryPtr->dataObjPtr);
	}
    } else {
	Rbc_TreeKey key;
	Tcl_Obj *objPtr;

	key = tvPtr->sortColumnPtr->key;
	for(p = tvPtr->flatArr; *p != NULL; p++) {
	    entryPtr = *p;
	    if (Rbc_TreeViewGetData(entryPtr, key, &objPtr) != TCL_OK) {
		objPtr = rbcEmptyStringObjPtr;
	    }
	    entryPtr->dataObjPtr = objPtr;
	    Tcl_IncrRefCount(entryPtr->dataObjPtr);
	}
    }
    qsort((char *)tvPtr->flatArr, tvPtr->nEntries, sizeof(TreeViewEntry *),
	  (QSortCompareProc *)CompareEntries);

    /* Free all the Tcl_Objs used for comparison data. */
    for(p = tvPtr->flatArr; *p != NULL; p++) {
	Tcl_DecrRefCount((*p)->dataObjPtr);
    }
    tvPtr->viewIsDecreasing = tvPtr->sortDecreasing;
    tvPtr->flags |= TV_SORTED;
}

/*
 *----------------------------------------------------------------------
 *
 * Rbc_TreeViewSortTreeView --
 *
 *	Sorts the tree array of entries.
 *
 *----------------------------------------------------------------------
 */
void
Rbc_TreeViewSortTreeView(tvPtr)
    TreeView *tvPtr;
{
    tvPtr->flags &= ~TV_SORT_PENDING;
    if ((tvPtr->sortType != SORT_TYPE_NONE) && (tvPtr->sortColumnPtr != NULL)) {
	treeViewInstance = tvPtr;
	Rbc_TreeApply(tvPtr->rootPtr->node, SortApplyProc, tvPtr);
    }
    tvPtr->viewIsDecreasing = tvPtr->sortDecreasing;
}

// vim: nowrap
