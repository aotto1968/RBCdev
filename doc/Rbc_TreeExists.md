

NAME
====

Rbc\_TreeExists \- Indicates if a tree exists\.  

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

int  
__Rbc\_TreeExists__(*interp*, *name*)  

ARGUMENTS
=========


Tcl\_Interp   *\*interp*   (in)
:   Interpreter to determine current
    namespace context\.  

const char   *\*name*     (in)
:   Name of an existing tree data object\.
    Can be qualified by a namespace\.

DESCRIPTION
===========

This procedure determines if a C\-based tree data object exists by a
given name\. The arguments are as follows:  

interp
:   Used the determine the current namespace context\.

name
:   Name of an existing tree data object\.  *Name* can be qualified
    by a namespace such as fred::myTree\.  If no namespace
    qualifier is used, the current namespace is searched, then
    the global namespace\.  

RETURNS
=======

A boolean result is returned\.  If the tree exists 1 is returned, 0
otherwise\.  

EXAMPLE
=======

The following example checks if a tree "myTree" exists\.

~~~~~
if (!Rbc_TreeExists(interp, "myTree")) {
    fprintf(stderr, "can't find tree \"myTree\\n");
}
~~~~~

KEYWORDS
========

tree, token Tcl\_TreeCreate, Tcl\_TreeGetToken, Tcl\_TreeReleaseToken

