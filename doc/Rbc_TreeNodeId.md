

NAME
====

Rbc\_TreeNodeId \- Returns the node serial number\.  

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

unsigned int  
__Rbc\_TreeNodeId__(*node*)  

ARGUMENTS
=========

Rbc\_TreeNode   *node*   (in)      Node whose ID is to be returned\.

DESCRIPTION
===========

This procedure returns the node serial number\.  The node serial number
is useful for programs that export the tree data object to the Tcl
programming level\.  Since node labels (and therefore pathnames) are not
unique, the ID can be used to uniquely identify a node\.

The arguments are as follows:  

*node*
:   The node whose serial number is returned\.  The serial number
    of the root node for example is always 0\.  

RETURNS
=======

The serial number of the node\.  Nodes are given a unique serial number
when they are created\.  You can use the ID to later retrieve the node
using __Rbc\_TreeGetNode__\.  

EXAMPLE
=======

The following example prints the ID of a node\.  

~~~~~
printf("root ID is %s\n", Rbc_TreeNodeId(node));
~~~~~

KEYWORDS
========

Tcl\_TreeCreateNode, Tcl\_TreeDeleteNode  

