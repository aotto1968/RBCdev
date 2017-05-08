

NAME
====

Rbc\_TreeCreateNode \- Creates a node in a tree data object\.

SYNOPSIS
========

#include \<rbcTree\.h\>  

Rbc\_TreeNode  
__Rbc\_TreeCreateNode__(*tree*, *parent*, *name*, *position*)  

ARGUMENTS
=========


Rbc\_Tree       *tree*     (in)
:   Tree containing the parent node\.

Rbc\_TreeNode   *parent*   (in)
:   Node in which to insert the new
    child\.  

const char     *\*name*    (in)
:   Node label\.  If NULL, a label will
    automatically be generated\.

int            *position* (in)
:   Position in the parent\'s list of
    children to insert the new node\.

DESCRIPTION
===========

This procedure creates a new node is a tree data object\.  The node is
initially empty, but data values can be added with __Rbc\_TreeSetValue__\.
Each node has a serial number that identifies it within the tree\.  No
two nodes in the same tree will ever have the same ID\.  You can find a
node\'s ID with __Rbc\_TreeNodeId__\.  

The arguments are as follows:  

*tree*
:   The tree containing the parent node\.

*parent*
:   Node in which the new child will be inserted\.

*name*
:   Label of the new node\.  If *name* is NULL, a label in the form
    "node0", "node1", etc\. will automatically be generated\.  *Name*
    can be any string\.  Labels are non\-unique\.  A parent can
    contain two nodes with the same label\. Nodes can be relabeled
    using __Rbc\_TreeRelabelNode__\.  

*position*
:   Position the parent\'s list of children to insert the new
    node\.  For example, if *position* is 0, then the new node is
    prepended to the beginning of the list\.  If *position* is \-1,
    then the node is appended onto the end of the parent\'s list\.

RETURNS
=======

The new node returned is of type __Rbc\_TreeNode__\.  It\'s a token that can
be used with other routines to add/delete data values or children
nodes\.  

EXAMPLE
=======

The following example creates a new node from the root node\.

~~~~~
Rbc_Tree token;
Rbc_TreeNode root, node;

if (Rbc_TreeGetToken(interp, "myTree", &token) != TCL_OK) {
    return TCL_ERROR;
}
root = Rbc_TreeRootNode(token);
node = Rbc_TreeCreateNode(token, root, "myNode", -1);
~~~~~

NOTIFICATIONS
=============

__Rbc\_TreeCreateNode__ can trigger tree notify events\.  You can be notified
whenever a node is created by using the __Rbc\_TreeCreateNotifyHandler__\.  A
callback routine is registered that will be automatically invoked
whenever a new node is added via __Rbc\_TreeCreateNode__ to the tree\.

KEYWORDS
========

tree, token  

