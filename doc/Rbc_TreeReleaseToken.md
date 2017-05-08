

NAME
====

Rbc\_TreeReleaseToken \- Releases token associated with tree object\.

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

int  
__Rbc\_TreeReleaseToken__(*token*)  

ARGUMENTS
=========

Rbc\_Tree   *\*token*  (in)      Token of tree to be released\.

DESCRIPTION
===========

This procedure releases the token associated with a C\-based tree data
object\.  When all outstanding tokens for a tree data object have been
released, then the data object itself will be freed\.  The arguments are
as follows:  

token
:   Token of the tree data object to be released\.  This token was
    initialized either by __Tcl\_TreeGetToken__ *or* *Rbc\_TreeCreate*
    earlier\.  

RETURNS
=======

Nothing\.  

EXAMPLE
=======

The following example creates and then releases a new token\.

~~~~~
Rbc_Tree token;

if (Rbc_TreeCreate(interp, "myTree", &token) != TCL_OK) {
    return TCL_ERROR;
}
printf("tree is %s\n", Rbc_TreeName(token));

/* Tree will be destroyed when the token is released. */
Rbc_TreeReleaseToken(token);
~~~~~

KEYWORDS
========

tree, token  

