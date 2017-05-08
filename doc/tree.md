

NAME
====

tree \-  Create and manage tree data objects\.  

SYNOPSIS
========

__rbc::tree create__ ?*treeName*?  

__rbc::tree destroy__ *treeName*\.\.\.  

__rbc::tree names__ ?*pattern*?  

DESCRIPTION
===========

The __tree__ command creates tree data objects\.  A *tree* *object* is general
ordered tree of nodes\.  Each node has both a label and a key\-value list
of data\.  Data can be heterogeneous, since nodes do not have to contain
the same data keys\.  It is associated with a Tcl command that you can
use to access and modify the its structure and data\. Tree objects can
also be managed via a C API\.  

INTRODUCTION
============


EXAMPLE
=======


SYNTAX
======


__tree create__ ?*treeName*?

:   Creates a new tree object\.  The name of the new tree is
    returned\.  If no *treeName* argument is present, then the name of
    the tree is automatically generated in the form "tree0",
    "tree1", etc\.  If the substring "#auto" is found in *treeName*, it
    is automatically substituted by a generated name\.  For example,
    the name \.foo\.#auto\.bar will be translated to \.foo\.tree0\.bar\.

    A new Tcl command (by the same name as the tree) is also
    created\.  Another Tcl command or tree object can not already
    exist as *treeName*\.  If the Tcl command is deleted, the tree will
    also be freed\.  The new tree will contain just the root node\.
    Trees are by default, created in the current namespace, not the
    global namespace, unless *treeName* contains a namespace
    qualifier, such as "fred::myTree"\.  

__tree destroy__ *treeName*\.\.\.

:   Releases one of more trees\.  The Tcl command associated with
    *treeName* is also removed\.  Trees are reference counted\.  The
    internal tree data object isn\'t destroyed until no one else is
    using the tree\.  

__tree names__ ?*pattern*?

:   Returns the names of all tree objects\.  if a *pattern* argument is
    given, then the only those trees whose name matches pattern will
    be listed\.  

NODE IDS AND TAGS
=================

Nodes in a tree object may be referred in either of two ways: by id or
by tag\.  Each node has a unique serial number or id that is assigned to
that node when it\'s created\. The id of an node never changes and id
numbers are not re\-used\.  

A node may also have any number of tags associated with it\.  A tag is
just a string of characters, and it may take any form except that of an
integer\.  For example, "x123" is valid, but "123" isn\'t\.  The same tag
may be associated with many different nodes\.  This is commonly done to
group nodes in various interesting ways\.  

There are two built\-in tags: The tag __all__ is implicitly associated with
every node in the tree\.  It may be used to invoke operations on all the
nodes in the tree\.  The tag __root__ is managed automatically by the tree
object\. It applies to the node currently set as root\.

When specifying nodes in tree object commands, if the specifier is an
integer then it is assumed to refer to the single node with that id\.
If the specifier is not an integer, then it is assumed to refer to all
of the nodes in the tree that have a tag matching the specifier\.  The
symbol *node* is used below to indicate that an argument specifies either
an id that selects a single node or a tag that selects zero or more
nodes\.  Many tree commands only operate on a single node at a time; if
*node* is specified in a way that names multiple items, then an error
"refers to more than one node" is generated\.  

NODE MODIFIERS
==============

You can also specify node in relation to another node by appending one
or more modifiers to the node id or tag\.  A modifier refers to a node
in relation to the specified node\.  For example, "root\-\>firstchild"
selects the first subtree of the root node\.  

The following modifiers are available:  

firstchild
:   Selects the first child of the node\.

lastchild
:   Selects the last child of the node\.

next
:   Selects the next node in preorder to the node\.

nextsibling
:   Selects the next sibling of the node\.

parent
:   Selects the parent of the node\.

previous
:   Selects the previous node in preorder to the node\.

prevsibling
:   Selects the previous sibling of the node\.

"*label*"
:   Selects the node whose label is *label*\.  Enclosing
    *label* in quotes indicates to always search for a node
    by its label (for example, even if the node is labeled
    "parent")\.  

It\'s an error the node can\'t be found\.  For example, __lastchild__ and
__firstchild__ will generate errors if the node has no children\.  The
exception to this is the __index__ operation\.  You can use __index__ to test if
a modifier is valid\.  

TREE OPERATIONS
===============

Once you create a tree object, you can use its Tcl command to query or
modify it\.  The general form is *treeName* *operation* ?*arg*?\.\.\.  Both
*operation* and its arguments determine the exact behavior of the
command\.  The operations available for trees are listed below\.

*treeName* __ancestor__ *node1* *node2*

:   Returns the mutual ancestor of the two nodes *node1* and *node2*\.
    The ancestor can be one of the two nodes\.  For example, if *node1*
    and *node2* are the same nodes, their ancestor is *node1*\.

*treeName* __apply__ *node* ?*switches*?

:   Runs commands for all nodes matching the criteria given by
    *switches* for the subtree designated by *node*\.  By default all
    nodes match, but you can set switches to narrow the match\.  This
    operation differs from __find__ in two ways: 1) Tcl commands can be
    invoked both pre\- and post\-traversal of a node and 2) the tree
    is always traversed in depth first order\.  

    The __\-exact__, __\-glob__, and __\-regexp__ switches indicate both what kind
    of pattern matching to perform and the pattern\.  By default each
    pattern will be compared with the node label\.  You can set more
    than one of these switches\.  If any of the patterns match
    (logical or), the node matches\.  If the __\-key__ switch is used, it
    designates the data field to be matched\.  

    The valid switches are listed below:  

    \-depth *number*
    :   Descend at most *number* (a non\-negative integer) levels
        If *number* is 1 this means only apply the tests to the
        children of *node*\.  

    \-exact *string*
    :   Matches each node using *string*\.  The node must match
        *string* exactly\.  

    \-glob *string*
    :   Test each node to *string* using global pattern
        matching\.  Matching is done in a fashion similar to
        that used by the C\-shell\.  

    \-invert
    :   Select non\-matching nodes\.  Any node that *doesn\'t*
        match the given criteria will be selected\.

    \-key
    :   *key*  If pattern matching is selected (using the __\-exact__,
        __\-glob__, or __\-regexp__ switches), compare the values of the
        data field keyed by *key* instead of the node\'s label\.
        If no pattern matching switches are set, then any node
        with this data key will match\.  

    \-leafonly
    :   Only test nodes with no children\.

    \-nocase
    :   Ignore case when matching patterns\.

    \-path
    :   Use the node\'s full path when comparing nodes\.  The
        node\'s full path is a list of labels, starting from
        the root of each ancestor and the node itself\.

    \-precommand *command*
    :   Invoke *command* for each matching node\.  Before *command*
        is invoked, the id of the node is appended\.  You can
        control processing by the return value of *command*\.  If
        *command* generates an error, processing stops and the
        __find__ operation returns an error\.  But if *command*
        returns __break__, then processing stops, no error is
        generated\.  If *command* returns __continue__, then
        processing stops on that subtree and continues on the
        next\.  

    \-postcommand *command*
    :   Invoke *command* for each matching node\.  Before *command*
        is invoked, the id of the node is appended\.  You can
        control processing by the return value of *command*\.  If
        *command* generates an error, processing stops and the
        __find__ operation returns an error\.  But if *command*
        returns __break__, then processing stops, no error is
        generated\.  If *command* returns __continue__, then
        processing stops on that subtree and continues on the
        next\.  

    \-regexp *string*
    :   Test each node using *string* as a regular expression
        pattern\.  

    \-tag *string*
    :   Only test nodes that have the tag *string*\.

*treeName* __attach__ *treeObject*

:   Attaches to an existing tree object *treeObject*\.  This is for
    cases where the tree object was previously created via the C
    API\.  The current tree associated with *treeName* is discarded\.
    In addition, the current set of tags, notifier events, and
    traces are removed\.  

*treeName* __children__ *node*

:   Returns a list of children for *node*\.  If *node* is a leaf, then an
    empty string is returned\.  

*treeName* __copy__ *srcNode* ?*destTree*? *parentNode* ?*switches*?

:   Copies *srcNode* into *parentNode*\. Both nodes *srcNode* and
    *parentNode* must already exist\. The id of the new node is
    returned\. You can copy from one tree to another\.  If a *destTree*
    argument is present, it indicates the name of the destination
    tree\.  By default both the source and destination trees are the
    same\. The valid *switches* are listed below:  

    \-label *string*
    :   Label *destNode* as *string*\.  By default, *destNode* has the
        same label as *srcNode*\.  

    \-overwrite
    :   Overwrite nodes that already exist\.  Normally nodes are
        always created, even if there already exists a node by
        the same name\.  This switch indicates to add or overwrite
        the node\'s data fields\.  

    \-recurse
    :   Recursively copy all the subtrees of *srcNode* as well\.  In
        this case, *srcNode* can\'t be an ancestor of *destNode* as it
        would result in a cyclic copy\.  

    \-tags
    :   Copy tag inforation\.  Normally the following node is
        copied: its label and data fields\.  This indicates to
        copy tags as well\.  

*treeName* __degree__ *node*

:   Returns the number of children of *node*\.

*treeName* __delete__ *node*\.\.\.

:   Recursively deletes one or more nodes from the tree\.  The node
    and all its descendants are removed\.   The one exception is the
    root node\.  In this case, only its descendants are removed\.  The
    root node will remain\.  Any tags or traces on the nodes are
    released\.  

*treeName* __depth__ *node*

:   Returns the depth of the node\.  The depth is the number of steps
    from the node to the root of the tree\.  The depth of the root
    node is 0\.  

*treeName* __dump__ *node*

:   Returns a list of the paths and respective data for *node* and its
    descendants\.  The subtree designated by *node* is traversed
    returning the following information for each node: 1) the node\'s
    path relative to *node*, 2) a sublist key value pairs representing
    the node\'s data fields, and 3) a sublist of tags\.  This list
    returned can be used later to copy or restore the tree with the
    __restore__ operation\.  

*treeName* __dumpfile__ *node* *fileName*

:   Writes a list of the paths and respective data for *node* and its
    descendants to the given file *fileName*\.  The subtree designated
    by *node* is traversed returning the following information for
    each node: 1) the node\'s path relative to *node*, 2) a sublist key
    value pairs representing the node\'s data fields, and 3) a
    sublist of tags\.  This list returned can be used later to copy
    or restore the tree with the __restore__ operation\.

*treeName* __exists__ *node* ?*key*?

:   Indicates if *node* exists in the tree\.  If a *key* argument is
    present then the command also indicates if the named data field
    exists\.  

*treeName* __find__ *node* ?*switches*?

:   Finds for all nodes matching the criteria given by *switches* for
    the subtree designated by *node*\.  A list of the selected nodes is
    returned\.  By default all nodes match, but you can set switches
    to narrow the match\.  

    The __\-exact__, __\-glob__, and __\-regexp__ switches indicate both what kind
    of pattern matching to perform and the pattern\.  By default each
    pattern will be compared with the node label\.  You can set more
    than one of these switches\.  If any of the patterns match
    (logical or), the node matches\.  If the __\-key__ switch is used, it
    designates the data field to be matched\.  

    The order in which the nodes are traversed is controlled by the
    __\-order__ switch\.  The possible orderings are __preorder__, __postorder__,
    __inorder__, and __breadthfirst__\.  The default is __postorder__\.

    The valid switches are listed below:  

    \-addtag *string*
    :   Add the tag *string* to each selected node\.

    \-count *number*
    :   Stop processing after *number* (a positive integer)
        matches\.  

    \-depth *number*
    :   Descend at most *number* (a non\-negative integer) levels
        If *number* is 1 this means only apply the tests to the
        children of *node*\.  

    \-exact *string*
    :   Matches each node using *string*\.  The node must match
        *string* exactly\.  

    \-exec *command*
    :   Invoke *command* for each matching node\.  Before *command*
        is invoked, the id of the node is appended\.  You can
        control processing by the return value of *command*\.  If
        *command* generates an error, processing stops and the
        __find__ operation returns an error\.  But if *command*
        returns __break__, then processing stops, no error is
        generated\.  If *command* returns __continue__, then
        processing stops on that subtree and continues on the
        next\.  

    \-glob *string*
    :   Test each node to *string* using global pattern
        matching\.  Matching is done in a fashion similar to
        that used by the C\-shell\.  

    \-invert
    :   Select non\-matching nodes\.  Any node that *doesn\'t*
        match the given criteria will be selected\.

    \-key
    :   *key*  Compare the values of the data field keyed by *key*
        instead of the node\'s label\. If no pattern is given
        (__\-exact__, __\-glob__, or __\-regexp__ switches), then any node
        with this data key will match\.  

    \-leafonly
    :   Only test nodes with no children\.

    \-nocase
    :   Ignore case when matching patterns\.

    \-order *string*
    :   Traverse the tree and process nodes according to
        *string*\. *String* can be one of the following:

        breadthfirst
        :   Process the node and the subtrees at each
            sucessive level\. Each node on a level is
            processed before going to the next level\.

        inorder
        :   Recursively process the nodes of the first
            subtree, the node itself, and any the
            remaining subtrees\.  

        postorder
        :   Recursively process all subtrees before the
            node\.  

        preorder
        :   Recursively process the node first, then any
            subtrees\.  

    \-path
    :   Use the node\'s full path when comparing nodes\.

    \-regexp *string*
    :   Test each node using *string* as a regular expression
        pattern\.  

    \-tag *string*
    :   Only test nodes that have the tag *string*\.

*treeName* __findchild__ *node* *label*

:   Searches for a child node Ilabel in *node*\.  The id of the child
    node is returned if found\.  Otherwise \-1 is returned\.

*treeName* __firstchild__ *node*

:   Returns the id of the first child in the *node*\'s list of
    subtrees\.  If *node* is a leaf (has no children), then \-1 is
    returned\.  

*treeName* __get__ *node* ?*key*? ?*defaultValue*?

:   Returns a list of key\-value pairs of data for the node\.  If *key*
    is present, then onlyx the value for that particular data field
    is returned\.  It\'s normally an error if *node* does not contain
    the data field *key*\.  But if you provide a *defaultValue* argument,
    this value is returned instead (*node* will still not contain
    *key*)\.  This feature can be used to access a data field of *node*
    without first testing if it exists\.  This operation may trigger
    __read__ data traces\.  

*treeName* __index__ *node*

:   Returns the id of *node*\.  If *node* is a tag, it can only specify
    one node\.  If *node* does not represent a valid node id or tag, or
    has modifiers that are invalid, then \-1 is returned\.

*treeName* __insert__ *parent* ?*switches*?

:   Inserts a new node into parent node *parent*\.  The id of the new
    node is returned\. The following switches are available:

    \-after *child*
    :   Position *node* after *child*\.  The node *child* must be a
        child of *parent*\.  

    \-at *number*
    :   Inserts the node into *parent*\'s list of children at
        position *number*\.  The default is to append *node*\.

    \-before *child*
    :   Position *node* before *child*\.  The node *child* must be a
        child of *parent*\.  

    \-data *dataList*
    :   Sets the value for each data field in *dataList* for the
        new node\. *DataList* is a list of key\-value pairs\.

    \-label *string*
    :   Designates the labels of the node as *string*\.  By
        default, nodes are labeled as node0, node1, etc\.

    \-node
    :   *id*  Designates the id for the node\.  Normally new ids are
        automatically generated\.  This allows you to create a
        node with a specific id\.  It is an error if the id is
        already used by another node in the tree\.

    \-tags *tagList*
    :   Adds each tag in *tagList* to the new node\. *TagList* is a
        list of tags, so be careful if a tag has embedded
        space\.  

*treeName* __is__ *property* *args*

:   Indicates the property of a node\. Both *property* and *args*
    determine the property being tested\.  Returns 1 if true and 0
    otherwise\.  The following *property* and *args* are valid:

    ancestor *node1* *node2*
    :   Indicates if *node1* is an ancestor of *node2*\.

    before *node1* *node2*
    :   Indicates if *node1* is before *node2* in depth first
        traversal\.  

    leaf *node*
    :   Indicates if *node* is a leaf (it has no subtrees)\.

    root *node*
    :   Indicates if *node* is the designated root\.  This can be
        changed by the __root__ operation\.  

*treeName* __label__ *node* ?*newLabel*?

:   Returns the label of the node designated by *node*\.  If *newLabel*
    is present, the node is relabeled using it as the new label\.

*treeName* __lastchild__ *node*

:   Returns the id of the last child in the *node*\'s list of subtrees\.
    If *node* is a leaf (has no children), then \-1 is returned\.

*treeName* __move__ *node* *newParent* ?*switches*?

:   Moves *node* into *newParent*\. *Node* is appended to the list children
    of *newParent*\.  *Node* can not be an ancestor of *newParent*\.  The
    valid flags for *switches* are described below\.  

    \-after *child*
    :   Position *node* after *child*\.  The node *child* must be a
        child of *newParent*\.  

    \-at *number*
    :   Inserts *node* into *parent*\'s list of children at
        position *number*\. The default is to append the node\.

    \-before *child*
    :   Position *node* before *child*\.  The node *child* must be a
        child of *newParent*\.  

*treeName* __next__ *node*

:   Returns the next node from *node* in a preorder traversal\.  If
    *node* is the last node in the tree, then \-1 is returned\.

*treeName* __nextsibling__ *node*

:   Returns the node representing the next subtree from *node* in its
    parent\'s list of children\.  If *node* is the last child, then \-1
    is returned\.  

*treeName* __notify__ *args*

:   Manages notification events that indicate that the tree
    structure has been changed\.  See the __NOTIFY OPERATIONS__ section
    below\.  

*treeName* __parent__ *node*

:   Returns the parent node of *node*\.  If *node* is the root of the
    tree, then \-1 is returned\.  

*treeName* __path__ *node*

:   Returns the full path (from root) of *node*\.

*treeName* __position__ *node*

:   Returns the position of the node in its parent\'s list of
    children\.  Positions are numbered from 0\.  The position of the
    root node is always 0\.  

*treeName* __previous__ *node*

:   Returns the previous node from *node* in a preorder traversal\.  If
    *node* is the root of the tree, then \-1 is returned\.

*treeName* __prevsibling__ *node*

:   Returns the node representing the previous subtree from *node* in
    its parent\'s list of children\.  If *node* is the first child, then
    \-1 is returned\.  

*treeName* __restore__ *node* *dataString* *switches*

:   Performs the inverse function of the __dump__ operation, restoring
    nodes to the tree\. The format of *dataString* is exactly what is
    returned by the __dump__ operation\.  It\'s a list containing
    information for each node to be restored\.  The information
    consists of 1) the relative path of the node, 2) a sublist of
    key value pairs representing the node\'s data, and 3) a list of
    tags for the node\.  Nodes are created starting from *node*\. Nodes
    can be listed in any order\.  If a node\'s path describes ancestor
    nodes that do not already exist, they are automatically created\.
    The valid *switches* are listed below:  

    \-overwrite
    :   Overwrite nodes that already exist\.  Normally nodes are
        always created, even if there already exists a node by
        the same name\.  This switch indicates to add or overwrite
        the node\'s data fields\.  

*treeName* __restorefile__ *node* *fileName* *switches*

:   Performs the inverse function of the __dumpfile__ operation,
    restoring nodes to the tree from the file *fileName*\. The format
    of *fileName* is exactly what is returned by the __dumpfile__
    operation\.  It\'s a list containing information for each node to
    be restored\.  The information consists of 1) the relative path
    of the node, 2) a sublist of key value pairs representing the
    node\'s data, and 3) a list of tags for the node\.  Nodes are
    created starting from *node*\. Nodes can be listed in any order\.
    If a node\'s path describes ancestor nodes that do not already
    exist, they are automatically created\.  The valid *switches* are
    listed below:  

    \-overwrite
    :   Overwrite nodes that already exist\.  Normally nodes are
        always created, even if there already exists a node by
        the same name\.  This switch indicates to add or overwrite
        the node\'s data fields\.  

*treeName* __root__ ?*node*?

:   Returns the id of the root node\.  Normally this is node 0\.  If a
    *node* argument is provided, it will become the new root of the
    tree\. This lets you temporarily work within a subset of the
    tree\.  Changing root affects operations such as __next__, __path__,
    __previous__, etc\.  

*treeName* __set__ *node* *key* *value* ?*key* *value*\.\.\.?

:   Sets one or more data fields in *node*\. *Node* may be a tag that
    represents several nodes\.  *Key* is the name of the data field to
    be set and *value* is its respective value\.  This operation may
    trigger __write__ and __create__ data traces\.  

*treeName* __size__ *node*

:   Returns the number of nodes in the subtree\. This includes the
    node and all its descendants\.  The size of a leaf node is 1\.

*treeName* __sort__ *node* ?*switches*?

: …

    \-ascii
    :   Compare strings using the ASCII  collation order\.

    \-command *string*
    :   Use command *string* as a comparison command\.  To
        compare two elements, evaluate a Tcl script consisting
        of command with the two elements appended as
        additional arguments\.  The script should return an
        integer less than, equal to, or greater than zero if
        the first element is to be considered less than, equal
        to, or greater than the second, respectively\.

    \-decreasing
    :   Sort in decreasing order (largest items come first)\.

    \-dictionary
    :   Compare strings using a dictionary\-style comparison\.
        This is the same as __\-ascii__ except (a) case is ignored
        except as a tie\-breaker and (b) if two strings contain
        embedded numbers, the numbers compare as integers, not
        characters\.  For example, in __\-dictionary__ mode, bigBoy
        sorts between bigbang and bigboy, and x10y sorts
        between x9y and x11y\.  

    \-integer
    :   Compare the nodes as integers\.

    \-key *string*
    :   Sort based upon the node\'s data field keyed by *string*\.
        Normally nodes are sorted according to their label\.

    \-path
    :   Compare the full path of each node\.  The default is to
        compare only its label\.  

    \-real
    :   Compare the nodes as real numbers\.

    \-recurse
    :   Recursively sort the entire subtree rooted at *node*\.

    \-reorder
    :   Recursively sort subtrees for each node\.  __Warning__\.
        Unlike the normal flat sort, where a list of nodes is
        returned, this will reorder the tree\.

*treeName* __tag__ *args*

:   Manages tags for the tree object\.  See the __TAG OPERATIONS__
    section below\.  

*treeName* __trace__ *args*

:   Manages traces for data fields in the tree object\.  Traces cause
    Tcl commands to be executed whenever a data field of a node is
    created, read, written, or unset\.  Traces can be set for a
    specific node or a tag, representing possibly many nodes\.  See
    the __TRACE OPERATIONS__ section below\.  

*treeName* __unset__ *node* *key*\.\.\.

:   Removes one or more data fields from *node*\. *Node* may be a tag
    that represents several nodes\.  *Key* is the name of the data
    field to be removed\.  It\'s not an error is *node* does not contain
    *key*\.  This operation may trigger __unset__ data traces\.

TAG OPERATIONS
==============

Tags are a general means of selecting and marking nodes in the tree\.  A
tag is just a string of characters, and it may take any form except
that of an integer\.  The same tag may be associated with many different
nodes\.  

There are two built\-in tags: The tag __all__ is implicitly associated with
every node in the tree\.  It may be used to invoke operations on all the
nodes in the tree\.  The tag __root__ is managed automatically by the tree
object\.  It specifies the node that is currently set as the root of the
tree\.  

Most tree operations use tags\.  And several operations let you operate
on multiple nodes at once\.  For example, you can use the __set__ operation
with the tag __all__ to set a data field in for all nodes in the tree\.

Tags are invoked by the __tag__ operation\.  The general form is *treeName*
__tag__ *operation* ?*arg*?\.\.\.  Both *operation* and its arguments determine the
exact behavior of the command\.  The operations available for tags are
listed below\.  

*treeName* __tag add__ *string* *node*\.\.\.

:   Adds the tag *string* to one of more nodes\.

*treeName* __tag delete__ *string* *node*\.\.\.

:   Deletes the tag *string* from one or more nodes\.

*treeName* __tag forget__ *string*

:   Removes the tag *string* from all nodes\.  It\'s not an error if no
    nodes are tagged as *string*\.  

*treeName* __tag names__ ?*node*?

:   Returns a list of tags used by the tree\.  If a *node* argument is
    present, only those tags used by *node* are returned\.

*treeName* __tag nodes__ *string*

:   Returns a list of nodes that have the tag *string*\.  If no node is
    tagged as *string*, then an empty string is returned\.

TRACE OPERATIONS
================

Data fields can be traced much in the same way that you can trace Tcl
variables\.  Data traces cause Tcl commands to be executed whenever a
particular data field of a node is created, read, written, or unset\.  A
trace can apply to one or more nodes\.  You can trace a specific node by
using its id, or a group of nodes by a their tag\.  

The tree\'s __get__, __set__, and __unset__ operations can trigger various traces\.
The __get__ operation can cause a *read*  trace to fire\.  The __set__ operation
causes a *write* trace to fire\.  And if the data field is written for the
first time, you will also get a *create* trace\.  The __unset__ operation
triggers *unset* traces\.  

Data traces are invoked by the __trace__ operation\.  The general form is
*treeName* __trace__ *operation* ?*arg*?\.\.\.  Both *operation* and its arguments
determine the exact behavior of the command\.  The operations available
for traces are listed below\.  

*treeName* __trace create__ *node* *key* *ops* *command*

:   Creates a trace for *node* on data field *key*\.  *Node* can refer to
    more than one node (for example, the tag __all__)\. If *node* is a tag,
    any node with that tag can possibly trigger a trace, invoking
    *command*\.  *Command* is command prefix, typically a procedure name\.
    Whenever a trace is triggered, four arguments are appended to
    *command* before it is invoked: *treeName*, id of the node, *key* and,
    *ops*\.  Note that no nodes need have the field *key*\.  A trace
    identifier in the form "trace0", "trace1", etc\.  is returned\.

    *Ops* indicates which operations are of interest, and consists of
    one or more of the following letters:  

    r
    :   Invoke *command* whenever *key* is read\. Both read and write
        traces are temporarily disabled when *command* is executed\.

    w
    :   Invoke *command* whenever *key* is written\.  Both read and
        write traces are temporarily disabled when *command* is
        executed\.  

    c
    :   Invoke *command* whenever *key* is created\.

    u
    :   Invoke *command* whenever *key* is unset\.  Data fields are
        typically unset with the __unset__ command\.   Data fields are
        also unset when the tree is released, but all traces are
        disabled prior to that\.  

*treeName* __trace delete__ *traceId*\.\.\.

:   Deletes one of more traces\.  *TraceId* is the trace identifier
    returned by the __trace create__ operation\.  

*treeName* __trace info__ *traceId*

:   Returns information about the trace *traceId*\.  *TraceId* is a trace
    identifier previously returned by the __trace create__ operation\.
    It\'s the same information specified for the __trace create__
    operation\.  It consists of the node id or tag, data field key, a
    string of letters indicating the operations that are traced
    (it\'s in the same form as *ops*) and, the command prefix\.

*treeName* __trace names__

:   Returns a list of identifers for all the current traces\.

NOTIFY OPERATIONS
=================

Tree objects can be shared among many clients, such as a __hiertable__
widget\.  Any client can create or delete nodes, sorting the tree, etc\.
You can request to be notified whenever these events occur\.  Notify
events cause Tcl commands to be executed whenever the tree structure is
changed\.  

Notifications are handled by the __notify__ operation\.  The general form is
*treeName* __notify__ *operation* ?*arg*?\.\.\.  Both *operation* and its arguments
determine the exact behavior of the command\.  The operations available
for events are listed below\.  

*treeName* __notify create__ ?*switches*? *command* ?*args*?\.\.\.

:   Creates a notifier for the tree\.  A notify identifier in the
    form "notify0", "notify1", etc\.  is returned\.  

    *Command* and *args* are saved and invoked whenever the tree
    structure is changed (according to *switches*)\. Two arguments are
    appended to *command* and *args* before it\'s invoked: the id of the
    node and a string representing the type of event that occured\.
    One of more switches can be set to indicate the events that are
    of interest\.  The valid switches are as follows:

    \-create
    :   Invoke *command* whenever a new node has been added\.

    \-delete
    :   Invoke *command* whenever a node has been deleted\.

    \-move
    :   Invoke *command* whenever a node has been moved\.

    \-sort
    :   Invoke *command* whenever the tree has been sorted and
        reordered\.  

    \-relabel
    :   Invoke *command* whenever a node has been relabeled\.

    \-allevents
    :   Invoke *command* whenever any of the above events occur\.

    \-whenidle
    :   When an event occurs don\'t invoke *command* immediately,
        but queue it to be run the next time the event loop is
        entered and there are no events to process\.  If
        subsequent events occur before the event loop is
        entered, *command* will still be invoked only once\.

*treeName* __notify delete__ *notifyId*

:   Deletes one or more notifiers from the tree\.  *NotifyId* is the
    notifier identifier returned by the __notify create__ operation\.

*treeName* __notify info__ *notifyId*

:   Returns information about the notify event *notifyId*\.  *NotifyId*
    is a notify identifier previously returned by the __notify create__
    operation\.  It\'s the same information specified for the __notify__
    __create__ operation\.  It consists of the notify id, a sublist of
    event flags (it\'s in the same form as *flags*) and, the command
    prefix\.  

*treeName* __notify names__

:   Returns a list of identifers for all the current notifiers\.

C LANGUAGE API
==============

Rbc\_TreeApply, Rbc\_TreeApplyBFS, Rbc\_TreeApplyDFS, Rbc\_TreeChangeRoot,
Rbc\_TreeCreate, Rbc\_TreeCreateEventHandler, Rbc\_TreeCreateNode,
Rbc\_TreeCreateTrace, Rbc\_TreeDeleteEventHandler, Rbc\_TreeDeleteNode,
Rbc\_TreeDeleteTrace, Rbc\_TreeExists, Rbc\_TreeFindChild,
Rbc\_TreeFirstChild, Rbc\_TreeFirstKey, Rbc\_TreeGetNode,
Rbc\_TreeGetToken, Rbc\_TreeGetValue, Rbc\_TreeIsAncestor,
Rbc\_TreeIsBefore, Rbc\_TreeIsLeaf, Rbc\_TreeLastChild, Rbc\_TreeMoveNode,
Rbc\_TreeName, Rbc\_TreeNextKey, Rbc\_TreeNextNode, Rbc\_TreeNextSibling,
Rbc\_TreeNodeDegree, Rbc\_TreeNodeDepth, Rbc\_TreeNodeId,
Rbc\_TreeNodeLabel, Rbc\_TreeNodeParent, Rbc\_TreePrevNode,
Rbc\_TreePrevSibling, Rbc\_TreeRelabelNode, Rbc\_TreeReleaseToken,
Rbc\_TreeRootNode, Rbc\_TreeSetValue, Rbc\_TreeSize, Rbc\_TreeSortNode, and
Rbc\_TreeUnsetValue\.  

KEYWORDS
========

tree, hiertable, widget  

