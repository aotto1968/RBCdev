

NAME
====

tabset \- Create and manipulate tabset widgets  

SYNOPSIS
========

__tabset__ *pathName* ?*options*?  

DESCRIPTION
===========

The __tabset__ widget displays a series of overlapping folders\. Only the
contents of one folder at a time is displayed\.  By clicking on the
tab\'s of a folder, you can view other folders\.  Each folder may contain
any Tk widget that can be automatically positioned and resized in the
folder\.  

There\'s no limit to the number of folders\.  Tabs can be tiered or
scrolled\.  Pages (i\.e\. embedded widgets) can be torn off and displayed
in another toplevel widget, and also restored\.  A tabset can also be
used as just a set of tabs, without a displaying any pages\.  You can
bind events to individual tabs, so it\'s easy to add features like
"balloon help"\.  

INTRODUCTION
============

Notebooks are a popular graphical paradigm\.  They allow you to organize
several windows that are too big to display at the same time as pages
of a notebook\.  For example, your application may display several X\-Y
graphs at the same time\.  The graphs are too big to pack into the same
frame\.  Managing them in several __toplevel__ widgets is also cumbersome
and clutters the screen\.  Instead, the __tabset__ widget organizes the
graphs as folders in a notebook\.  

Only one page is visible at a time\. When you click on a tab, the folder
corresponding to the tab is displayed in the  __tabset__ widget\.  The
tabset also lets you temporarily tear pages out of the notebook into a
separate toplevel widget, and put them back in the tabset later\.  For
example, you could compare two graphs side\-by\-side by tearing them out,
and then replace them when you are finished\.  

A tabset can contain any number of folders\.  If there are too many tabs
to view, you can arrange them as multiple tiers or scroll the tabs\. You
can also attach Tk scrollbars to the tabset to scroll the tabs\.

SYNTAX
======

The __tabset__ command creates a new window using the *pathName* argument and
makes it into a tabset widget\.  __tabset__ *pathName* ?*option* *value*?\.\.\.
Additional options may be specified on the command line or in the
option database to configure aspects of the tabset such as its colors,
font, text, and relief\.  The __tabset__ command returns its *pathName*
argument\.  At the time this command is invoked, there must not exist a
window named *pathName*, but *pathName*\'s parent must exist\.

When first created, a new tabset contains no tabs\.  Tabs are added or
deleted using widget operations described below\. It is not necessary
for all the tabs to be displayed in the tabset window at once; commands
described below may be used to change the view in the window\.  Tabsets
allow scrolling of tabs using the __\-scrollcommand__ option\.  They also
support scanning (see the __scan__ operation)\.  Tabs may be arranged along
any side of the tabset window using the __\-side__ option\.

The size of the tabset window is determined the number of tiers of tabs
and the sizes of the Tk widgets embedded inside each folder\.  The
widest widget determines the width of the folder\. The tallest
determines the height\.  If no folders contain an embedded widget, the
size is detemined solely by the size of the tabs\.  

You can override either dimension with the tabset\'s __\-width__ and __\-height__
options\.  

INDICES
=======

Indices refer to individual tabs/folders in the tabset\.  Many of the
operations for tabset widgets take one or more indices as arguments\.
An index may take several forms:  

*number*
:   Unique node id of the tab\.

\@*x*,*y*
:   Tab that covers the point in the tabset window specified by
    *x* and *y* (in screen coordinates)\.  If no tab covers that
    point, then the index is ignored\.  

select
:   The currently selected tab\.  The __select__ index is typically
    changed by either clicking on the tab with the left mouse
    button or using the widget\'s __invoke__ operation\.

active
:   The tab where the mouse pointer is currently located\.  The
    label is drawn using its active colors (see the
    __\-activebackground__ and __\-activeforeground__ options)\.  The
    __active__ index is typically changed by moving the mouse
    pointer over a tab or using the widget\'s __activate__
    operation\. There can be only one active tab at a time\.  If
    there is no tab located under the mouse pointer, the index
    is ignored\.  

focus
:   Tab that currently has the widget\'s focus\.  This tab is
    displayed with a dashed line around its label\.  You can
    change this using the __focus__ operation\. If no tab has focus,
    then the index is ignored\.  

down
:   Tab immediately below the tab that currently has focus, if
    there is one\. If there is no tab below, the current tab is
    returned\.  

left
:   Tab immediately to the left the tab that currently has
    focus, if there is one\.  If there is no tab to the left,
    the current tab is returned\.  

right
:   Tab immediately to the right the tab that currently has
    focus, if there is one\. If there is no tab to the right,
    the current tab is returned\.  

up
:   Tab immediately above, if there is one, to the tab that
    currently has focus\. If there is no tab above, the current
    tab is returned\.  

end
:   Last tab in the tabset\.  If there are no tabs in the tabset
    then the index is ignored\.  

Some indices may not always be available\.  For example, if the mouse is
not over any tab, "active" does not have an index\.  For most tabset
operations this is harmless and ignored\.  

OPERATIONS
==========

All __tabset__ operations are invoked by specifying the widget\'s pathname,
the operation, and any arguments that pertain to that operation\.  The
general form is:  

> *pathName* *operation* ?*arg* *arg* *\.\.\.*?  

*Operation* and the *arg*s determine the exact behavior of the command\.
The following operations are available for tabset widgets:

*pathName* __activate__ *index*

:   Sets the active tab to the one indicated by *index*\.  The active
    tab is drawn with its *active* colors (see the __\-activebackground__
    and __\-activeforeground__ options) and may be retrieved with the
    index __active__\.  Only one tab may be active at a time\.  If *index*
    is the empty string, then all tabs will be drawn with their
    normal foreground and background colors\.  

*pathName* __bind__ *tagName* ?*sequence*? ?*command*?

:   Associates *command* with *tagName* such that whenever the event
    sequence given by *sequence* occurs for a tab with this tag,
    *command* will be invoked\.  The syntax is similar to the __bind__
    command except that it operates on tabs, rather than widgets\.
    See the __bind__ manual entry for complete details on *sequence* and
    the substitutions performed on *command*\.  

    If all arguments are specified then a new binding is created,
    replacing any existing binding for the same *sequence* and
    *tagName*\.  If the first character of *command* is + then *command*
    augments an existing binding rather than replacing it\.  If no
    *command* argument is provided then the command currently
    associated with *tagName* and *sequence* (it\'s an error occurs if
    there\'s no such binding) is returned\.  If both *command* and
    *sequence* are missing then a list of all the event sequences for
    which bindings have been defined for *tagName*\.  

*pathName* __cget__ *option*

:   Returns the current value of the configuration option given by
    *option*\.  *Option* may have any of the values accepted by the
    __configure__ operation described in the section __WIDGET OPTIONS__
    below\.  

*pathName* __configure__ ?*option*? ?*value* *option* *value* *\.\.\.*?

:   Query or modify the configuration options of the widget\.  If no
    *option* is specified, returns a list describing all the available
    options for *pathName* (see __Tk\_ConfigureInfo__ for information on
    the format of this list)\.  If *option* is specified with no *value*,
    then the command returns a list describing the one named option
    (this list will be identical to the corresponding sublist of the
    value returned if no *option* is specified)\.  If one or more
    *option\-value* pairs are specified, then the command modifies the
    given widget option(s) to have the given value(s);  in this case
    the command returns an empty string\.  *Option* and *value* are
    described in the section __WIDGET OPTIONS__ below\.

*pathName* __delete__ *first* ?*last*?

:   Deletes one or more tabs from the tabset\.  *First* and *last* are
    the first and last indices, defining a range of tabs to be
    deleted\.  If *last* isn\'t specified, then only the tab at *first* is
    deleted\.  

*pathName* __focus__ *index*

:   Designates a tab to get the widget\'s focus\.  This tab is
    displayed with a dashed line around its label\.

*pathName* __get__ *index*

:   Returns the name of the tab\.  The value of *index* may be in any
    form described in the section __INDICES \.__  

*pathName* __index__ ?*flag*? *string*

:   Returns the node id of the tab specified by *string*\.  If *flag* is
    __\-name__, then *string* is the name of a tab\.  If *flag* is __\-index__,
    *string* is an index such as "active" or "focus"\.  If *flag* isn\'t
    specified, it defaults to __\-index__\.  

*pathName* __insert__ *position* *name* ?*option* *value*?\.\.\.

:   Inserts new tabs into the tabset\.  Tabs are inserted just before
    the tab given by *position*\.  *Position* may be either a number,
    indicating where in the list the new tab should be added, or
    __end__, indicating that the new tab is to be added the end of the
    list\.  *Name* is the symbolic name of the tab\. *Be* *careful* *not* *to*
    *use* *a* *number\.* *Otherwise* *the* *tabset* *will* *confuse* *it* *with* *tab*
    *indices*\.  Returns a list of indices for all the new tabs\.

*pathName* __invoke__ *index*

:   Selects the tab given by *index*, maps the tab\'s embedded widget,
    and invokes the Tcl command associated with the tab, if  there
    is  one\.  The return value is the return value from the Tcl
    command, or an empty string  if there  is  no  command
    associated with the tab\.  This command is ignored if the  tab\'s
    state (see the __\-state__ option) is disabled\.  

*pathName* __move__ *index* __before__|__after__ *index*

:   Moves the tab *index* to a new position in the tabset\.

*pathName* __nearest__ *x* *y*

:   Returns the name of the tab nearest to given X\-Y screen
    coordinate\.  

*pathName* __perforation__ *operation* ?*args*?

:   This operation controls the perforation on the tab label\.

    *pathName* __perforation highlight__ *index* *boolean*

    : …

    *pathName* __perforation invoke__ *index*

    :   Invokes the command specified for perforations (see the
        __\-perforationcommand__ widget option)\. Typically this
        command places the page into a top level widget\. The name
        of the toplevel is the concatonation of the *pathName*,
        "\-",  and the *tabName*\.  The return value is the return
        value from the Tcl command, or an empty string  if there
        is  no  command  associated with the tab\.  This command
        is ignored if the  tab\'s state (see the __\-state__ option) is
        disabled\.  

*pathName* __scan__ *option* *args*

:   This command implements scanning on tabsets\.  It has two forms,
    depending on *option*:  

    *pathName* __scan mark__ *x* *y*

    :   Records *x* and *y* and the current view in the tabset
        window;  used with later __scan dragto__ commands\.  Typically
        this command is associated with a mouse button press in
        the widget\.  It returns an empty string\.

    *pathName* __scan dragto__ *x* *y*\.

    :   This command computes the difference between its *x* and *y*
        arguments and the *x* and *y* arguments to the last __scan mark__
        command for the widget\.  It then adjusts the view by 10
        times the difference in coordinates\.  This command is
        typically associated with mouse motion events in the
        widget, to produce the effect of dragging the list at
        high speed through the window\.  The return value is an
        empty string\.  

*pathName* __see__ *index*

:   Scrolls the tabset so that the tab *index* is visible in the
    widget\'s window\.  

*pathName* __size__

:   Returns the number of tabs in the tabset\.

*pathName* __tab__ *operation* ?*args*?

: …

    *pathName* __tab cget__ *nameOrIndex* *option*

    :   Returns the current value of the configuration option
        given by *option*\.  *Option* may have any of the values
        accepted by the __tab configure__ operation described in the
        section __TAB OPTIONS__ below\.  

    *pathName* __tab configure__ *nameOrIndex* ?*nameOrIndex*\.\.\.? *option*? ?*value* *option* *value* *\.\.\.*?

    :   Query or modify the configuration options of one or more
        tabs\.  If no *option* is specified, this operation returns
        a list describing all the available options for
        *nameOrIndex*\.  *NameOrIndex* can be either the name of a tab
        or its index\.  Names of tabs take precedence over their
        indices\.  That means a tab named *focus* is picked over the
        "focus" tab\.  

        If *option* is specified, but not *value*, then a list
        describing the one named option is returned\.  If  one or
        more *option\-value* pairs are specified, then each named
        tab (specified by *nameOrIndex*) will have its
        configurations option(s) set the given value(s)\.  In this
        last case, the empty string is returned\.  *Option* and
        *value* are described in the section __TAB OPTIONS__ below\.

    *pathName* __tab names__ ?*pattern*?

    :   Returns the names of all the tabs matching the given
        pattern\. If no *pattern* argument is provided, then all tab
        names are returned\.  

    *pathName* __tab tearoff__ *index* ?*newName*?

    :   Reparents the widget embedded into *index*, placing it
        inside of *newName*\.  *NewName* is either the name of an new
        widget that will contain the embedded widget or the name
        of the __tabset__ widget\.  It the last case, the embedded
        widget is put back into the folder\.  

        If no *newName* argument is provided, then the name of the
        current parent of the embedded widget is returned\.

*pathName* __view__ *args*

:   This command queries or changes the position of the tabset in
    the widget\'s window\.  It can take any of the following forms:

    *pathName* __view__

    :   Returns a list of two numbers between 0\.0 and 1\.0 that
        describe the amount and position of the tabset that is
        visible in the window\.  For example, if *view* is "0\.2
        0\.6", 20% of the tabset\'s text is off\-screen to the left,
        40% is visible in the window, and 40% of the tabset is
        off\-screen to the right\.  These are the same values
        passed to scrollbars via the __\-scrollcommand__ option\.

    *pathName* __view moveto__ *fraction*

    :   Adjusts the view in the window so that *fraction* of the
        total width of the tabset text is off\-screen to the left\.
        *fraction* must be a number between 0\.0 and 1\.0\.

    *pathName* __view scroll__ *number* *what*

    :   This command shifts the view in the window (left/top or
        right/bottom) according to *number* and *what*\.  *Number* must
        be an integer\. *What* must be either __units__ or __pages__ or an
        abbreviation of these\.  If *what* is __units__, the view
        adjusts left or right by *number* scroll units (see the
        __\-scrollincrement__ option)\.  ; if it is __pages__ then the view
        adjusts by *number* widget windows\.  If *number* is negative
        then tabs farther to the left become visible; if it is
        positive then tabs farther to the right become visible\.

WIDGET OPTIONS
==============

Widget configuration options may be set either by the __configure__
operation or the Tk __option__ command\.  The resource class is Tabset\.  The
resource name is the name of the widget\.  

~~~~~
option add *Tabset.Foreground white
option add *Tabset.Background blue
~~~~~

The following widget options are available:  

\-activebackground *color*
:   Sets the default active background color for tabs\.  A tab is
    active when the mouse is positioned over it or set by the
    __activate__ operation\.  Individual tabs may override this option by
    setting the tab\'s __\-activebackground__ option\.  

\-activeforeground *color*
:   Sets the default active foreground color for tabs\.  A tab is
    active when the mouse is positioned over it or set by the
    __activate__ operation\.  Individual tabs may override this option by
    setting the tab\'s __\-activeforeground__ option\.  

\-background *color*
:   Sets the background color of the tabset\.

\-borderwidth *pixels*
:   Sets the width of the 3\-D border around the outside edge of the
    widget\.  The __\-relief__ option determines how the border is to be
    drawn\.  The default is 2\.  

\-cursor *cursor*
:   Specifies the widget\'s cursor\.  The default cursor is ""\.

\-dashes *dashList*
:   Sets the dash style of the focus outline\.  When a tab has the
    widget\'s focus, it is drawn with a dashed outline around its
    label\.  *DashList* is a list of up to 11 numbers that alternately
    represent the lengths of the dashes and gaps on the cross hair
    lines\.  Each number must be between 1 and 255\.  If *dashList* is
    "", the outline will be a solid line\.  The default value is 5 2\.

\-font *fontName*
:   Sets the default font for the text in tab labels\.  Individual
    tabs may override this by setting the tab\'s __\-font__ option\.  The
    default value is \*\-Helvetica\-Bold\-R\-Normal\-\*\-12\-120\-\*\.

\-foreground *color*
:   Sets the default color of tab labels\.  Individual tabs may
    override this option by setting the tab\'s __\-foreground__ option\.
    The default value is black\.  

\-gap *size*
:   Sets the gap (in pixels) between tabs\.  The default value is 2\.

\-height *pixels*
:   Specifies the requested height of widget\.  If *pixels* is 0, then
    the height of the widget will be calculated based on the size
    the tabs and their pages\.  The default is 0\.  

\-highlightbackground  *color*
:   Sets the color to display in the traversal highlight region when
    the tabset does not have the input focus\.  

\-highlightcolor *color*
:   Sets the color to use for the traversal highlight rectangle that
    is drawn around the widget when it has the input focus\.  The
    default is black\.  

\-highlightthickness *pixels*
:   Sets the width of the highlight rectangle to draw around the
    outside of the widget when it has the input focus\. *Pixels* is a
    non\-negative value and may have any of the forms acceptable to
    __Tk\_GetPixels__\.  If the value is zero, no focus highlight is drawn
    around the widget\.  The default is 2\.  

\-outerpad *pixels*
:   Padding around the exterior of the tabset and folder\.

\-pageheight *pixels*
:   Sets the requested height of the page\.  The page is the area
    under the tab used to display the page contents\.  If *pixels* is
    0, the maximum height of all embedded tab windows is used\.  The
    default is 0\.  

\-pagewidth *pixels*
:   Sets the requested width of the page\.  The page is the area
    under the tab used to display the page contents\.  If *pixels* is
    0, the maximum width of all embedded tab windows is used\.  The
    default is 0\.  

\-perforationcommand *string*
:   Specifies a Tcl script to be invoked to tear off the current
    page in the tabset\. This command is typically invoked when left
    mouse button is released over the tab perforation\.  The default
    action is to tear\-off the page and place it into a new toplevel
    window\.  

\-relief *relief*
:   Specifies the 3\-D effect for the tabset widget\.  *Relief*
    specifies how the tabset should appear relative to widget that
    it is packed into; for example, raised means the tabset should
    appear to protrude\.  The default is sunken\.  

\-rotate *theta*
:   Specifies the degrees to rotate text in tab labels\.  *Theta* is a
    real value representing the number of degrees to rotate the tick
    labels\.  The default is 0\.0 degrees\.  

\-samewidth *boolean*
:   Indicates if each tab should be the same width\.  If true, each
    tab will be as wide as the widest tab\.  The default is no\.

\-scrollcommand *string*
:   Specifies the prefix for a command for communicating with
    scrollbars\.  Whenever the view in the widget\'s window changes,
    the widget will generate a Tcl command by concatenating the
    scroll command and two numbers\.  If this option is not
    specified, then no command will be executed\.  

\-scrollincrement *pixels*
:   Sets the smallest number of pixels to scroll the tabs\.  If
    *pixels* is greater than 0, this sets the units for scrolling
    (e\.g\.,  when you the change the view by clicking on the left and
    right arrows of a scrollbar)\.  

\-selectbackground *color*
:   Sets the color to use when displaying background of the selected
    tab\. Individual tabs can override this option by setting the
    tab\'s __\-selectbackground__ option\.  

\-selectcommand *string*
:   Specifies a default Tcl script to be associated with tabs\.  This
    command is typically invoked when left mouse button is released
    over the tab\.  Individual tabs may override this with the tab\'s
    __\-command__ option\. The default value is ""\.  

\-selectforeground *color*
:   Sets the default color of the selected tab\'s text label\.
    Individual tabs can override this option by setting the tab\'s
    __\-selectforeground__ option\. The default value is black\.

\-selectpad *pixels*
:   Specifies extra padding to be displayed around the selected tab\.
    The default value is 3\.  

\-side *side*
:   Specifies the side of the widget to place tabs\. The following
    values are valid for *side*\. The default value is top\.

    top
    :   Tabs are drawn along the top\.

    left
    :   Tabs are drawn along the left side\.

    right
    :   Tabs are drawn along the right side\.

    both
    :   Tabs are drawn along the bottom side\.

\-slant *slant*
:   Specifies if the tabs should be slanted 45 degrees on the left
    and/or right sides\. The following values are valid for *slant*\.
    The default is none\.  

    none
    :   Tabs are drawn as a rectangle\.

    left
    :   The left side of the tab is slanted\.

    right
    :   The right side of the tab is slanted\.

    both
    :   Boths sides of the tab are slanted\.

\-tabbackground *color*
:   Sets the default background color of tabs\.  Individual tabs can
    override this option by setting the tab\'s __\-background__ option\.

\-tabborderwidth *pixels*
:   Sets the width of the 3\-D border around the outside edge of the
    tab\.  The __\-tabrelief__ option determines how the border is to be
    drawn\.  The default is 2\.  

\-tabforeground *color*
:   Specifies the color to use when displaying a tab\'s label\.
    Individual tabs can override this option by setting the tab\'s
    __\-foreground__ option\.  

\-tabrelief *relief*
:   Specifies the 3\-D effect for both tabs and folders\.  *Relief*
    specifies how the tabs should appear relative to background of
    the widget; for example, raised means the tab should appear to
    protrude\.  The default is raised\.  

\-takefocus *focus*
:   Provides information used when moving the focus from window to
    window via keyboard traversal (e\.g\., Tab and Shift\-Tab)\.  If
    *focus* is 0, this means that this window should be skipped
    entirely during keyboard traversal\.  1 means that the this
    window should always receive the input focus\.  An empty value
    means that the traversal scripts decide whether to focus on the
    window\.  The default is 1\.  

__\-tearoff__ *boolean*  

\-textside *side*
:   If both images and text are specified for a tab, this option
    determines on which side of the tab the text is to be displayed\.
    The valid sides are left, right, top, and bottom\.  The default
    value is left\.  

\-tiers *number*
:   Specifies the maximum number of tiers to use to display the
    tabs\.  The default value is 1\.  

\-tile *image*
:   Specifies a tiled background for the widget\.  If *image* isn\'t "",
    the background is tiled using *image*\.  Otherwise, the normal
    background color is drawn (see the __\-background__ option)\.  *Image*
    must be an image created using the Tk __image__ command\.  The
    default is ""\.  

\-width *pixels*
:   Specifies the requested width of the widget\.  If *pixels* is 0,
    then the width of the widget will be calculated based on the
    size the tabs and their pages\.  The default is 0\.

TAB OPTIONS
===========

In addition to the __configure__ operation, widget configuration options
may also be set by the Tk __option__ command\.  The class resource name is
Tab\.  

~~~~~
option add *Tabset.Tab.Foreground white
option add *Tabset.name.Background blue
~~~~~

The following widget options are available:  

\-activebackground *color*
:   Sets the active background color for *nameOrIndex*\.  A tab is
    active when the mouse is positioned over it or set by the
    __activate__ operation\.  This overrides the widget\'s
    __\-activebackground__ option\.  

\-activeforeground *color*
:   Sets the default active foreground color *nameOrIndex*\.  A tab is
    "active" when the mouse is positioned over it or set by the
    __activate__ operation\.  Individual tabs may override this option by
    setting the tab\'s __\-activeforeground__ option\.  

\-anchor *anchor*
:   Anchors the tab\'s embedded widget to a particular edge of the
    folder\.  This option has effect only if the space in the folder
    surrounding the embedded widget is larger than the widget
    itself\. *Anchor* specifies how the widget will be positioned in
    the extra space\.  For example, if *anchor* is center then the
    window is centered in the folder ; if *anchor* is w then the
    window will be aligned with the leftmost edge of the folder\. The
    default value is center\.  

\-background *color*
:   Sets the background color for *nameOrIndex*\.  Setting this option
    overides the widget\'s __\-tabbackground__ option\.  

\-bindtags *tagList*
:   Specifies the binding tags for this tab\.  *TagList* is a list of
    binding tag names\.  The tags and their order will determine how
    commands for events in tabs are invoked\.  Each tag in the list
    matching the event sequence will have its Tcl command executed\.
    Implicitly the name of the tab is always the first tag in the
    list\.  The default value is all\.  

\-command *string*
:   Specifies a Tcl script to be associated with *nameOrIndex*\.  This
    command is typically invoked when left mouse button is released
    over the tab\.  Setting this option overrides the widget\'s
    __\-selectcommand__ option\.  

\-data *string*
:   Specifies a string to be associated with *nameOrIndex*\.  This
    value isn\'t used in the widget code\.  It may be used in Tcl
    bindings to associate extra data (other than the image or text)
    with the tab\. The default value is ""\.  

\-fill *fill*
:   If the space in the folder surrounding the tab\'s embedded widget
    is larger than the widget, then *fill* indicates if the embedded
    widget should be stretched to occupy the extra space\.  *Fill* is
    either none, x, y, both\.  For example, if *fill* is x, then the
    widget is stretched horizontally\.  If *fill* is y, the widget is
    stretched vertically\.  The default is none\.  

\-font *fontName*
:   Sets the font for the text in tab labels\.  If *fontName* is not
    the empty string, this overrides the tabset\'s __\-font__ option\.  The
    default value is ""\.  

\-foreground *color*
:   Sets the color of the label for *nameOrIndex*\.  If *color* is not
    the empty string, this overrides the widget\'s __\-tabforeground__
    option\.  The default value is ""\.  

\-image *imageName*
:   Specifies the image to be drawn in label for *nameOrIndex*\.  If
    *image* is "", no image will be drawn\.  Both text and images may
    be displayed at the same time in tab labels\.  The default value
    is ""\.  

\-ipadx *pad*
:   Sets the padding to the left and right of the label\.  *Pad* can be
    a list of one or two screen distances\.  If *pad* has two elements,
    the left side of the label is padded by the first distance and
    the right side by the second\.  If *pad* has just one distance,
    both the left and right sides are padded evenly\.  The default
    value is 0\.  

\-ipady *pad*
:   Sets the padding to the top and bottom of the label\.  *Pad* can be
    a list of one or two screen distances\.  If *pad* has two elements,
    the top of the label is padded by the first distance and the
    bottom by the second\.  If *pad* has just one distance, both the
    top and bottom sides are padded evenly\.  The default value is 0\.

\-padx *pad*
:   Sets the padding around the left and right of the embedded
    widget, if one exists\.  *Pad* can be a list of one or two screen
    distances\.  If *pad* has two elements, the left side of the widget
    is padded by the first distance and the right side by the
    second\.  If *pad* has just one distance, both the left and right
    sides are padded evenly\.  The default value is 0\.

\-pady *pad*
:   Sets the padding around the top and bottom of the embedded
    widget, if one exists\.  *Pad* can be a list of one or two screen
    distances\.  If *pad* has two elements, the top of the widget is
    padded by the first distance and the bottom by the second\.  If
    *pad* has just one distance, both the top and bottom sides are
    padded evenly\.  The default value is 0\.  

\-selectbackground *color*
:   Sets the color to use when displaying background of the selected
    tab\. If *color* is not the empty string, this overrides the
    widget\'s __\-selectbackground__ option\. The default value is ""\.

\-shadow *color*
:   Sets the shadow color for the text in the tab\'s label\. Drop
    shadows are useful when both the foreground and background of
    the tab have similar color intensities\.  If *color* is the empty
    string, no shadow is drawn\.  The default value is ""\.

\-state *state*
:   Sets the state of the tab\. If *state* is disable the text of the
    tab is drawn as engraved and operations on the tab (such as
    __invoke__ and __tab tearoff__) are ignored\.  The default is normal\.

\-stipple *bitmap*
:   Specifies a stipple pattern to use for the background of the
    folder when the window is torn off\.  *Bitmap* specifies a bitmap
    to use as the stipple pattern\. The default is RBC\.

\-text *text*
:   Specifies the text of the tab\'s label\.  The exact way the text
    is drawn may be affected by other options such as __\-state__ or
    __\-rotate__\.  

\-window *pathName*
:   Specifies the widget to be embedded into the tab\.  *PathName* must
    be a child of the __tabset__ widget\.  The tabset will "pack" and
    manage the size and placement of *pathName*\.  The default value is
    ""\.  

\-windowheight *pixels*
:   Sets the requested height of the page\.  The page is the area
    under the tab used to display the page contents\.  If *pixels* is
    0, the maximum height of all embedded tab windows is used\.  The
    default is 0\.  

\-windowwidth *pixels*
:   Sets the requested width of the page\.  The page is the area
    under the tab used to display the page contents\.  If *pixels* is
    0, the maximum width of all embedded tab windows is used\.  The
    default is 0\.  

DEFAULT BINDINGS
================

RBC automatically generates class bindings that supply tabsets their
default behaviors\. The following event sequences are set by default for
tabsets (via the class bind tag Tabset):  

__\<ButtonPress\-2\>__  

__\<B2\-Motion\>__  

\<ButtonRelease\-2\>
:   Mouse button 2 may be used for scanning\.  If it is pressed and
    dragged over the tabset, the contents of the tabset drag at high
    speed in the direction the mouse moves\.  

__\<KeyPress\-Up\>__  

\<KeyPress\-Down\>
:   The up and down arrow keys move the focus to the tab immediately
    above or below the current focus tab\.  The tab with focus is
    drawn with the a dashed outline around the tab label\.

__\<KeyPress\-Left\>__  

\<KeyPress\-Right\>
:   The left and right arrow keys move the focus to the tab
    immediately to the left or right of the current focus tab\.  The
    tab with focus is drawn with the a dashed outline around the tab
    label\.  

__\<KeyPress\-space\>__  

\<KeyPress\-Return\>
:   The space and return keys select the current tab given focus\.
    When a folder is selected, it\'s command is invoked and the
    embedded widget is mapped\.  

Each tab, by default, also has a set of bindings (via the tag all)\.
These bindings may be reset using the tabset\'s __bind__ operation\.

__\<Enter\>__  

\<Leave\>
:   When the mouse pointer enters a tab, it is activated (i\.e\. drawn
    in its active colors) and when the pointer leaves, it is redrawn
    in its normal colors\.  

\<ButtonRelease\-1\>
:   Clicking with the left mouse button on a tab causes the tab to
    be selected and its Tcl script (see the __\-command__ or
    __\-selectcommand__ options) to be invoked\.  The folder and any
    embedded widget (if one is specified) is automatically mapped\.

__\<ButtonRelease\-3\>__  

\<Control\-ButtonRelease\-1\>
:   Clicking on the right mouse button (or the left mouse button
    with the Control key held down) tears off the current page into
    its own toplevel widget\. The embedded widget is re\-packed into a
    new toplevel and an outline of the widget is drawn in the
    folder\.  Clicking again (toggling) will reverse this operation
    and replace the page back in the folder\.  

BIND TAGS
=========

You can bind commands to tabs that are triggered when a particular
event sequence occurs in them, much like canvas items in Tk\'s canvas
widget\.  Not all event sequences are valid\.  The only binding events
that may be specified are those related to the mouse and keyboard (such
as __Enter__, __Leave__, __ButtonPress__, __Motion__, and __KeyPress__)\.  

It is possible for multiple bindings to match a particular event\.  This
could occur, for example, if one binding is associated with the tab
name and another is associated with the tab\'s tags (see the __\-bindtags__
option)\.  When this occurs, all the matching bindings are invoked\.  A
binding associated with the tab name is invoked first, followed by one
binding for each of the tab\'s bindtags\.  If there are multiple matching
bindings for a single tag, then only the most specific binding is
invoked\.  A continue command in a binding script terminates that
script, and a break command terminates that script and skips any
remaining scripts for the event, just as for the bind command\.

The __\-bindtags__ option for tabs controls addition tag names that can be
matched\.  Implicitly the first tag for each tab is its name\.  Setting
the value of the __\-bindtags__ option doesn\'t change this\.

EXAMPLE
=======

You create a tabset widget with the __tabset__ command\.  

~~~~~
# Create a new tabset
tabset .ts -relief sunken -borderwidth 2
~~~~~

A new Tcl command \.ts is also created\.  This command can be used to
query and modify the tabset\.  For example, to change the default font
used by all the tab labels, you use the new command and the tabset\'s
__configure__ operation\.  

~~~~~
# Change the default font.
.ts configure -font "fixed"
~~~~~

You can then add folders using the __insert__ operation\.  

~~~~~
# Create a new folder "f1"
.ts insert 0 "f1"
~~~~~

This inserts the new tab named "f1" into the tabset\.  The index 0
indicates location to insert the new tab\.  You can also use the index
end to append a tab to the end of the tabset\.  By default, the text of
the tab is the name of the tab\.  You can change this by configuring the
__\-text__ option\.  

~~~~~
# Change the label of "f1"
.ts tab configure "f1" -text "Tab #1"
~~~~~

The __insert__ operation lets you add one or more folders at a time\.

~~~~~
.ts insert end "f2" -text "Tab #2" "f3" "f4"
~~~~~

The tab on each folder contains a label\.  A label may display both an
image and a text string\.  You can reconfigure the tab\'s attributes
(foreground/background colors, font, rotation, etc) using the __tab__
__configure__ operation\.  

~~~~~
# Add an image to the label of "f1"
set image [image create photo -file stopsign.gif]
.ts tab configure "f1" -image $image
.ts tab configure "f2" -rotate 90
~~~~~

Each folder may contain an embedded widget to represent its contents\.
The widget to be embedded must be a child of the tabset widget\.  Using
the __\-window__ option, you specify the name of widget to be embedded\.  But
don\'t pack the widget, the tabset takes care of placing and arranging
the widget for you\.  

~~~~~
graph .ts.graph
.ts tab configure "f1" -window ".ts.graph" \
    -fill both -padx 0.25i -pady 0.25i
~~~~~

The size of the folder is determined the sizes of the Tk widgets
embedded inside each folder\.  The folder will be as wide as the widest
widget in any folder\. The tallest determines the height\.  You can use
the tab\'s __\-pagewidth__ and __\-pageheight__ options override this\.

Other options control how the widget appears in the folder\.  The __\-fill__
option says that you wish to have the widget stretch to fill the
available space in the folder\.  

~~~~~
.ts tab configure "f1" -fill both -padx 0.25i -pady 0.25i
~~~~~

Now when you click the left mouse button on "f1", the graph will be
displayed in the folder\.  It will be automatically hidden when another
folder is selected\.  If you click on the right mouse button, the
embedded widget will be moved into a toplevel widget of its own\.
Clicking again on the right mouse button puts it back into the folder\.

If you want to share a page between two different folders, the __\-command__
option lets you specify a Tcl command to be invoked whenever the folder
is selected\.  You can reset the __\-window__ option for the tab whenever
it\'s clicked\.  

~~~~~
.ts tab configure "f2" -command {
    .ts tab configure "f2" -window ".ts.graph"
}
.ts tab configure "f1" -command {
    .ts tab configure "f1" -window ".ts.graph"
}
~~~~~

If you have many folders, you may wish to stack tabs in multiple tiers\.
The tabset\'s __\-tiers__ option requests a maximum number of tiers\.   The
default is one tier\.  

~~~~~
.ts configure -tiers 2
~~~~~

If the tabs can fit in less tiers, the widget will use that many\.
Whenever there are more tabs than can be displayed in the maximum
number of tiers, the tabset will automatically let you scroll the tabs\.
You can even attach a scrollbar to the tabset\.  

~~~~~
.ts configure -scrollcommand { .sbar set }  -scrollincrement 20
.sbar configure -orient horizontal -command { .ts view }
~~~~~

By default tabs are along the top of the tabset from left to right\.
But tabs can be placed on any side of the tabset using the __\-side__
option\.  

~~~~~
# Arrange tabs along the right side of the tabset.
.ts configure -side right -rotate 270
~~~~~

KEYWORDS
========

tabset, widget  

