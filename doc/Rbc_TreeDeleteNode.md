

NAME
====

Rbc\_TreeDeleteNode \- Deletes a node and its descendants\.

SYNOPSIS
========

#include \<rbcTree\.h\>  

Rbc\_TreeNode  
__Rbc\_TreeDeleteNode__(*tree*, *node*)  

ARGUMENTS
=========

Rbc\_Tree       *tree*   (in)      Tree containing the node\.

Rbc\_TreeNode   *node*   (in)      Node to be deleted\.  

DESCRIPTION
===========

This procedure deletes a given node and all it descendants from a tree
data object\.  

The arguments are as follows:  

*tree*
:   The tree containing the parent node\.

*node*
:   Node to be deleted\.  The node and its descendant nodes are
    deleted\.  Each node\'s data values are deleted also\.   The
    reference count of the Tcl\_Obj is decremented\.

Since all tree objects must contain at least a root node, the root node
itself can\'t be deleted unless the tree is released and destroyed\.
Therefore you can clear a tree by deleting its root, but the root node
will remain until the tree is destroyed\.  

RETURNS
=======

Always returns TCL\_OK\.  Errors generated in a notification callbacks
are backgrounded (see __Tcl\_TreeCreateNotifyHandler__)\.  

EXAMPLE
=======

The following example deletes the root node\.  

~~~~~
Rbc_TreeNode root;

root = Rbc_TreeRootNode(token);
Rbc_TreeDeleteNode(token, root);
~~~~~

NOTIFICATIONS
=============

__Rbc\_TreeDeleteNode__ can trigger tree notify events\.  You can be notified
whenever a node is deleted by using the __Rbc\_TreeCreateNotifyHandler__\.  A
callback routine is registered that will be automatically invoked
whenever a node is deleted via __Rbc\_TreeDeleteNode__ to the tree\.

KEYWORDS
========

tree, token  

