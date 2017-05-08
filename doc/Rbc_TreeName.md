

NAME
====

Rbc\_TreeName \- Returns the name of the tree data object\.

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

char \*  
__Rbc\_TreeName__(*tree*)  

ARGUMENTS
=========

Rbc\_Tree   *tree*   (in)      Token for the tree object\.

DESCRIPTION
===========

This procedure returns the name of the C\-based tree data object\.  The
arguments are as follows:  

*tree*
:   Token for the tree object\.  The token must have been
    previously obtained via __Rbc\_TreeGetToken__ or __Rbc\_TreeCreate__\.

RETURNS
=======

The name of the tree object is returned\.  The name will be fully
qualified with a namespace context\.  

EXAMPLE
=======

The following example prints the name of the new tree\.

~~~~~
Rbc_Tree token;

if (Rbc_TreeCreate(interp, NULL, &token) != TCL_OK) {
    return TCL_ERROR;
}
printf("tree is %s\n", Rbc_TreeName(token));
~~~~~

KEYWORDS
========

Tcl\_TreeGetToken, Tcl\_TreeExists, Tcl\_TreeReleaseToken

