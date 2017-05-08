

NAME
====

Rbc\_TreeGetToken \- Grabs a token associated with existing tree data
object\.  

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

int  
__Rbc\_TreeGetToken__(*interp*, *name*, *tokenPtr*)  

ARGUMENTS
=========


Tcl\_Interp   *\*interp*   (in)
:   Interpreter to report results back to\.

const char   *\*name*     (in)
:   Name of an existing tree data object\.
    Can be qualified by a namespace\.

Rbc\_Tree     *\*tokenPtr* (out)
:   Points to location to store the client
    tree token\.  

DESCRIPTION
===========

This procedure obtains a token to a C\-based tree data object\.  The
arguments are as follows:  

*interp*
:   Interpreter to report results back to\.  If an error occurs,
    then interp\-\>result will contain an error message\.

*name*
:   Name of an existing tree data object\.  It\'s an error if a
    tree *name* doesn\'t already exist\.  *Name* can be qualified by a
    namespace such as fred::myTree\.  If no namespace qualifier is
    used, the tree the current namespace is searched, then the
    global namespace\.  

*tokenPtr*
:   Points to the location where the returned token is stored\. A
    tree token is used to work with the tree object\.

A token for the tree data object is returned\.  Tree data objects can be
shared\.  For example, the __tree__ and __hiertable__ commands may be accessing
the same tree data object\.  Each client grabs a token that is
associated with the tree\.  When all tokens are released (see
__Rbc\_TreeReleaseToken__) the tree data object is automatically destroyed\.

RETURNS
=======

A standard Tcl result is returned\.  If TCL\_ERROR is returned, then
*interp\-\>result* will contain an error message\.  The following errors may
occur:  

*   No tree exists as *name*\. You can use __Tcl\_TreeExists__ to determine if a
    tree exists beforehand\.  

*   Memory can\'t be allocated for the token\.

EXAMPLE
=======

The following example allocated a token for an existing tree\.

~~~~~
Rbc_Tree token;

if (Rbc_TreeGetToken(interp, "myTree", &token) != TCL_OK) {
    return TCL_ERROR;
}
printf("tree is %s\n", Rbc_TreeName(token));
~~~~~

SEE ALSO
========

Tcl\_TreeCreate, Tcl\_TreeExists, Tcl\_TreeReleaseToken  

