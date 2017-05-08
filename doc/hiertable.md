

NAME
====

treeview \- Create and manipulate hierarchical table widgets

SYNOPSIS
========

__treeview__ *pathName* ?*options*?  

DESCRIPTION
===========

The __treeview__ widget displays a tree of data\.  It replaces both the
__hiertable__ and __hierbox__ widgets\.  The __treeview__ is 100% syntax compatible
with the __hiertable__ widget\.  The __hiertable__ command is retained for sake
of script\-level compatibility\.  This widget obsoletes the __hierbox__
widget\.  It does everything the old __hierbox__ widget did, but also
provides data sharing (via *tree* *data* *objects*) and the ability to tag
nodes\.  

INTRODUCTION
============

The __treeview__ widget displays hierarchical data\.  Data is represented as
nodes in a general\-ordered tree\.  Each node may have sub\-nodes and
these nodes can in turn has their own children\.  

A node is displayed as a row entry in the widget\.  Each entry has a
text label and icon\.  When a node has children, its entry is drawn with
a small button to the left of the label\.  Clicking the mouse over this
button opens or closes the node\.  When a node is *open*, its children are
exposed\.  When it is *closed*, the children and their descedants are
hidden\.  The button is normally a + or \- symbol (ala Windows Explorer),
but can be replaced with a pair of Tk images (open and closed images)\.

If the node has data associated with it, they can be displayed in
columns running vertically on either side the tree\.  You can control
the color, font, etc of each entry\.  Any entry label or data field can
be edited in\-place\.  

TREE DATA OBJECT
================

The tree is not stored inside the widget but in a tree data object (see
the __tree__ command for a further explanation)\.  Tree data objects can be
shared among different clients, such as a __treeview__ widget or the __tree__
command\.  You can walk the tree and manage its data with the __tree__
command tree, while displaying it with the __treeview__ widget\.  Whenever
the tree is updated, the __treeview__ widget is automatically redrawn\.

By default, the __treeview__ widget creates its own tree object\.  The tree
initially contains just a root node\.  But you can also display trees
created by the __tree__ command using the __\-tree__ configuration option\.
__Treeview__ widgets can share the same tree object, possibly displaying
different views of the same data\.  

A tree object has both a Tcl and C API\.  You can insert or delete nodes
using __treeview__ widget or __tree__ command operations, but also from C code\.
For example, you can load the tree from your C code while still
managing and displaying the tree from Tcl\. The widget is automatically
notified whenever the tree is modified via C or Tcl\.  

SYNTAX
======

__treeview__ *pathName* ?*option* *value*?\.\.\.  The __treeview__ command creates a new
window *pathName* and makes it into a __treeview__ widget\.  At the time this
command is invoked, there must not exist a window named *pathName*, but
*pathName*\'s parent must exist\.  Additional options may be specified on
the command line or in the option database to configure aspects of the
widget such as its colors and font\.  See the __configure__ operation below
for the exact details about what *option* and *value* pairs are valid\.

If successful, __treeview__ returns the path name of the widget\.  It also
creates a new Tcl command by the same name\.  You can use this command
to invoke various operations that query or modify the widget\.  The
general form is: *pathName* *operation* ?*arg*?\.\.\.  Both *operation* and its
arguments determine the exact behavior of the command\.  The operations
available are described in the __TREEVIEW OPERATIONS__ section\.

IDS AND TAGS
============

Nodes can be inserted into a tree using the __treeview__ widget

~~~~~
rbc::treeview .t
set node [.t insert end root "one"]
~~~~~

or __tree__ command\.  

~~~~~
set tree [rbc::tree create]
set node [$tree insert root "one"]
~~~~~

In both cases, a number identifying the node is returned (the value of
\$node)\.  This serial number or *id* uniquely identifies the node\.  Please
note that you can\'t infer a location or position of a node from its id\.
The only exception is that the root node is always id 0\. Since nodes
may have the same labels or be moved within the tree, ids provide an
convenient way to identify nodes\.  If a tree is shared, the ids will be
the same regardless if you are using by the __treeview__ widget or the __tree__
command\.  Ids are recycled when the node deleted\.  

A node may also have any number of *tags* associated with it\.  A tag is
just a string of characters, and it may take any form except that of an
integer\.  For example, "x123" is valid, but "123" isn\'t\.  The same tag
may be associated with many different nodes\.  This is typically done to
associate a group of nodes\.  Many operations in the __treeview__ widget
take either node ids or tag names as arguments\.  Using a tag says to
apply the operation to all nodes with that tag\.  

The tag __all__ is implicitly associated with every node in the tree\.  It
may be used to invoke operations on all the nodes in the tree\.

Tags may be shared, just like trees, between clients\.  For example, you
can use the tags created by the __tree__ command with __treeview__ widgets\.

SPECIAL NODE IDS
================

There are also several special non\-numeric ids\.  Special ids differ
from tags in that they are always translated to their numeric
equivalent\.  They also take precedence over tags\.  For example, you
can\'t use a tag name that is a special id\.  These ids are specific to
the __treeview__ widget\.  

active
:   The node where the mouse pointer is currently located\.
    When a node is active, it is drawn using its active icon
    (see the __\-activeicon__ option)\.  The __active__ id is changed
    automatically by moving the mouse pointer over another
    node or by using the __entry activate__ operation\. Note that
    there can be only one active node at a time\.

anchor
:   The node representing the fixed end of the current
    selection\.  The anchor is set by the __selection anchor__
    operation\.  

current
:   The node where the mouse pointer is currently located\.
    But unlike __active__, this id changes while the selection
    is dragged\.  It is used to determine the current node
    during button drags\.  

down
:   The next open node from the current focus\. The __down__ of
    the last open node is the same\.  

end
:   The last open node (in depth\-first order) on the tree\.

focus
:   The node that currently has focus\.  When a node has
    focus, it receives key events\.  To indicate focus, the
    node is drawn with a dotted line around its label\.  You
    can change the focus using the __focus__ operation\.

last
:   The last open node from the current focus\. But unlike
    __up__, when the focus is at root, __last__ wraps around to the
    last open node in the tree\.  

mark
:   The node representing the non\-fixed end of the current
    selection\.  The mark is set by the __selection mark__
    operation\.  

next
:   The next open node from the current focus\.  But unlike
    __down__, when the focus is on last open node, __next__ wraps
    around to the root node\.  

nextsibling
:   The next sibling from the node with the current focus\.
    If the node is already the last sibling then it is the
    __nextsibling\.__  

parent
:   The parent of the node with the current focus\. The
    __parent__ of the root is also the root\.  

prevsibling
:   The previous sibling from the node with the current
    focus\.  If the node is already the first sibling then it
    is the __prevsibling\.__  

root
:   The root node\. You can also use id 0 to indicate the
    root\.  

up
:   The last open node (in depth\-first order) from the
    current focus\. The __up__ of the root node (i\.e\. the root
    has focus) is also the root\.  

view\.top
:   First node that\'s current visible in the widget\.

view\.bottom
:   Last node that\'s current visible in the widget\.

*path*
:   Absolute path of a node\.  Path names refer to the node
    name, not their entry labels\. Paths don\'t have to start
    with a separator (see the __\-separator__ configuration
    option), but component names must be separated by the
    designated separator\.  

\@*x*,*y*
:   Indicates the node that covers the point in the treeview
    window specified by *x* and *y* (in pixel coordinates)\.  If
    no part of the entryd covers that point, then the
    closest node to that point is used\.  

A node may be specified as an id or tag\. If the specifier is an integer
then it is assumed to refer to the single node with that id\.  If the
specifier is not an integer, it\'s checked to see if it\'s a special id
(such as focus)\.  Otherwise, it\'s assumed to be tag\.  Some operations
only operate on a single node at a time; if a tag refers to more than
one node, then an error is generated\.  

DATA FIELDS
===========

A node in the tree can have *data* *fields*\.  A data field is a name\-value
pair, used to represent arbitrary data in the node\.  Nodes can contain
different fields (they aren\'t required to contain the same fields)\.
You can optionally display these fields in the __treeview__ widget in
columns running on either side of the displayed tree\.  A node\'s value
for the field is drawn in the column along side its node in the
hierarchy\.  Any node that doesn\'t have a specific field is left blank\.
Columns can be interactively resized, hidden, or, moved\.

ENTRY BINDINGS
==============

You can bind Tcl commands to be invoked when events occur on nodes
(much like Tk canvas items)\.  You can bind a node using its id or its
*bindtags*\.  Bindtags are simply names that associate a binding with one
or more nodes\.  There is a built\-in tag all that all node entries
automatically have\.  

TREEVIEW OPERATIONS
===================

The __treeview__ operations are the invoked by specifying the widget\'s
pathname, the operation, and any arguments that pertain to that
operation\.  The general form is:  

~~~~~
pathName operation ?arg arg ...?
~~~~~

*Operation* and the *arg*s determine the exact behavior of the command\.
The following operation are available for __treeview__ widgets:

*pathName* __bbox__ ?__\-screen__? *tagOrId\.\.\.*

:   Returns a list of 4 numbers, representing a bounding box of
    around the specified entries\. The entries is given by one or
    more *tagOrId* arguments\.  If the __\-screen__ flag is given, then the
    x\-y coordinates of the bounding box are returned as screen
    coordinates, not virtual coordinates\. Virtual coordinates start
    from 0 from the root node\.  The returned list contains the
    following values\.  

    *x*
    :   X\-coordinate of the upper\-left corner of the
        bounding box\.  

    *y*
    :   Y\-coordinate of the upper\-left corner of the
        bounding box\.  

    *width*
    :   Width of the bounding box\.

    *height*
    :   Height of the bounding box\.

*pathName* __bind__ *tagName* ?*sequence* *command*?

:   Associates *command* with *tagName* such that whenever the event
    sequence given by *sequence* occurs for a node with this tag,
    *command* will be invoked\.  The syntax is similar to the __bind__
    command except that it operates on __treeview__ entries, rather than
    widgets\. See the __bind__ manual entry for complete details on
    *sequence* and the substitutions performed on *command* before
    invoking it\.  

    If all arguments are specified then a new binding is created,
    replacing any existing binding for the same *sequence* and
    *tagName*\.  If the first character of *command* is + then *command*
    augments an existing binding rather than replacing it\.  If no
    *command* argument is provided then the command currently
    associated with *tagName* and *sequence* (it\'s an error occurs if
    there\'s no such binding) is returned\.  If both *command* and
    *sequence* are missing then a list of all the event sequences for
    which bindings have been defined for *tagName*\.  

*pathName* __button__ *operation* ?*args*?

:   This command is used to control the button selectors within a
    __treeview__ widget\.  It has several forms, depending on *operation*:

    *pathName* __button activate__ *tagOrId*

    :   Designates the node given by *tagOrId* as active\.  When a
        node is active it\'s entry is drawn using its active icon
        (see the __\-activeicon__ option)\.  Note that there can be
        only one active entry at a time\.  The special id __active__
        indicates the currently active node\.  

    *pathName* __button bind__ *tagName* ?*sequence* *command*?

    :   Associates *command* with *tagName* such that whenever the
        event sequence given by *sequence* occurs for an button of
        a node entry with this tag, *command* will be invoked\.  The
        syntax is similar to the __bind__ command except that it
        operates on __treeview__ buttons, rather than widgets\. See
        the __bind__ manual entry for complete details on *sequence*
        and the substitutions performed on *command* before
        invoking it\.  

        If all arguments are specified then a new binding is
        created, replacing any existing binding for the same
        *sequence* and *tagName*\.  If the first character of *command*
        is + then *command* augments an existing binding rather
        than replacing it\.  If no *command* argument is provided
        then the command currently associated with *tagName* and
        *sequence* (it\'s an error occurs if there\'s no such
        binding) is returned\.  If both *command* and *sequence* are
        missing then a list of all the event sequences for which
        bindings have been defined for *tagName*\.

    *pathName* __button cget__ *option*

    :   Returns the current value of the configuration option
        given by *option*\.  *Option* may have any of the values
        accepted by the __configure__ operation described below\.

    *pathName* __button configure__ ?*option*? ?*value* *option* *value* *\.\.\.*?

    :   Query or modify the configuration options of the widget\.
        If no *option* is specified, returns a list describing all
        of the available options for *pathName* (see
        __Tk\_ConfigureInfo__ for information on the format of this
        list)\.  If *option* is specified with no *value*, then the
        command returns a list describing the one named option
        (this list will be identical to the corresponding sublist
        of the value returned if no *option* is specified)\.  If one
        or more *option\-value* pairs are specified, then the
        command modifies the given widget option(s) to have the
        given value(s);  in this case the command returns an
        empty string\.  *Option* and *value* are described in the
        section __BUTTON OPTIONS__ below\.  

*pathName* __cget__ *option*

:   Returns the current value of the configuration option given by
    *option*\.  *Option* may have any of the values accepted by the
    __configure__ operation described below\.  

*pathName* __close__ ?__\-recurse__? *tagOrId\.\.\.*

:   Closes the node specified by *tagOrId*\.  In addition, if a Tcl
    script was specified by the __\-closecommand__ option, it is invoked\.
    If the node is already closed, this command has no effect\.  If
    the __\-recurse__ flag is present, each child node is recursively
    closed\.  

*pathName* __column__ *operation* ?*args*?

:   The following operations are available for treeview columns\.

    *pathName* __column activate__ *column*

    :   Sets the active column to *column*\.  *Column* is the name of
        a column in the widget\.  When a column is active, it\'s
        drawn using its __\-activetitlebackground__ and
        __\-activetitleforeground__ options\.  If *column* is the "",
        then no column will be active\.  If no column argument is
        provided, then the name of the currently active column is
        returned\.  

    *pathName* __column cget__ *name* *option*

    :   Returns the current value of the column configuration
        option given by *option* for *name*\.  *Name* is the name of
        column that corresponds to a data field\.  *Option* may have
        any of the values accepted by the __configure__ operation
        described below\.  

    *pathName* __column configure__ *name* ?*option*? ?*value* *option* *value* *\.\.\.*?

    :   Query or modify the configuration options of the column
        designated by *name*\. *Name* is the name of the column
        corresponding to a data field\.  If no *option* is
        specified, returns a list describing all of the available
        options for *pathName* (see __Tk\_ConfigureInfo__ for
        information on the format of this list)\.  If *option* is
        specified with no *value*, then the command returns a list
        describing the one named option (this list will be
        identical to the corresponding sublist of the value
        returned if no *option* is specified)\.  If one or more
        *option\-value* pairs are specified, then the command
        modifies the given widget option(s) to have the given
        value(s);  in this case the command returns an empty
        string\.  *Option* and *value* are described in the section
        __COLUMN OPTIONS__ below\.  

    *pathName* __column delete__ *field* ?*field*\.\.\.?

    :   Deletes one of more columns designated by *field*\.  Note
        that this does not delete the data fields themselves\.

    *pathName* __column insert__ *position* *field* ?*options*\.\.\.?

    :   Inserts one of more columns designated by *field*\.  A
        column displays each node\'s data field by the same name\.
        If the node doesn\'t have the given field, the cell is
        left blank\.  *Position* indicates where in the list of
        columns to add the new column\.  It may be either a number
        or end\.  

    *pathName* __column invoke__ *field*

    :   Invokes the Tcl command associated with the column *field*,
        if there is one (using the column\'s __\-command__ option)\.
        The command is ignored if the column\'s __\-state__ option set
        to disabled\.  

    *pathName* __column move__ *name* *dest*

    :   Moves the column *name* to the destination position\.  *Dest*
        is the name of another column or a screen position in the
        form \@*x,y*\.  

    *pathName* __column names__

    :   Returns a list of the names of all columns in the widget\.
        The list is ordered as the columns are drawn from left\-
        to\-right\.  

    *pathName* __column nearest__ *x* ?*y*?

    :   Returns the name of the column closest to the given X\-Y
        screen coordinate\.  If you provide a *y* argument (it\'s
        optional), a name is returned only when if the point is
        over a column\'s title\.  

*pathName* __configure__ ?*option*? ?*value* *option* *value* *\.\.\.*?

:   Query or modify the configuration options of the widget\.  If no
    *option* is specified, returns a list describing all of the
    available options for *pathName* (see __Tk\_ConfigureInfo__ for
    information on the format of this list)\.  If *option* is specified
    with no *value*, then the command returns a list describing the
    one named option (this list will be identical to the
    corresponding sublist of the value returned if no *option* is
    specified)\.  If one or more *option\-value* pairs are specified,
    then the command modifies the given widget option(s) to have the
    given value(s);  in this case the command returns an empty
    string\.  *Option* and *value* are described in the section __TREEVIEW__
    __OPTIONS__ below\.  

*pathName* __curselection__

:   Returns a list containing the ids of all of the entries that are
    currently selected\.  If there are no entries selected, then the
    empty string is returned\.  

*pathName* __delete__ *tagOrId*\.\.\.

:   Deletes one or more entries given by *tagOrId* and its children\.

*pathName* __entry__ *operation* ?*args*?

:   The following operations are available for treeview entries\.

    *pathName* __entry activate__ *tagOrId*

    :   Sets the active entry to the one specified by *tagOrId*\.
        When an entry is active it is drawn using its active icon
        (see the __\-activeicon__ option)\.  Note that there can be
        only one active node at a time\.  The special id of the
        currently active node is __active__\.  

    *pathName* __entry cget__ *option*

    :   Returns the current value of the configuration option
        given by *option*\.  *Option* may have any of the values
        accepted by the __configure__ operation described below\.

    *pathName* __entry children__ *tagOrId*  ?*first*? ?*last*?

    :   Returns a list of ids for the given range of children of
        *tagOrId*\.  *TagOrId* is the id or tag of the node to be
        examined\.  If only a *first* argument is present, then the
        id of the that child at that numeric position is
        returned\.  If both *first* and *last* arguments are given,
        then the ids of all the children in that range are
        returned\.  Otherwise the ids of all children are
        returned\.  

    *pathName* __entry configure__ ?*option*? ?*value* *option* *value* *\.\.\.*?

    :   Query or modify the configuration options of the widget\.
        If no *option* is specified, returns a list describing all
        of the available options for *pathName* (see
        __Tk\_ConfigureInfo__ for information on the format of this
        list)\.  If *option* is specified with no *value*, then the
        command returns a list describing the one named option
        (this list will be identical to the corresponding sublist
        of the value returned if no *option* is specified)\.  If one
        or more *option\-value* pairs are specified, then the
        command modifies the given widget option(s) to have the
        given value(s);  in this case the command returns an
        empty string\.  *Option* and *value* are described below:

    *pathName* __entry delete__ *tagOrId* ?*first* ?*last*?

    :   Deletes the one or more children nodes of the parent
        *tagOrId*\.  If *first* and *last* arguments are present, they
        are positions designating a range of children nodes to be
        deleted\.  

    *pathName* __entry isbefore__ *tagOrId1* *tagOrId2*

    :   Returns 1 if *tagOrId1* is before *tagOrId2* and 0 otherwise\.

    *pathName* __entry ishidden__ *tagOrId*

    :   Returns 1 if the node is currently hidden and 0
        otherwise\.  A node is also hidden if any of its ancestor
        nodes are closed or hidden\.  

    *pathName* __entry isopen__ *tagOrId*

    :   Returns 1 if the node is currently open and 0 otherwise\.

    *pathName* __entry size \-recurse__ *tagOrId*

    :   Returns the number of children for parent node *tagOrId*\.
        If the __\-recurse__ flag is set, the number of all its
        descendants is returned\.  The node itself is not counted\.

*pathName* __find__ ?*flags*? *first* *last*

:   Finds for all entries matching the criteria given by *flags*\.  A
    list of ids for all matching nodes is returned\. *First* and *last*
    are ids designating the range of the search in depth\-first
    order\. If *last* is before *first*, then nodes are searched in
    reverse order\.  The valid flags are:  

    \-name *pattern*
    :   Specifies pattern to match against node names\.

    \-full *pattern*
    :   Specifies pattern to match against node pathnames\.

    \-*option* *pattern*
    :   Specifies pattern to match against the node entry\'s
        configuration option\.  

    \-exact
    :   Patterns must match exactly\.  The is the default\.

    \-glob
    :   Use global pattern matching\.  Matching is done in a
        fashion similar to that used by the C\-shell\.  For
        the  two strings  to match, their contents must be
        identical except that the  following  special
        sequences  may appear in pattern:  

        \*
        :   Matches  any  sequence  of  characters in
            string, including a null string\.

        ?
        :   Matches any single character in string\.

        \[*chars\]*
        :   Matches any character in the set given by
            *chars*\. If a sequence of the form *x*\-*y* appears in
            *chars*, then any character between *x* and *y*,
            inclusive, will match\.  

        \\\\*x*
        :   Matches  the  single  character  *x*\.  This
            provides a way of  avoiding  the  special
            interpretation of the characters \*?\[\]\\ in the
            pattern\.  

    \-regexp
    :   Use regular expression pattern matching (i\.e\. the
        same as implemented by the __regexp__ command)\.

    \-nonmatching
    :   Pick entries that don\'t match\.

    \-exec *string*
    :   Specifies a Tcl script to be invoked for each
        matching node\.  Percent substitutions are performed
        on *string* before it is executed\.  The following
        substitutions are valid:  

        %W
        :   The pathname of the widget\.

        %p
        :   The name of the node\.

        %P
        :   The full pathname of the node\.

        %#
        :   The id of the node\.

        %%
        :   Translates to a single percent\.

    \-count *number*
    :   Stop searching after *number* matches\.

    \-\-
    :   Indicates the end of flags\.

*pathName* __focus__  *tagOrId*

:   Sets the focus to the node given by *tagOrId*\.  When a node has
    focus, it can receive keyboard events\.  The special id __focus__
    designates the node that currently has focus\.  

*pathName* __get__ ?__\-full__? *tagOrId* *tagOrId*\.\.\.

:   Translates one or more ids to their node entry names\.  It
    returns a list of names for all the ids specified\.  If the __\-full__
    flag is set, then the full pathnames are returned\.

*pathName* __hide__ ?__flags__? *tagOrId*\.\.\.

:   Hides all nodes matching the criteria given by *flags*\.  The
    search is performed recursively for each node given by *tagOrId*\.
    The valid flags are described below:  

    \-name *pattern*
    :   Specifies pattern to match against node names\.

    \-full *pattern*
    :   Specifies pattern to match against node pathnames\.

    \-*option* *pattern*
    :   Specifies pattern to match against the node entry\'s
        configuration option\.  

    \-exact
    :   Match patterns exactly\.  The is the default\.

    \-glob
    :   Use global pattern matching\.  Matching is done in a
        fashion similar to that used by the C\-shell\.  For
        the  two strings  to match, their contents must be
        identical except that the  following  special
        sequences  may appear in pattern:  

        \*
        :   Matches  any  sequence  of  characters in
            string, including a null string\.

        ?
        :   Matches any single character in string\.

        \[*chars\]*
        :   Matches any character in the set given by
            *chars*\. If a sequence of the form *x*\-*y* appears in
            *chars*, then any character between *x* and *y*,
            inclusive, will match\.  

        \\\\*x*
        :   Matches  the  single  character  *x*\.  This
            provides a way of  avoiding  the  special
            interpretation of the characters \*?\[\]\\ in the
            pattern\.  

    \-regexp
    :   Use regular expression pattern matching (i\.e\. the
        same as implemented by the __regexp__ command)\.

    \-nonmatching
    :   Hide nodes that don\'t match\.

    \-\-
    :   Indicates the end of flags\.

*pathName* __index__ ?__\-at__ *tagOrId*? *string*

:   Returns the id of the node specified by *string*\.  *String* may be a
    tag or node id\.  Some special ids are normally relative to the
    node that has focus\.  The __\-at__ flag lets you select another node\.

*pathName* __insert__ ?__\-at__ *tagOrId*? *position* *path* ?*options\.\.\.*? ?*path*? ?*options\.\.\.*?

:   Inserts one or more nodes at *position*\.  *Position* is the location
    (number or end) where the new nodes are added to the parent
    node\.  *Path* is the pathname of the new node\.  Pathnames can be
    formated either as a Tcl list (each element is a path component)
    or as a string separated by a special character sequence (using
    the __\-separator__ option)\.  Pathnames are normally absolute, but
    the __\-at__ switch lets you select a relative starting point\.  Its
    value is the id of the starting node\.  

    All ancestors of the new node must already exist, unless the
    __\-autocreate__ option is set\.  It is also an error if a node
    already exists, unless the __\-allowduplicates__ option is set\.

    *Option* and *value* may have any of the values accepted by the
    __entry configure__ operation described in the __ENTRY OPERATIONS__
    section below\.  This command returns a list of the ids of the
    new entries\.  

*pathName* __move__ *tagOrId* *how* *destId*

:   Moves the node given by *tagOrId* to the destination node\.  The
    node can not be an ancestor of the destination\.  *DestId* is the
    id of the destination node and can not be the root of the tree\.
    In conjunction with *how*, it describes how the move is performed\.

    before
    :   Moves the node before the destination node\.

    after
    :   Moves the node after the destination node\.

    into
    :   Moves the node to the end of the destination\'s list of
        children\.  

*pathName* __nearest__ *x* *y* ?*varName*?

:   Returns the id of the node entry closest to the given X\-Y screen
    coordinate\.  The optional argument *varName* is the name of
    variable which is set to either button or select to indicate
    over what part of the node the coordinate lies\.  If the
    coordinate is not directly over any node, then *varName* will
    contain the empty string\.  

*pathName* __open__ ?__\-recurse__? *tagOrId\.\.\.*

:   Opens the one or more nodes specified by *tagOrId*\.  If a node is
    not already open, the Tcl script specified by the __\-opencommand__
    option is invoked\. If the __\-recurse__ flag is present, then each
    descendant is recursively opened\.  

*pathName* __range__ ?__\-open__? *first* *last*

:   Returns the ids in depth\-first order of the nodes between the
    *first* and *last* ids\.  If the __\-open__ flag is present, it indicates
    to consider only open nodes\.  If *last* is before *first*, then the
    ids are returned in reverse order\.  

*pathName* __scan__ *option* *args*

:   This command implements scanning\.  It has two forms, depending
    on *option*:  

    *pathName* __scan mark__ *x* *y*

    :   Records *x* and *y* and the current view in the treeview
        window;  used in conjunction with later __scan dragto__
        commands\.  Typically this command is associated with a
        mouse button press in the widget\.  It returns an empty
        string\.  

    *pathName* __scan dragto__ *x* *y*\.

    :   Computes the difference between its *x* and *y* arguments and
        the *x* and *y* arguments to the last __scan mark__ command for
        the widget\.  It then adjusts the view by 10 times the
        difference in coordinates\.  This command is typically
        associated with mouse motion events in the widget, to
        produce the effect of dragging the list at high speed
        through the window\.  The return value is an empty string\.

*pathName* __see__ ?__\-anchor__ *anchor*? *tagOrId*

:   Adjusts the view of entries so that the node given by *tagOrId* is
    visible in the widget window\.  It is an error if __tagOrId__ is a
    tag that refers to more than one node\.  By default the node\'s
    entry is displayed in the middle of the window\.  This can
    changed using the __\-anchor__ flag\.  Its value is a Tk anchor
    position\.  

*pathName* __selection__ *option* *arg*

:   This command is used to adjust the selection within a __treeview__
    widget\.  It has several forms, depending on *option*:

    *pathName* __selection anchor__ *tagOrId*

    :   Sets the selection anchor to the node given by *tagOrId*\.
        If *tagOrId* refers to a non\-existent node, then the
        closest node is used\.  The selection anchor is the end of
        the selection that is fixed while dragging out a
        selection with the mouse\.  The special id __anchor__ may be
        used to refer to the anchor node\.  

    *pathName* __selection cancel__

    :   Clears the temporary selection of entries back to the
        current anchor\.  Temporary selections are created by the
        __selection mark__ operation\.  

    *pathName* __selection clear__ *first* ?*last*?

    :   Removes the entries between *first* and *last* (inclusive)
        from the selection\.  Both *first* and *last* are ids
        representing a range of entries\.  If *last* isn\'t given,
        then only *first* is deselected\.  Entries outside the
        selection are not affected\.  

    *pathName* __selection clearall__

    :   Clears the entire selection\.

    *pathName* __selection mark__ *tagOrId*

    :   Sets the selection mark to the node given by *tagOrId*\.
        This causes the range of entries between the anchor and
        the mark to be temporarily added to the selection\.  The
        selection mark is the end of the selection that is fixed
        while dragging out a selection with the mouse\.  The
        special id __mark__ may be used to refer to the current mark
        node\.  If *tagOrId* refers to a non\-existent node, then the
        mark is ignored\.  Resetting the mark will unselect the
        previous range\.  Setting the anchor finalizes the range\.

    *pathName* __selection includes__ *tagOrId*

    :   Returns 1 if the node given by *tagOrId* is currently
        selected, 0 if it isn\'t\.  

    *pathName* __selection present__

    :   Returns 1 if any nodes are currently selected and 0
        otherwise\.  

    *pathName* __selection set__ *first* ?*last*?

    :   Selects all of the nodes in the range between *first* and
        *last*, inclusive, without affecting the selection state of
        nodes outside that range\.  

    *pathName* __selection toggle__ *first* ?*last*?

    :   Selects/deselects nodes in the range between *first* and
        *last*, inclusive, from the selection\.  If a node is
        currently selected, it becomes deselected, and visa
        versa\.  

*pathName* __show__ ?__flags__? *tagOrId*\.\.\.

:   Exposes all nodes matching the criteria given by *flags*\.  This is
    the inverse of the __hide__ operation\.  The search is performed
    recursively for each node given by *tagOrId*\.  The valid flags are
    described below:  

    \-name *pattern*
    :   Specifies pattern to match against node names\.

    \-full *pattern*
    :   Specifies pattern to match against node pathnames\.

    \-*option* *pattern*
    :   Specifies pattern to match against the entry\'s
        configuration option\.  

    \-exact
    :   Match patterns exactly\.  The is the default\.

    \-glob
    :   __\-glob__ Use global pattern matching\.  Matching is done
        in a fashion similar to that used by the C\-shell\.
        For  the  two strings  to match, their contents must
        be identical except that the  following  special
        sequences  may appear in pattern:  

        \*
        :   Matches  any  sequence  of  characters in
            string, including a null string\.

        ?
        :   Matches any single character in string\.

        \[*chars\]*
        :   Matches any character in the set given by
            *chars*\. If a sequence of the form *x*\-*y* appears in
            *chars*, then any character between *x* and *y*,
            inclusive, will match\.  

        \\\\*x*
        :   Matches  the  single  character  *x*\.  This
            provides a way of  avoiding  the  special
            interpretation of the characters \*?\[\]\\ in the
            pattern\.  

    \-regexp
    :   Use regular expression pattern matching (i\.e\. the
        same as implemented by the __regexp__ command)\.

    \-nonmatching
    :   Expose nodes that don\'t match\.

    \-\-
    :   Indicates the end of flags\.

*pathName* __sort__ ?*operation*? *args\.\.\.*

: …

    *pathName* __sort auto__ ?*boolean*

    :   Turns on/off automatic sorting of node entries\.  If
        *boolean* is true, entries will be automatically sorted as
        they are opened, closed, inserted, or deleted\.  If no
        *boolean* argument is provided, the current state is
        returned\.  

    *pathName* __sort cget__ *option*

    :   Returns the current value of the configuration option
        given by *option*\.  *Option* may have any of the values
        accepted by the __configure__ operation described below\.

    *pathName* __sort configure__ ?*option*? ?*value* *option* *value* *\.\.\.*?

    :   Query or modify the sorting configuration options of the
        widget\.  If no *option* is specified, returns a list
        describing all of the available options for *pathName* (see
        __Tk\_ConfigureInfo__ for information on the format of this
        list)\.  If *option* is specified with no *value*, then the
        command returns a list describing the one named option
        (this list will be identical to the corresponding sublist
        of the value returned if no *option* is specified)\.  If one
        or more *option\-value* pairs are specified, then the
        command modifies the given sorting option(s) to have the
        given value(s);  in this case the command returns an
        empty string\.  *Option* and *value* are described below:

        \-column *string*
        :   Specifies the column to sort\. Entries in the
            widget are rearranged according to this column\.
            If *column* is "" then no sort is performed\.

        \-command *string*
        :   Specifies a Tcl procedure to be called when
            sorting nodes\.  The procedure is called with three
            arguments: the pathname of the widget and the
            fields of two entries\.  The procedure returns 1 if
            the first node is greater than the second, \-1 is
            the second is greater, and 0 if equal\.

        \-decreasing *boolean*
        :   Indicates to sort in ascending/descending order\.
            If *boolean* is true, then the entries as in
            descending order\. The default is no\.

        \-mode *string*
        :   Specifies how to compare entries when sorting\.
            *String* may be one of the following:

            ascii
            :   Use string comparison based upon
                the ASCII collation order\.

            dictionary
            :   Use dictionary\-style comparison\.
                This is the same as ascii except
                (a) case is ignored except as a
                tie\-breaker and (b) if two strings
                contain embedded numbers, the
                numbers compare as integers, not
                characters\.  For example, "bigBoy"
                sorts between "bigbang" and
                "bigboy", and "x10y" sorts between
                "x9y" and "x11y"\.

            integer
            :   Compares fields as integers\.

            real
            :   Compares fields as floating point
                numbers\.  

            command
            :   Use the Tcl proc specified by the
                __\-command__ option to compare entries
                when sorting\.   If no command is
                specified, the sort reverts to
                ascii sorting\.  

    *pathName* __sort once__ ?*flags*? *tagOrId\.\.\.*

    :   Sorts the children for each entries specified by *tagOrId*\.
        By default, entries are sorted by name, but you can
        specify a Tcl proc to do your own comparisons\.

        \-recurse
        :   Recursively sort the entire branch, not
            just the children\.  

*pathName* __tag__ *operation* *args*

:   Tags are a general means of selecting and marking nodes in the
    tree\.  A tag is just a string of characters, and it may take any
    form except that of an integer\.  The same tag may be associated
    with many different nodes\.  

    Both *operation* and its arguments determine the exact behavior of
    the command\.  The operations available for tags are listed
    below\.  

    *pathName* __tag add__ *string* *id*\.\.\.

    :   Adds the tag *string* to one of more entries\.

    *pathName* __tag delete__ *string* *id*\.\.\.

    :   Deletes the tag *string* from one or more entries\.

    *pathName* __tag forget__ *string*

    :   Removes the tag *string* from all entries\.  It\'s not an
        error if no entries are tagged as *string*\.

    *pathName* __tag names__ ?*id*?

    :   Returns a list of tags used\.  If an *id* argument is
        present, only those tags used by the node designated by
        *id* are returned\.  

    *pathName* __tag nodes__ *string*

    :   Returns a list of ids that have the tag *string*\.  If no
        node is tagged as *string*, then an empty string is
        returned\.  

*pathName* __text__ *operation* ?*args*?

:   This operation is used to provide text editing for cells (data
    fields in a column) or entry labels\.  It has several forms,
    depending on *operation*:  

    *pathName* __text apply__

    :   Applies the edited buffer, replacing the entry label or
        data field\. The edit window is hidden\.  

    *pathName* __text cancel__

    :   Cancels the editing operation, reverting the entry label
        or data value back to the previous value\. The edit window
        is hidden\.  

    *pathName* __text cget__ *value*

    :   Returns the current value of the configuration option
        given by *option*\.  *Option* may have any of the values
        accepted by the __configure__ operation described below\.

    *pathName* __text configure__ ?*option* *value*?

    :   Query or modify the configuration options of the edit
        window\.  If no *option* is specified, returns a list
        describing all of the available options (see
        __Tk\_ConfigureInfo__ for information on the format of this
        list)\.  If *option* is specified with no *value*, then the
        command returns a list describing the one named option
        (this list will be identical to the corresponding sublist
        of the value returned if no *option* is specified)\.  If one
        or more *option\-value* pairs are specified, then the
        command modifies the given widget option(s) to have the
        given value(s);  in this case the command returns an
        empty string\.  *Option* and *value* are described in the
        section __TEXT EDITING OPTIONS__ below\.  

*pathName* __text delete__ *first* *last*

:   Deletes the characters in the edit buffer between the two given
    character positions\.  

*pathName* __text get__ ?*\-root*? *x* *y*

: …

*pathName* __text icursor__ *index*

: …

*pathName* __text index__ *index*

:   Returns the text index of given *index*\.

*pathName* __text insert__ *index* *string*

:   Insert the text string *string* into the edit buffer at the index
    *index*\.  For example, the index 0 will prepend the buffer\.

*pathName* __text selection__ *args*

:   This operation controls the selection of the editing window\.
    Note that this differs from the selection of entries\.  It has
    the following forms:  

    *pathName* __text selection adjust__ *index*

    :   Adjusts either the first or last index of the selection\.

    *pathName* __text selection clear__

    :   Clears the selection\.

    *pathName* __text selection from__ *index*

    :   Sets the anchor of the selection\.

    *pathName* __text selection present__

    :   Indicates if a selection is present\.

    *pathName* __text selection range__ *start* *end*

    :   Sets both the anchor and mark of the selection\.

    *pathName* __text selection to__ *index*

    :   Sets the unanchored end (mark) of the selection\.

*pathName* __toggle__ *tagOrId*

:   Opens or closes the node given by *tagOrId*\.  If the corresponding
    __\-opencommand__ or __\-closecommand__ option is set, then that command
    is also invoked\.  

*pathName* __xview__ *args*

:   This command is used to query and change the horizontal position
    of the information in the widget\'s window\.  It can take any of
    the following forms:  

    *pathName* __xview__

    :   Returns a list containing two elements\.  Each element is
        a real fraction between 0 and 1;  together they describe
        the horizontal span that is visible in the window\.  For
        example, if the first element is \.2 and the second
        element is \.6, 20% of the __treeview__ widget\'s text is off\-
        screen to the left, the middle 40% is visible in the
        window, and 40% of the text is off\-screen to the right\.
        These are the same values passed to scrollbars via the
        __\-xscrollcommand__ option\.  

    *pathName* __xview__ *tagOrId*

    :   Adjusts the view in the window so that the character
        position given by *tagOrId* is displayed at the left edge
        of the window\.  Character positions are defined by the
        width of the character __0__\.  

    *pathName* __xview moveto__ *fraction*

    :   Adjusts the view in the window so that *fraction* of the
        total width of the __treeview__ widget\'s text is off\-screen
        to the left\.  *fraction* must be a fraction between 0 and
        1\.  

    *pathName* __xview scroll__ *number* *what*

    :   This command shifts the view in the window left or right
        according to *number* and *what*\.  *Number* must be an integer\.
        *What* must be either __units__ or __pages__ or an abbreviation of
        one of these\.  If *what* is __units__, the view adjusts left or
        right by *number* character units (the width of the __0__
        character) on the display;  if it is __pages__ then the view
        adjusts by *number* screenfuls\.  If *number* is negative then
        characters farther to the left become visible;  if it is
        positive then characters farther to the right become
        visible\.  

*pathName* __yview__ *?args*?

:   This command is used to query and change the vertical position
    of the text in the widget\'s window\.  It can take any of the
    following forms:  

    *pathName* __yview__

    :   Returns a list containing two elements, both of which are
        real fractions between 0 and 1\.  The first element gives
        the position of the node at the top of the window,
        relative to the widget as a whole (0\.5 means it is
        halfway through the treeview window, for example)\.  The
        second element gives the position of the node just after
        the last one in the window, relative to the widget as a
        whole\.  These are the same values passed to scrollbars
        via the __\-yscrollcommand__ option\.  

    *pathName* __yview__ *tagOrId*

    :   Adjusts the view in the window so that the node given by
        *tagOrId* is displayed at the top of the window\.

    *pathName* __yview moveto__ *fraction*

    :   Adjusts the view in the window so that the node given by
        *fraction* appears at the top of the window\.  *Fraction* is a
        fraction between 0 and 1;  0 indicates the first node,
        0\.33 indicates the node one\-third the way through the
        __treeview__ widget, and so on\.  

    *pathName* __yview scroll__ *number* *what*

    :   This command adjusts the view in the window up or down
        according to *number* and *what*\.  *Number* must be an integer\.
        *What* must be either __units__ or __pages__\.  If *what* is __units__,
        the view adjusts up or down by *number* lines;  if it is
        __pages__ then the view adjusts by *number* screenfuls\.  If
        *number* is negative then earlier nodes become visible;  if
        it is positive then later nodes become visible\.

TREEVIEW OPTIONS
================

In addition to the __configure__ operation, widget configuration options
may also be set by the Tk __option__ command\.  The class resource name is
TreeView\.  

~~~~~
option add *TreeView.Foreground white
option add *TreeView.Background blue
~~~~~

The following widget options are available:  

\-activebackground *color*
:   Sets the background color for active entries\.  A node is active
    when the mouse passes over it\'s entry or using the __activate__
    operation\.  

\-activeforeground *color*
:   Sets the foreground color of the active node\.  A node is active
    when the mouse passes over it\'s entry or using the __activate__
    operation\.  

\-activeicons *images*
:   Specifies images to be displayed for an entry\'s icon when it is
    active\. *Images* is a list of two Tk images: the first image is
    displayed when the node is open, the second when it is closed\.

\-autocreate *boolean*
:   If *boolean* is true, automatically create missing ancestor nodes
    when inserting new nodes\. Otherwise flag an error\.  The default
    is no\.  

\-allowduplicates *boolean*
:   If *boolean* is true, allow nodes with duplicate pathnames when
    inserting new nodes\.  Otherwise flag an error\.  The default is
    no\.  

\-background *color*
:   Sets the background color of the widget\.  The default is white\.

\-borderwidth *pixels*
:   Sets the width of the 3\-D border around the outside edge of the
    widget\.  The __\-relief__ option determines if the border is to be
    drawn\.  The default is 2\.  

\-closecommand *string*
:   Specifies a Tcl script to be invoked when a node is closed\.  You
    can overrider this for individual entries using the entry\'s
    __\-closecommand__ option\. The default is ""\.  Percent substitutions
    are performed on *string* before it is executed\.  The following
    substitutions are valid:  

    %W
    :   The pathname of the widget\.

    %p
    :   The name of the node\.

    %P
    :   The full pathname of the node\.

    %#
    :   The id of the node\.

    %%
    :   Translates to a single percent\.

\-cursor *cursor*
:   Specifies the widget\'s cursor\.  The default cursor is ""\.

\-dashes *number*
:   Sets the dash style of the horizontal and vertical lines drawn
    connecting entries\. *Number* is the length in pixels of the dashes
    and gaps in the line\. If *number* is 0, solid lines will be drawn\.
    The default is 1 (dotted)\.  

\-exportselection *boolean*
:   Indicates if the selection is exported\.  If the widget is
    exporting its selection then it will observe the standard X11
    protocols for handling the selection\.  Selections are available
    as type __STRING__; the value of the selection will be the label of
    the selected nodes, separated by newlines\.  The default is no\.

\-flat *boolean*
:   Indicates whether to display the tree as a flattened list\.  If
    *boolean* is true, then the hierarchy will be a list of full paths
    for the nodes\.  This option also has affect on sorting\.  See the
    __SORT OPERATIONS__ section for more information\.  The default is
    no\.  

\-focusdashes *dashList*
:   Sets the dash style of the outline rectangle drawn around the
    entry label of the node that current has focus\. *Number* is the
    length in pixels of the dashes and gaps in the line\.  If *number*
    is 0, a solid line will be drawn\. The default is 1\.

\-focusforeground *color*
:   Sets the color of the focus rectangle\.  The default is black\.

\-font *fontName*
:   Specifies the font for entry labels\.  You can override this for
    individual entries with the entry\'s __\-font__ configuration option\.
    The default is \*\-Helvetica\-Bold\-R\-Normal\-\*\-12\-120\-\*\.

\-foreground *color*
:   Sets the text color of entry labels\.  You can override this for
    individual entries with the entry\'s __\-foreground__ configuration
    option\.  The default is black\.  

\-height *pixels*
:   Specifies the requested height of widget\.  The default is 400\.

\-hideroot *boolean*
:   If *boolean* is true, it indicates that no entry for the root node
    should be displayed\.  The default is no\.  

\-highlightbackground  *color*
:   Specifies the normal color of the traversal highlight region
    when the widget does not have the input focus\.

\-highlightcolor *color*
:   Specifies the color of the traversal highlight rectangle when
    the widget has the input focus\.  The default is black\.

\-highlightthickness *pixels*
:   Specifies the width of the highlight rectangle indicating when
    the widget has input focus\. The value may have any of the forms
    acceptable to __Tk\_GetPixels__\.  If the value is zero, no focus
    highlight will be displayed\.  The default is 2\.

\-icons *images*
:   Specifies images for the entry\'s icon\.  *Images* is a list of two
    Tk images: the first image is displayed when the node is open,
    the second when it is closed\.  

\-linecolor *color*
:   Sets the color of the connecting lines drawn between entries\.
    The default is black\.  

\-linespacing *pixels*
:   Sets the number of pixels spacing between entries\.  The default
    is 0\.  

\-linewidth *pixels*
:   Set the width of the lines drawn connecting entries\.  If *pixels*
    is 0, no vertical or horizontal lines are drawn\.  The default is
    1\.  

\-opencommand *string*
:   Specifies a Tcl script to be invoked when a node is open\.  You
    can override this for individual entries with the entry\'s
    __\-opencommand__ configuration option\.  The default is ""\.  Percent
    substitutions are performed on *string* before it is executed\.
    The following substitutions are valid:  

    %W
    :   The pathname of the widget\.

    %p
    :   The name of the node\.

    %P
    :   The full pathname of the node\.

    %#
    :   The id of the node\.

    %%
    :   Translates to a single percent\.

\-relief *relief*
:   Specifies the 3\-D effect for the widget\.  *Relief* specifies how
    the __treeview__ widget should appear relative to widget it is
    packed into; for example, raised means the __treeview__ widget
    should appear to protrude\.  The default is sunken\.

\-scrollmode *mode*
:   Specifies the style of scrolling to be used\.  The following
    styles are valid\.  This is the default is hierbox\.

    listbox
    :   Like the __listbox__ widget, the last entry can always
        be scrolled to the top of the widget window\.  This
        allows the scrollbar thumb to shrink as the last
        entry is scrolled upward\.  

    hierbox
    :   Like the __hierbox__ widget, the last entry can only be
        viewed at the bottom of the widget window\.  The
        scrollbar stays a constant size\.  

    canvas
    :   Like the __canvas__ widget, the entries are bound within
        the scrolling area\.  

\-selectbackground *color*
:   Sets the background color selected node entries\.  The default is
    #ffffea\.  

\-selectborderwidth *pixels*
:   Sets the width of the raised 3\-D border drawn around the labels
    of selected entries\. The default is 0\.  __\-selectcommand__ *string*
    Specifies a Tcl script to invoked when the set of selected nodes
    changes\.  The default is ""\.  

\-selectforeground *color*
:   Sets the color of the labels of selected node entries\.  The
    default is black\.  

\-selectmode *mode*
:   Specifies the selection mode\. If *mode* is single, only one node
    can be selected at a time\.  If multiple more than one node can
    be selected\.  The default is single\.  

\-separator *string*
:   Specifies the character sequence to use when spliting the path
    components\.  The separator may be several characters wide (such
    as "::") Consecutive separators in a pathname are treated as
    one\.  If *string* is the empty string, the pathnames are Tcl
    lists\.  Each element is a path component\.   The default is ""\.

\-showtitles *boolean*
:   If *boolean* is false, column titles are not be displayed\.  The
    default is yes\.  

\-sortselection *boolean*
:   If *boolean* is true, nodes in the selection are ordered as they
    are currently displayed (depth\-first or sorted), not in the
    order they were selected\. The default is no\.  

\-takefocus *focus*
:   Provides information used when moving the focus from window to
    window via keyboard traversal (e\.g\., Tab and Shift\-Tab)\.  If
    *focus* is 0, this means that this window should be skipped
    entirely during keyboard traversal\.  1 means that the this
    window should always receive the input focus\.  An empty value
    means that the traversal scripts make the decision whether to
    focus on the window\.  The default is "1"\.  

\-trim *string*
:   Specifies a string leading characters to trim from entry
    pathnames before parsing\.  This only makes sense if the
    __\-separator__ is also set\.  The default is ""\.  

\-width *pixels*
:   Sets the requested width of the widget\.  If *pixels* is 0, then
    the with is computed from the contents of the __treeview__ widget\.
    The default is 200\.  

\-xscrollcommand *string*
:   Specifies the prefix for a command used to communicate with
    horizontal scrollbars\.  Whenever the horizontal view in the
    widget\'s window changes, the widget will generate a Tcl command
    by concatenating the scroll command and two numbers\.  If this
    option is not specified, then no command will be executed\.

\-xscrollincrement *pixels*
:   Sets the horizontal scrolling distance\. The default is 20
    pixels\.  

\-yscrollcommand *string*
:   Specifies the prefix for a command used to communicate with
    vertical scrollbars\.   Whenever the vertical view in the
    widget\'s window changes, the widget will generate a Tcl command
    by concatenating the scroll command and two numbers\.  If this
    option is not specified, then no command will be executed\.

\-yscrollincrement *pixels*
:   Sets the vertical scrolling distance\. The default is 20 pixels\.

ENTRY OPTIONS
=============

Many widget configuration options have counterparts in entries\.  For
example, there is a __\-closecommand__ configuration option for both widget
itself and for individual entries\.  Options set at the widget level are
global for all entries\.  If the entry configuration option is set, then
it overrides the widget option\.  This is done to avoid wasting memory
by replicated options\.  Most entries will have redundant options\.

There is no resource class or name for entries\.  

\-activeicons *images*
:   Specifies images to be displayed as the entry\'s icon when it is
    active\. This overrides the global __\-activeicons__ configuration
    option for the specific entry\.  *Images* is a list of two Tk
    images: the first image is displayed when the node is open, the
    second when it is closed\.  

\-bindtags *tagList*
:   Specifies the binding tags for nodes\.  *TagList* is a list of
    binding tag names\.  The tags and their order will determine how
    events are handled for nodes\.  Each tag in the list matching the
    current event sequence will have its Tcl command executed\.  The
    default value is all\.  

\-button *string*
:   Indicates whether a button should be displayed on the left side
    of the node entry\.  *String* can be yes, no, or auto\.  If auto,
    then a button is automatically displayed if the node has
    children\.  This is the default\.  

\-closecommand *string*
:   Specifies a Tcl script to be invoked when the node is closed\.
    This overrides the global __\-closecommand__ option for this entry\.
    The default is ""\.  Percent substitutions are performed on
    *string* before it is executed\.  The following substitutions are
    valid:  

    %W
    :   The pathname of the widget\.

    %p
    :   The name of the node\.

    %P
    :   The full pathname of the node\.

    %#
    :   The id of the node\.

    %%
    :   Translates to a single percent\.

\-data *string*
:   Sets data fields for the node\.  *String* is a list of name\-value
    pairs to be set\. The default is ""\.  

\-font *fontName*
:   Sets the font for entry labels\.  This overrides the widget\'s
    __\-font__ option for this node\.  The default is \*\-Helvetica\-Bold\-R\-
    Normal\-\*\-12\-120\-\*\.  

\-foreground *color*
:   Sets the text color of the entry label\.  This overrides the
    widget\'s __\-foreground__ configuration option\.  The default is ""\.

\-icons *images*
:   Specifies images to be displayed for the entry\'s icon\.  This
    overrides the global __\-icons__ configuration option\.  *Images* is a
    list of two Tk images: the first image is displayed when the
    node is open, the second when it is closed\.  

\-label *string*
:   Sets the text for the entry\'s label\.  If not set, this defaults
    to the name of the node\. The default is ""\.  

\-opencommand *string*
:   Specifies a Tcl script to be invoked when the entry is opened\.
    This overrides the widget\'s __\-opencommand__ option for this node\.
    The default is ""\.  Percent substitutions are performed on
    *string* before it is executed\.  The following substitutions are
    valid:  

    %W
    :   The pathname of the widget\.

    %p
    :   The name of the node\.

    %P
    :   The full pathname of the node\.

    %#
    :   The id of the node\.

    %%
    :   Translates to a single percent\.

BUTTON OPTIONS
==============

Button configuration options may also be set by the __option__ command\.
The resource subclass is Button\.   The resource name is always button\.

~~~~~
option add *TreeView.Button.Foreground white
option add *TreeView.button.Background blue
~~~~~

The following are the configuration options available for buttons\.

\-activebackground *color*
:   Sets the background color of active buttons\.  A button is made
    active when the mouse passes over it or by the __button activate__
    operation\.  

\-activeforeground *color*
:   Sets the foreground color of active buttons\.  A button is made
    active when the mouse passes over it or by the __button activate__
    operation\.  

\-background *color*
:   Sets the background of the button\.  The default is white\.

\-borderwidth *pixels*
:   Sets the width of the 3\-D border around the button\.  The __\-relief__
    option determines if a border is to be drawn\.  The default is 1\.

\-closerelief *relief*
:   Specifies the 3\-D effect for the closed button\.  *Relief*
    indicates how the button should appear relative to the widget;
    for example, raised means the button should appear to protrude\.
    The default is solid\.  

\-cursor *cursor*
:   Sets the widget\'s cursor\.  The default cursor is ""\.

\-foreground *color*
:   Sets the foreground color of buttons\.  The default is black\.

\-images *images*
:   Specifies images to be displayed for the button\.  *Images* is a
    list of two Tk images: the first image is displayed when the
    button is open, the second when it is closed\.  If the *images* is
    the empty string, then a plus/minus gadget is drawn\.  The
    default is ""\.  

\-openrelief *relief*
:   Specifies the 3\-D effect of the open button\.  *Relief* indicates
    how the button should appear relative to the widget; for
    example, raised means the button should appear to protrude\.  The
    default is flat\.  

\-size *pixels*
:   Sets the requested size of the button\.  The default is 0\.

COLUMN OPTIONS
==============

Column configuration options may also be set by the __option__ command\.
The resource subclass is Column\.   The resource name is the name of the
column\.  

~~~~~
option add *TreeView.Column.Foreground white
option add *TreeView.treeView.Background blue
~~~~~

The following configuration options are available for columns\.

\-background *color*
:   Sets the background color of the column\.  This overrides the
    widget\'s __\-background__ option\. The default is white\.

\-borderwidth *pixels*
:   Sets the width of the 3\-D border of the column\.  The __\-relief__
    option determines if a border is to be drawn\.  The default is 0\.

\-edit *boolean*
:   Indicates if the column\'s data fields can be edited\. If *boolean*
    is false, the data fields in the column may not be edited\.  The
    default is yes\.  

\-foreground *color*
:   Specifies the foreground color of the column\.  You can override
    this for individual entries with the entry\'s __\-foreground__ option\.
    The default is black\.  

\-font *fontName*
:   Sets the font for a column\.  You can override this for
    individual entries with the entry\'s __\-font__ option\.  The default
    is \*\-Helvetica\-Bold\-R\-Normal\-\*\-12\-120\-\*\.  

\-hide *boolean*
:   If *boolean* is true, the column is not displayed\.  The default is
    yes\.  

\-justify *justify*
:   Specifies how the column data fields title should be justified
    within the column\.  This matters only when the column is wider
    than the data field to be display\.  *Justify* must be left, right,
    or center\.  The default is left\.  

\-pad *pad*
:   Specifies how much padding for the left and right sides of the
    column\.  *Pad* is a list of one or two screen distances\.  If *pad*
    has two elements, the left side of the column is padded by the
    first distance and the right side by the second\.  If *pad* has
    just one distance, both the left and right sides are padded
    evenly\.  The default is 2\.  

\-relief *relief*
:   Specifies the 3\-D effect of the column\.  *Relief* specifies how
    the column should appear relative to the widget; for example,
    raised means the column should appear to protrude\.  The default
    is flat\.  

\-state *state*
:   Sets the state of the column\. If *state* is disable then the
    column title can not be activated nor invoked\.  The default is
    normal\.  

\-text *string*
:   Sets the title for the column\.  The default is ""\.

\-titleforeground *color*
:   Sets the foreground color of the column title\.  The default is
    black\.  

\-titleshadow *color*
:   Sets the color of the drop shadow of the column title\.  The
    default is ""\.  

\-width *pixels*
:   Sets the requested width of the column\.  This overrides the
    computed with of the column\.  If *pixels* is 0, the width is
    computed as from the contents of the column\. The default is 0\.

TEXT EDITING OPTIONS
====================

Text edit window configuration options may also be set by the __option__
command\. The resource class is TreeViewEditor\.  The resource name is
always edit\.  

~~~~~
option add *TreeViewEditor.Foreground white
option add *edit.Background blue
~~~~~

The following are the configuration options available for the text
editing window\.  

\-background *color*
:   Sets the background of the text edit window\.  The default is
    white\.  

\-borderwidth *pixels*
:   Sets the width of the 3\-D border around the edit window\.  The
    __\-relief__ option determines if a border is to be drawn\.  The
    default is 1\.  

\-exportselection *boolean*
:   Indicates if the text selection is exported\.  If the edit window
    is exporting its selection then it will observe the standard X11
    protocols for handling the selection\.  Selections are available
    as type __STRING__\.  The default is no\.  

\-relief *relief*
:   Specifies the 3\-D effect of the edit window\.  *Relief* indicates
    how the background should appear relative to the edit window;
    for example, raised means the background should appear to
    protrude\.  The default is solid\.  

\-selectbackground *color*
:   Sets the background of the selected text in the edit window\.
    The default is white\.  

\-selectborderwidth *pixels*
:   Sets the width of the 3\-D border around the selected text in the
    edit window\.  The __\-selectrelief__ option determines if a border is
    to be drawn\.  The default is 1\.  

\-selectforeground *color*
:   Sets the foreground of the selected text in the edit window\.
    The default is white\.  

\-selectrelief *relief*
:   Specifies the 3\-D effect of the selected text in the edit
    window\.  *Relief* indicates how the text should appear relative to
    the edit window; for example, raised means the text should
    appear to protrude\.  The default is flat\.  

DEFAULT BINDINGS
================

Tk automatically creates class bindings for treeviews that give them
Motif\-like behavior\.  Much of the behavior of a __treeview__ widget is
determined by its __\-selectmode__ option, which selects one of two ways of
dealing with the selection\.  

If the selection mode is __single__, only one node can be selected at a
time\.  Clicking button 1 on an node selects it and deselects any other
selected item\.  

If the selection mode is __multiple__, any number of entries may be
selected at once, including discontiguous ranges\.  Clicking Control\-
Button\-1 on a node entry toggles its selection state without affecting
any other entries\.  Pressing Shift\-Button\-1 on a node entry selects it,
extends the selection\.  

\[1\]
:   In __extended__ mode, the selected range can be adjusted by pressing
    button 1 with the Shift key down:  this modifies the selection
    to consist of the entries between the anchor and the entry under
    the mouse, inclusive\.  The un\-anchored end of this new selection
    can also be dragged with the button down\.  

\[2\]
:   In __extended__ mode, pressing button 1 with the Control key down
    starts a toggle operation: the anchor is set to the entry under
    the mouse, and its selection state is reversed\.  The selection
    state of other entries isn\'t changed\.  If the mouse is dragged
    with button 1 down, then the selection state of all entries
    between the anchor and the entry under the mouse is set to match
    that of the anchor entry;  the selection state of all other
    entries remains what it was before the toggle operation began\.

\[3\]
:   If the mouse leaves the treeview window with button 1 down, the
    window scrolls away from the mouse, making information visible
    that used to be off\-screen on the side of the mouse\.  The
    scrolling continues until the mouse re\-enters the window, the
    button is released, or the end of the hierarchy is reached\.

\[4\]
:   Mouse button 2 may be used for scanning\.  If it is pressed and
    dragged over the __treeview__ widget, the contents of the hierarchy
    drag at high speed in the direction the mouse moves\.

\[5\]
:   If the Up or Down key is pressed, the location cursor (active
    entry) moves up or down one entry\.  If the selection mode is
    __browse__ or __extended__ then the new active entry is also selected
    and all other entries are deselected\.  In __extended__ mode the new
    active entry becomes the selection anchor\.  

\[6\]
:   In __extended__ mode, Shift\-Up and Shift\-Down move the location
    cursor (active entry) up or down one entry and also extend the
    selection to that entry in a fashion similar to dragging with
    mouse button 1\.  

\[7\]
:   The Left and Right keys scroll the __treeview__ widget view left and
    right by the width of the character __0__\.  Control\-Left and
    Control\-Right scroll the __treeview__ widget view left and right by
    the width of the window\.  Control\-Prior and Control\-Next also
    scroll left and right by the width of the window\.

\[8\]
:   The Prior and Next keys scroll the __treeview__ widget view up and
    down by one page (the height of the window)\.  

\[9\]
:   The Home and End keys scroll the __treeview__ widget horizontally to
    the left and right edges, respectively\.  

\[10\]
:   Control\-Home sets the location cursor to the the first entry,
    selects that entry, and deselects everything else in the widget\.

\[11\]
:   Control\-End sets the location cursor to the the last entry,
    selects that entry, and deselects everything else in the widget\.

\[12\]
:   In __extended__ mode, Control\-Shift\-Home extends the selection to
    the first entry and Control\-Shift\-End extends the selection to
    the last entry\.  

\[13\]
:   In __multiple__ mode, Control\-Shift\-Home moves the location cursor
    to the first entry and Control\-Shift\-End moves the location
    cursor to the last entry\.  

\[14\]
:   The space and Select keys make a selection at the location
    cursor (active entry) just as if mouse button 1 had been pressed
    over this entry\.  

\[15\]
:   In __extended__ mode, Control\-Shift\-space and Shift\-Select extend
    the selection to the active entry just as if button 1 had been
    pressed with the Shift key down\.  

\[16\]
:   In __extended__ mode, the Escape key cancels the most recent
    selection and restores all the entries in the selected range to
    their previous selection state\.  

\[17\]
:   Control\-slash selects everything in the widget, except in __single__
    and __browse__ modes, in which case it selects the active entry and
    deselects everything else\.  

\[18\]
:   Control\-backslash deselects everything in the widget, except in
    __browse__ mode where it has no effect\.  

\[19\]
:   The F16 key (labelled Copy on many Sun workstations) or Meta\-w
    copies the selection in the widget to the clipboard, if there is
    a selection\.  

The behavior of __treeview__ widgets can be changed by defining new
bindings for individual widgets or by redefining the class bindings\.

WIDGET BINDINGS
---------------

In addition to the above behavior, the following additional behavior is
defined by the default widget class (TreeView) bindings\.

\<ButtonPress\-2\>
:   Starts scanning\.

\<B2\-Motion\>
:   Adjusts the scan\.

\<ButtonRelease\-2\>
:   Stops scanning\.

\<B1\-Leave\>
:   Starts auto\-scrolling\.

\<B1\-Enter\>
:   Starts auto\-scrolling

\<KeyPress\-Up\>
:   Moves the focus to the previous entry\.

\<KeyPress\-Down\>
:   Moves the focus to the next entry\.

\<Shift\-KeyPress\-Up\>
:   Moves the focus to the previous sibling\.

\<Shift\-KeyPress\-Down\>
:   Moves the focus to the next sibling\.

\<KeyPress\-Prior\>
:   Moves the focus to first entry\.  Closed or hidden entries are
    ignored\.  

\<KeyPress\-Next\>
:   Move the focus to the last entry\. Closed or hidden entries are
    ignored\.  

\<KeyPress\-Left\>
:   Closes the entry\.  It is not an error if the entry has no
    children\.  

\<KeyPress\-Right\>
:   Opens the entry, displaying its children\.  It is not an error if
    the entry has no children\.  

\<KeyPress\-space\>
:   In "single" select mode this selects the entry\.  In "multiple"
    mode, it toggles the entry (if it was previous selected, it is
    not deselected)\.  

\<KeyRelease\-space\>
:   Turns off select mode\.

\<KeyPress\-Return\>
:   Sets the focus to the current entry\.

\<KeyRelease\-Return\>
:   Turns off select mode\.

\<KeyPress\>
:   Moves to the next entry whose label starts with the letter
    typed\.  

\<KeyPress\-Home\>
:   Moves the focus to first entry\.  Closed or hidden entries are
    ignored\.  

\<KeyPress\-End\>
:   Move the focus to the last entry\. Closed or hidden entries are
    ignored\.  

\<KeyPress\-F1\>
:   Opens all entries\.

\<KeyPress\-F2\>
:   Closes all entries (except root)\.

BUTTON BINDINGS
---------------

Buttons have bindings\.  There are associated with the "all" bindtag
(see the entry\'s \-bindtag option)\.  You can use the __bind__ operation to
change them\.  

\<Enter\>
:   Highlights the button of the current entry\.

\<Leave\>
:   Returns the button back to its normal state\.

\<ButtonRelease\-1\>
:   Adjust the view so that the current entry is visible\.

ENTRY BINDINGS
--------------

Entries have default bindings\.  There are associated with the "all"
bindtag (see the entry\'s \-bindtag option)\.  You can use the __bind__
operation to modify them\.  

\<Enter\>
:   Highlights the current entry\.

\<Leave\>
:   Returns the entry back to its normal state\.

\<ButtonPress\-1\>
:   Sets the selection anchor the current entry\.

\<Double\-ButtonPress\-1\>
:   Toggles the selection of the current entry\.

\<B1\-Motion\>
:   For "multiple" mode only\.  Saves the current location of the
    pointer for auto\-scrolling\.  Resets the selection mark\.

\<ButtonRelease\-1\>
:   For "multiple" mode only\.  Sets the selection anchor to the
    current entry\.  

\<Shift\-ButtonPress\-1\>
:   For "multiple" mode only\. Extends the selection\.

\<Shift\-Double\-ButtonPress\-1\>
:   Place holder\. Does nothing\.

\<Shift\-B1\-Motion\>
:   Place holder\. Does nothing\.

\<Shift\-ButtonRelease\-1\>
:   Stop auto\-scrolling\.

\<Control\-ButtonPress\-1\>
:   For "multiple" mode only\.  Toggles and extends the selection\.

\<Control\-Double\-ButtonPress\-1\>
:   Place holder\. Does nothing\.

\<Control\-B1\-Motion\>
:   Place holder\. Does nothing\.

\<Control\-ButtonRelease\-1\>
:   Stops auto\-scrolling\.

\<Control\-Shift\-ButtonPress\-1\>
:   ???

\<Control\-Shift\-Double\-ButtonPress\-1\>
:   Place holder\. Does nothing\.

\<Control\-Shift\-B1\-Motion\>
:   Place holder\. Does nothing\.

COLUMN BINDINGS
---------------

Columns have bindings too\.  They are associated with the column\'s "all"
bindtag (see the column \-bindtag option)\.  You can use the __column bind__
operation to change them\.  

\<Enter\>
:   Highlights the current column title\.

\<Leave\>
:   Returns the column back to its normal state\.

\<ButtonRelease\-1\>
:   Invokes the command (see the column\'s \-command option) if one if
    specified\.  

COLUMN RULE BINDINGS
--------------------


\<Enter\>
:   Highlights the current and activates the ruler\.

\<Leave\>
:   Returns the column back to its normal state\. Deactivates the
    ruler\.  

\<ButtonPress\-1\>
:   Sets the resize anchor for the column\.

\<B1\-Motion\>
:   Sets the resize mark for the column\.

\<ButtonRelease\-1\>
:   Adjust the size of the column, based upon the resize anchor and
    mark positions\.  

EXAMPLE
=======

The __treeview__ command creates a new widget\.  

~~~~~
treeview .h -bg white
~~~~~

A new Tcl command \.h is also created\.  This command can be used to
query and modify the __treeview__ widget\.  For example, to change the
background color of the table to "green", you use the new command and
the widget\'s __configure__ operation\.  

~~~~~
# Change the background color.
.h configure -background "green"
~~~~~

By default, the __treeview__ widget will automatically create a new tree
object to contain the data\.  The name of the new tree is the pathname
of the widget\.  Above, the new tree object name is "\.h"\.  But you can
use the __\-tree__ option to specify the name of another tree\.

~~~~~
# View the tree "myTree".
.h configure -tree "myTree"
~~~~~

When a new tree is created, it contains only a root node\.  The node is
automatically opened\.  The id of the root node is always 0 (you can use
also use the special id root)\. The __insert__ operation lets you insert one
or more new entries into the tree\.  The last argument is the node\'s
*pathname*\.  

~~~~~
# Create a new entry named "myEntry"
set id [.h insert end "myEntry"]
~~~~~

This appends a new node named "myEntry"\.  It will positioned as the
last child of the root of the tree (using the position "end")\.  You can
supply another position to order the node within its siblings\.

~~~~~
# Prepend "fred".
set id [.h insert 0 "fred"]
~~~~~

Entry names do not need to be unique\.  By default, the node\'s label is
its name\.  To supply a different text label, add the __\-label__ option\.

~~~~~
# Create a new node named "fred"
set id [.h insert end "fred" -label "Fred Flintstone"]
~~~~~

The __insert__ operation returns the id of the new node\.  You can also use
the __index__ operation to get this information\.  

~~~~~
# Get the id of "fred"
.h index "fred"
~~~~~

To insert a node somewhere other than root, use the __\-at__ switch\.  It
takes the id of the node where the new child will be added\.

~~~~~
# Create a new node "barney" in "fred".
.h insert -at $id end "barney"
~~~~~

A pathname describes the path to an entry in the hierarchy\.  It\'s a
list of entry names that compose the path in the tree\.  Therefore, you
can also add "barney" to "fred" as follows\.  

~~~~~
# Create a new sub-entry of "fred"
.h insert end "fred barney"
~~~~~

Every name in the list is ancestor of the next\.  All ancestors must
already exist\.  That means that an entry "fred" is an ancestor of
"barney" and must already exist\.  But you can use the __\-autocreate__
configuration option to force the creation of ancestor nodes\.

~~~~~
# Force the creation of ancestors.
.h configure -autocreate yes
.h insert end "fred barney wilma betty"
~~~~~

Sometimes the pathname is already separated by a character sequence
rather than formed as a list\.  A file name is a good example of this\.
You can use the __\-separator__ option to specify a separator string to
split the path into its components\.  Each pathname inserted is
automatically split using the separator string as a separator\.
Multiple separators are treated as one\.  

~~~~~
.h configure -separator /
.h insert end "/usr/local/tcl/bin"
~~~~~

If the path is prefixed by extraneous characters, you can automatically
trim it off using the __\-trim__ option\.  It removed the string from the
path before it is parsed\.  

~~~~~
.h configure -trim C:/windows -separator /
.h insert end "C:/window/system"
~~~~~

You can insert more than one entry at a time with the __insert__ operation\.
This can be much faster than looping over a list of names\.

~~~~~
# The slow way
foreach f [glob $dir/*] {
    .h insert end $f
}
# The fast way
eval .h insert end [glob $dir/*]
~~~~~

In this case, the __insert__ operation will return a list of ids of the new
entries\.  

You can delete entries with the __delete__ operation\.  It takes one or more
tags of ids as its argument\. It deletes the entry and all its children\.

~~~~~
.h delete $id
~~~~~

Entries have several configuration options\.  They control the
appearance of the entry\'s icon and label\.  We have already seen the
__\-label__ option that sets the entry\'s text label\.   The __entry configure__
operation lets you set or modify an entry\'s configuration options\.

~~~~~
.h entry configure $id -color red -font fixed
~~~~~

You can hide an entry and its children using the __\-hide__ option\.

~~~~~
.h entry configure $id -hide yes
~~~~~

More that one entry can be configured at once\.  All entries specified
are configured with the same options\.  

~~~~~
.h entry configure $i1 $i2 $i3 $i4 -color brown
~~~~~

An icon is displayed for each entry\.  It\'s a Tk image drawn to the left
of the label\.  You can set the icon with the entry\'s __\-icons__ option\.  It
takes a list of two image names: one to represent the open entry,
another when it is closed\.  

~~~~~
set im1 [image create photo -file openfolder.gif]
set im2 [image create photo -file closefolder.gif]
.h entry configure $id -icons "$im1 $im2"
~~~~~

If __\-icons__ is set to the empty string, no icons are display\.

If an entry has children, a button is displayed to the left of the
icon\. Clicking the mouse on this button opens or closes the sub\-
hierarchy\.  The button is normally a + or \- symbol, but can be
configured in a variety of ways using the __button configure__ operation\.
For example, the + and \- symbols can be replaced with Tk images\.

~~~~~
set im1 [image create photo -file closefolder.gif]
set im2 [image create photo -file downarrow.gif]
.h button configure $id -images "$im1 $im2" \
    -openrelief raised -closerelief raised
~~~~~

Entries can contain an arbitrary number of *data* *fields*\.  Data fields
are name\-value pairs\.  Both the value and name are strings\.  The
entry\'s __\-data__ option lets you set data fields\.  

~~~~~
.h entry configure $id -data {mode 0666 group users}
~~~~~

The __\-data__ takes a list of name\-value pairs\.  

You can display these data fields as *columns* in the __treeview__ widget\.
You can create and configure columns with the __column__ operation\.  For
example, to add a new column to the widget, use the __column insert__
operation\.  The last argument is the name of the data field that you
want to display\.  

~~~~~
.h column insert end "mode"
~~~~~

The column title is displayed at the top of the column\.  By default,
it\'s is the field name\.  You can override this using the column\'s __\-text__
option\.  

~~~~~
.h column insert end "mode" -text "File Permissions"
~~~~~

Columns have several configuration options\.  The __column configure__
operation lets you query or modify column options\.  

~~~~~
.h column configure "mode" -justify left
~~~~~

The __\-justify__ option says how the data is justified within in the
column\.  The __\-hide__ option indicates whether the column is displayed\.

~~~~~
.h column configure "mode" -hide yes
~~~~~

Entries can be selected by clicking on the mouse\.  Selected entries are
drawn using the colors specified by the __\-selectforeground__ and
__\-selectbackground__ configuration options\.  The selection itself is
managed by the __selection__ operation\.  

~~~~~
# Clear all selections
.h selection clear 0 end
# Select the root node
.h selection set 0
~~~~~

The __curselection__ operation returns a list of ids of all the selected
entries\.  

~~~~~
set ids [.h curselection]
~~~~~

You can use the __get__ operation to convert the ids to their pathnames\.

~~~~~
set names [eval .h get -full $ids]
~~~~~

If a treeview is exporting its selection (using the __\-exportselection__
option), then it will observe the standard X11 protocols for handling
the selection\.  Treeview selections are available as type __STRING__; the
value of the selection will be the pathnames of the selected entries,
separated by newlines\.  

The __treeview__ supports two modes of selection: single and multiple\.  In
single select mode, only one entry can be selected at a time, while
multiple select mode allows several entries to be selected\.  The mode
is set by the widget\'s __\-selectmode__ option\.  

~~~~~
.h configure -selectmode "multiple"
~~~~~

You can be notified when the list of selected entries changes\.  The
widget\'s __\-selectcommand__ specifies a Tcl procedure that is called
whenever the selection changes\.  

~~~~~
proc SelectNotify { widget } {
   set ids [$widget curselection]
}
.h configure -selectcommand "SelectNotify .h"
~~~~~

The widget supports the standard Tk scrolling and scanning operations\.
The __treeview__ can be both horizontally and vertically\. You can attach
scrollbars to the __treeview__ the same way as the listbox or canvas
widgets\.  

~~~~~
scrollbar .xbar -orient horizontal -command ".h xview"
scrollbar .ybar -orient vertical -command ".h yview"
.h configure -xscrollcommand ".xbar set" \
    -yscrollcommand ".ybar set"
~~~~~

There are three different modes of scrolling: listbox, canvas, and
hierbox\.  In listbox mode, the last entry can always be scrolled to the
top of the widget\.  In hierbox mode, the last entry is always drawn at
the bottom of the widget\.  The scroll mode is set by the widget\'s
__\-selectmode__ option\.  

~~~~~
.h configure -scrollmode "listbox"
~~~~~

Entries can be programmatically opened or closed using the __open__ and
__close__ operations respectively\.  

~~~~~
.h open $id
.h close $id
~~~~~

When an entry is opened, a Tcl procedure can be automatically invoked\.
The __\-opencommand__ option specifies this procedure\.  This procedure can
lazily insert entries as needed\.  

~~~~~
proc AddEntries { dir } {
   eval .h insert end [glob -nocomplain $dir/*]
}
.h configure -opencommand "AddEntries %P"
~~~~~

Now when an entry is opened, the procedure AddEntries is called and
adds children to the entry\.  Before the command is invoked, special "%"
substitutions (like __bind__) are performed\. Above, %P is translated to the
pathname of the entry\.  

The same feature exists when an entry is closed\.  The __\-closecommand__
option specifies the procedure\.  

~~~~~
proc DeleteEntries { id } {
   .h entry delete $id 0 end
}
.h configure -closecommand "DeleteEntries %#"
~~~~~

When an entry is closed, the procedure DeleteEntries is called and
deletes the entry\'s children using the __entry delete__ operation (%# is
the id of entry)\.  

KEYWORDS
========

treeview, widget  

