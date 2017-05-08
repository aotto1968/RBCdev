

NAME
====

busy \- Make Tk widgets busy, temporarily blocking user interactions\.

SYNOPSIS
========

__busy hold__ *window* ?*option* *value*?\.\.\.  

__busy release__ *window* ?*window*?\.\.\.  

__busy configure__ *window* ?*option* *value*?\.\.\.  

__busy forget__ *window* ?*window*?\.\.\.  

__busy isbusy__ ?*pattern*?  

__busy names__ ?*pattern*?  

__busy status__ *window*  

DESCRIPTION
===========

The __busy__ command provides a simple means to block keyboard, button, and
pointer events from Tk widgets, while overriding the widget\'s cursor
with a configurable busy cursor\.  

INTRODUCTION
============

There are many times in applications where you want to temporarily
restrict what actions the user can take\.  For example, an application
could have a "run" button that when pressed causes some processing to
occur\.  But while the application is busy processing, you probably
don\'t want the the user to be able to click the "run" button again\.
You may also want restrict the user from other tasks such as clicking a
"print" button\.  

The __busy__ command lets you make Tk widgets busy\. This means that user
interactions such as button clicks, moving the mouse, typing at the
keyboard, etc\. are ignored by the widget\.  You can set a special cursor
(like a watch) that overrides the widget\'s normal cursor, providing
feedback that the application (widget) is temporarily busy\.

When a widget is made busy, the widget and all of its descendents will
ignore events\.  It\'s easy to make an entire panel of widgets busy\. You
can simply make the toplevel widget (such as "\.") busy\.  This is easier
and far much more efficient than recursively traversing the widget
hierarchy, disabling each widget and re\-configuring its cursor\.

Often, the busy command can be used instead of Tk\'s __grab__ command\.
Unlike __grab__ which restricts all user interactions to one widget, with
the busy command you can have more than one widget active (for example,
a "cancel" dialog and a "help" button)\.  

EXAMPLE
=======

You can make several widgets busy by simply making its ancestor widget
busy using the __hold__ operation\.  

~~~~~
frame .top
button .top.button; canvas .top.canvas
pack .top.button .top.canvas
pack .top
  . . .
busy hold .top
update
~~~~~

All the widgets within \.top (including \.top) are now busy\.  Using
__update__ insures that __busy__ command will take effect before any other user
events can occur\.  

When the application is no longer busy processing, you can allow user
interactions again by the __release__ operation\.  

busy release \.top  

The busy window has a configurable cursor\.  You can change the busy
cursor using the __configure__ operation\.  

busy configure \.top \-cursor "watch"  

Finally, when you no longer need to the busy window, invoke the __forget__
operation to free any resources it allocated\.  

busy forget \.top  

Destroying the widget will also clean up any resources allocated by the
busy command\.  

OPERATIONS
==========

The following operations are available for the __busy__ command:

__busy hold__ *window* ?*option* *value*?\.\.\.

:   Makes the widget *window* (and its descendants in the Tk window
    hierarchy) busy\.  *Window* must be a valid path name of a Tk
    widget\.  The busy window is mapped the next time idle tasks are
    processed, and the widget and its descendants will be blocked
    from user interactions\. All events in the widget window and its
    descendants are ignored\.  Normally __update__ should be called
    immediately afterward to insure that the __hold__ operation is in
    effect *before* the application starts its processing\. The
    following configuration options are valid:  

    \-cursor *cursorName*
    :   Specifies the cursor to be displayed when the widget is
        made busy\.  *CursorName* can be in any form accepted by
        __Tk\_GetCursor__\.  The default cursor is watch\.

__busy configure__ *window* ?*option* *value*?\.\.\.

:   Queries or modifies the __busy__ command configuration options for
    *window*\. *Window* must be the path name of a widget previously made
    busy by the __hold__ operation\.  If no options are specified, a list
    describing all of the available options for *window* (see
    __Tk\_ConfigureInfo__ for information on the format of this list) is
    returned\.  If *option* is specified with no *value*, then the
    command returns a list describing the one named option (this
    list will be identical to the corresponding sublist of the value
    returned if no *option* is specified)\.  If one or more
    *option\-value* pairs are specified, then the command modifies the
    given widget option(s) to have the given value(s); in this case
    the command returns the empty string\.  *Option* may have any of
    the values accepted by the __hold__ operation\.  

    Please note that the option database is referenced through
    *window*\.  For example, if the widget \.frame is to be made busy,
    the busy cursor can be specified for it by either __option__
    command:  

    option add \*frame\.busyCursor gumby  
    option add \*Frame\.BusyCursor gumby  

__busy forget__ *window* ?*window*?\.\.\.

:   Releases resources allocated by the busy command for *window*,
    including the busy window\.  User events will again be received
    again by *window*\.  Resources are also released when *window* is
    destroyed\. *Window* must be the name of a widget specified in the
    __hold__ operation, otherwise an error is reported\.

__busy isbusy__ ?*pattern*?

:   Returns the pathnames of all widgets that are currently busy\.
    If a *pattern* is given, the path names of busy widgets matching
    *pattern* are returned\.  

__busy names__ ?*pattern*?

:   Returns the pathnames of all widgets that have previously been
    made busy (i\.e\. a busy window is allocated and associated with
    the widget)\.  It makes no difference if the window is currently
    busy or not\.  If a *pattern* is given, the path names of busy
    widgets matching *pattern* are returned\.  

__busy release__ *window* ?*window*?\.\.\.

:   Restores user interactions to the widget *window* again\.  This
    differs from the __forget__ operation in that the busy window is not
    destroyed, but simply unmapped\.  *Window* must be the name of a
    widget specified in a __hold__ operation, otherwise an error is
    reported\.  

__busy status__ *window*

:   Returns the status of a widget *window* previously made busy\.  An
    error is reported if *window* was never made busy, or the __forget__
    operation was invoked (i\.e\. does not currently have a busy
    window associated with it)\.  If *window* is presently can not
    receive user interactions, 1 is returned, otherwise 0\.

BINDINGS
========

The event blocking feature is implemented by creating and mapping a
transparent window that completely covers the widget\.  When the busy
window is mapped, it invisibly shields the widget and its hierarchy
from all events that may be sent\.  Like Tk widgets, busy windows have
widget names in the Tk window hierarchy\.  This means that you can use
the __bind__ command, to handle events in the busy window\.

~~~~~
busy hold .frame.canvas
bind .frame.canvas_Busy <Enter> { ... }
~~~~~

Normally the busy window is a sibling of the widget\.  The name of the
busy window is "*widget\_Busy*" where *widget* is the name of the widget to
be made busy\.  In the previous example, the pathname of the busy window
is "\.frame\.canvas\_Busy" The exception is when the widget is a toplevel
widget (such as "\.")  where the busy window can\'t be made a sibling\.
The busy window is then a child of the widget named "*widget\.\_Busy*"
where *widget* is the name of the toplevel widget\.  In the following
example, the pathname of the busy window is "\.\_Busy"  

~~~~~
busy hold .
bind ._Busy <Enter> { ... }
~~~~~

ENTER/LEAVE EVENTS
==================

Mapping and unmapping busy windows generates Enter/Leave events for all
widgets they cover\.  Please note this if you are tracking Enter/Leave
events in widgets\.  

KEYBOARD EVENTS
===============

When a widget is made busy, the widget is prevented from gaining the
keyboard focus by the busy window\. But if the widget already had focus,
it still may received keyboard events\.  To prevent this, you must move
focus to another window\.  

~~~~~
busy hold .frame
label .dummy
focus .dummy
update
~~~~~

The above example moves the focus from \.frame immediately after
invoking the __hold__ so that no keyboard events will be sent to \.frame or
any of its descendants\.  

KEYWORDS
========

busy, keyboard events, pointer events, window, cursor

