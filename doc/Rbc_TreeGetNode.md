

NAME
====

Rbc\_TreeGetNode \- Finds the node from the ID\.  

SYNOPSIS
========

__#include \<rbcTree\.h\>__  

Rbc\_TreeNode  
__Rbc\_TreeGetNode__(*tree*, *number*)  

ARGUMENTS
=========

Rbc\_Tree       *tree*     (in)      Tree containing the requested node\.

unsigned int   *number*   (in)      Serial number of the requested node\.

DESCRIPTION
===========

This procedure returns a node in a tree object based upon a give serial
number\.  The node is searched using the serial number\.

The arguments are as follows:  

*tree*
:   The tree containing the requested node\.

*number*
:   The serial number of the requested node\.

RETURNS
=======

The node represented by the given serial number is returned\.  If no
node with that ID exists in *tree* then NULL is returned\.

EXAMPLE
=======

The following example gets the node from a serial number\.

~~~~~
unsigned int number;
Rbc_TreeNode node;
Rbc_TreeToken token;
node = Rbc_TreeGetNode(token, number);
if (node == NULL) {
    printf("no node with ID %d exists\n", number);
} else {
    printf("node found: label is %s\n", Rbc_TreeNodeLabel(node));
}
~~~~~

KEYWORDS
========

Tcl\_TreeCreateNode, Tcl\_TreeDeleteNode  

