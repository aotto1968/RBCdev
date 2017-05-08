

NAME
====

Rbc\_Tree \- Tree data object\.  

SYNOPSIS
========

#include \<rbcTree\.h\>  

struct Rbc\_Tree {  
__Tcl\_Alloc__(*size*)  

__Tcl\_Free__(*ptr*)  

char \*  
__Tcl\_Realloc__(*ptr,* *size*)  

ARGUMENTS
=========

int    *size*    (in)      Size in bytes of the memory block to allocate\.

char   *\*ptr*    (in)      Pointer to memory block to free or realloc\.

DESCRIPTION
===========

These procedures provide a platform and compiler independent interface
for memory allocation\.  Programs that need to transfer ownership of
memory blocks between Tcl and other modules should use these routines
rather than the native __malloc()__ and __free()__ routines provided by the C
run\-time library\.  

__Tcl\_Alloc__ returns a pointer to a block of at least *size* bytes suitably
aligned for any use\.  

__Tcl\_Free__ makes the space referred to by *ptr* available for further
allocation\.  

__Tcl\_Realloc__ changes the size of the block pointed to by *ptr* to *size*
bytes and returns a pointer to the new block\.  The contents will be
unchanged up to the lesser of the new and old sizes\.  The returned
location may be different from *ptr*\.  

TREE OBJECT ROUTINES
====================

The following library routines allow you to create and destroy tree
objects\.  Each tree object has a name that uniquely identifies it\.
Tree objects can also be shared\.  For example, the __tree__ and __hiertable__
commands may access the same tree data object\.  Each client grabs a
token associated with the tree\.  When all tokens are released the tree
data object is automatically destroyed\.  

Rbc\_TreeCreate
:   Create a tree data object and optionally obtains a
    token associated with it\.  

Rbc\_TreeExists
:   Indicates if a tree by a given name exists\.

Rbc\_TreeGetToken
:   Obtains a token for an existing tree data object\.

Rbc\_TreeReleaseToken
:   Releases a token for a tree data object\.  The tree
    object is deleted when all outstanding tokens have
    been released\.  

Rbc\_TreeName
:   Returns the name of the tree object\.

Rbc\_TreeChangeRoot
:   Specifies a node as the new root to a tree\.

TREENODE ROUTINES
=================

Tree objects initially contain only a root node\. You can add or delete
nodes with the following routines\.  

Rbc\_TreeCreateNode
:   Creates a new child node for a given parent in the
    tree\.  

Rbc\_TreeDeleteNode
:   Deletes a node and its children\.

Rbc\_TreeNodeId
:   Returns the unique node identifier for a node\.

Rbc\_TreeGetNode
:   Gets a node based upon its identifier\.

Rbc\_TreeFindChild
:   Searches for a child node given by its label in a
    parent node\.  

Rbc\_TreeNodeLabel
:   Returns the current label for a node\.

Rbc\_TreeRelabelNode
:   Resets a node\'s label\.

Rbc\_TreeNodePath
:   Returns the fullpath to a node\.

Rbc\_TreeNodeDepth
:   Returns the depth of the node\.

Rbc\_TreeNodeDegree
:   Returns the number of children for a node\.

Rbc\_TreeIsLeaf
:   Indicates if a node has no children\.

Rbc\_TreeIsBefore
:   Indicates if a node is before another node in
    depth\-first search order\.  

Rbc\_TreeIsAncestor
:   Indicates if a node is an ancestor or another\.

Rbc\_TreeSortNode
:   Sorts the children of a node\.

Rbc\_TreeSize
:   Returns the number of nodes in a node and its
    descendants\.  

__Rbc\_TreeMoveNode__  

NODE NAVIGATION
===============

Each node can have zero or more children nodes\.  These routines let you
navigate the tree hierarchy\.  

Rbc\_TreeNodeParent
:   Returns the parent node\.

Rbc\_TreeFirstChild
:   Returns the first child of a parent node\.

Rbc\_TreeLastChild
:   Returns the last child of a parent node\.

Rbc\_TreeNextSibling
:   Returns the next sibling node in the parent\'s list
    of children\.  

Rbc\_TreePrevSibling
:   Returns the previous sibling node in the parent\'s
    list of children\.  

Rbc\_TreeRootNode
:   Returns the root node of the tree\.

Rbc\_TreeNextNode
:   Returns the next node in depth\-first order\.

Rbc\_TreePrevNode
:   Returns the previous node in depth\-first order\.

Rbc\_TreeEndNode
:   Returns the last node in the tree as determined by
    depth\-first order\.  

Rbc\_TreeApply
:   Walks through a node and all it descendants,
    applying a given callback procedure\.

Rbc\_TreeApplyDFS
:   Walks through a node and all it descendants in
    depth\-first search order, applying a given callback
    procedure\.  

Rbc\_TreeApplyBFS
:   Walks through a node and all it descendants in
    breadth\-first search order, applying a given
    callback procedure\.  

NODE DATA VALUES
================

Data values can be stored at any node\.  Values have by both a string
key and a Tcl\_Obj value\.  Data value keys do not have to be homogenous
across all nodes (i\.e\. nodes do not have to contain the same keys)\.
There is also a special node array data type\.  

Rbc\_TreeGetValue
:   Gets the node data value given by a key\.

Rbc\_TreeValueExists
:   Indicates if a node data value given by a key
    exists\.  

Rbc\_TreeSetValue
:   Sets a node\'s value of a key\.

Rbc\_TreeUnsetValue
:   Remove the node data value and key\.

Rbc\_TreeGetArrayValue
:   Gets the node data array value given by a key and
    an array index\.  

Rbc\_TreeSetArrayValue
:   Sets the node data array value given by a key and
    an array index\.  

Rbc\_TreeUnsetArrayValue
:   Remove the node data array value\.

Rbc\_TreeArrayValueExists
:   Determines if an array element by a given index
    exists\.  

Rbc\_TreeFirstKey
:   Returns the key of the first value in the node\.

Rbc\_TreeNextKey
:   Returns the key of the next value in the node\.

Rbc\_TreePrivateValue
:   Lock the value to current client, making it
    private\.  

Rbc\_TreePublicValue
:   Unlock the value so that all clients can access it\.

__Rbc\_TreeGetKey__  

NODE TRACES
===========


Rbc\_TreeCreateTrace
:   Sets up a trace callback to be invoked when the
    node value is read, set, or unset\.

Rbc\_TreeDeleteTrace
:   Deletes an existing trace\.

NODE EVENTS
===========


Rbc\_TreeCreateEventHandler
:   Sets up a callback to be invoked when events
    (create, delete, relabel, etc) take place on a
    node\.  

Rbc\_TreeDeleteEventHandler
:   Deletes an existing node callback\.

KEYWORDS
========

alloc, allocation, free, malloc, memory, realloc  

