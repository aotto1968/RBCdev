

NAME
====

table \- Arranges widgets in a table  

SYNOPSIS
========

__table__ *container* ?*widget* *index* *option* *value*?\.\.\.  

__table arrange__ *container*  

__table cget__ *container* ?*item*? *option*  

__table configure__ *container* ?*item*?\.\.\. ?*option* *value*?\.\.\.

__table extents__ *container* *item*  

__table forget__ *widget* ?*widget*?\.\.\.  

__table info__ *container* *item*  

__table locate__ *container* *x* *y*  

__table containers__ ?*switch*? ?*arg*?  

__table save__ *container*  

__table search__ *container* ?*switch* *arg*?\.\.\.  

DESCRIPTION
===========

The __table__ command arranges widgets in a table\.  The alignment of
widgets is detemined by their row and column positions and the number
of rows or columns that they span\.  

INTRODUCTION
============

Probably the most painstaking aspect of building a graphical
application is getting the placement and size of the widgets just
right\.  It usually takes many iterations to align widgets and adjust
their spacing\.  That\'s because managing the geometry of widgets is
simply not a packing problem, but also graphical design problem\.
Attributes such as alignment, symmetry, and balance are more important
than minimizing the amount of space used for packing\.

The __table__ geometry manager arranges widgets in a table\.  It\'s easy to
align widgets (horizontally and vertically) or to create empty space to
balance the arrangement of the widgets\.  Widgets (called *slaves* in the
Tk parlance) are arranged inside a containing widget (called the
*master*)\.  Widgets are positioned at row,column locations and may span
any number of rows or columns\.  More than one widget can occupy a
single location\.  

The placement of widget windows determines both the size and
arrangement of the table\.  The table queries the requested size of each
widget\.  The *requested* *size* of a widget is the natural size of the
widget (before the widget is shrunk or expanded)\.  The height of each
row and the width of each column is the largest widget spanning that
row or column\.  The size of the table is in turn the sum of the row and
column sizes\.  This is the table\'s *normal* *size*\.  

The total number of rows and columns in a table is determined from the
indices specified\.  The table grows dynamically as windows are added at
larger indices\.  

EXAMPLE
=======

The table geometry manager is created by invoking the __table__ command\.

~~~~~
# Create a table in the root window
table .
~~~~~

The window \. is now the *container* of the table\.  Widgets are packed
into the table and displayed within the confines of the container\.

You add widgets to the table by row and column location\.  Row and
column indices start from zero\.  

~~~~~
label .title -text "This is a title"

# Add a label to the table
table . .title 0,0
~~~~~

The label \.title is added to the table\.  We can add more widgets in the
same way\.  

~~~~~
button .ok -text "Ok"
button .cancel -text "Cancel"

# Add two buttons
table . .ok 1,0
table . .cancel 1,1
~~~~~

Two buttons \.ok and \.cancel are now packed into the second row of the
table\.  They each occupy one cell of the table\.  By default, widgets
span only a single row and column\.  

The first column contains two widgets, \.title and \.ok\.  By default, the
widest of the two widgets will define the width of the column\.
However, we want \.title to be centered horizontally along the top of
the table\.  We can make \.title span two columns using the __configure__
operation\.  

~~~~~
# Make the label span both columns
table configure . .title -cspan 2
~~~~~

The label \.title will now be centered along the top row of the table\.

In the above example, we\'ve create and arranged the layout for the
table invoking the __table__ command several times\.  Alternately, we could
have used a single __table__ command\.  

~~~~~
label .title -text "This is a title"
button .ok -text "Ok"
button .cancel -text "Cancel"

# Create and pack the table
table . \
    .title  0,0 -cspan 2 \
    .ok     1,0 \
    .cancel 1,1
~~~~~

The table will override the requested width and height of the container
so that the window fits the table exactly\.  This also means that any
change to the size of table will be propagated up through the Tk window
hierarchy\.  This feature can be turned off using the __configure__
operation again\.  

~~~~~
table configure . -propagate no
~~~~~

You can also set the width of height of the table to a specific value\.
This supersedes the calculated table size\.  

~~~~~
# Make the container 4 inches wide, 3 inches high
table configure . -reqwidth 4i -reqheight 3i
~~~~~

If a widget is smaller than the cell(s) it occupies, the widget will
float within the extra space\.  By default, the widget will be centered
within the space, but you can anchor the widget to any side of cell
using the __\-anchor__ configuration option\.  

~~~~~
table configure . .ok -anchor w
~~~~~

The __\-fill__ option expands the widget to fill the extra space either
vertically or horizontally (or both)\.  

~~~~~
# Make the title label fill the entire top row
table configure . .title -cspan 2 -fill x

# Each button will be as height of the 2nd row.
table configure . .ok .cancel -fill y
~~~~~

The width of \.title will be the combined widths of both columns\.  Both
\.ok and \.cancel will become as tall as the second row\.

The __\-padx__ and __\-pady__ options control the amount of padding around the
widget\.  Both options take a list of one or two values\.

~~~~~
# Pad the title by two pixels above and below.
table configure . .title -pady 2

# Pad each button 2 pixels on the left, and 4 on the right.
table configure . .ok .cancel -padx { 2 4 }
~~~~~

If the list has only one value, then both exterior sides (top and
bottom or left and right) of the widget are padded by that amount\.  If
the list has two elements, the first specifies padding for the top or
left side and the second for the bottom or right side\.

Like the container, you can also override the requested widths and
heights of widgets using the __\-reqwidth__ and __\-reqheight__ options\.  This is
especially useful with character\-based widgets (such as buttons,
labels, text, listbox, etc) that let you specify their size only in
units of characters and lines, instead of pixels\.  

~~~~~
# Make all buttons one inch wide
table configure . .ok .cancel -reqwidth 1i
~~~~~

Each row and column of the table can be configured, again using the
__configure__ operation\.  Rows are and columns are designated by R*i* and C*i*
respectively, where *i* is the index of the row or column\.

For example, you can set the size of a row or column\.

~~~~~
# Make the 1st column 2 inches wide
table configure . c0 -width 2.0i

# Make the 2nd row 1/2 inch high.
table configure . r1 -height 0.5i
~~~~~

The new size for the row or column overrides its calculated size\.  If
no widgets span the row or column, its height or width is zero\.  So you
can use the __\-width__ and __\-height__ options to create empty spaces in the
table\.  

~~~~~
# Create an empty row and column
table configure . r2 c2 -width 1i
~~~~~

The __\-pady__ option lets you add padding to the top and bottom sides of
rows\.  The __\-padx__ option adds padding to the left and right sides of
columns\.  Both options take a list of one or two values\.

~~~~~
# Pad above the title by two pixels
table configure . r0 -pady { 2 0 }

# Pad each column 4 pixels on the left, and 2 on the right.
table configure . c* -padx { 2 4 }
~~~~~

Notice that you can configure all the rows and columns using either R\*
or C\*\.  

When the container is resized, the rows and columns of the table are
also resized\.  Only the rows or columns that contain widgets (a widget
spans the row or column) grow or shrink\.  The __\-resize__ option indicates
whether the row or column can be shrunk or stretched\.  If the value is
shrink, the row or column can only be resized smaller\.  If expand, it
can only be resized larger\.  If none, the row or column is frozen at
its requested size\.  

~~~~~
# Let the 1st column get smaller, but not bigger
table configure . c0 -resize shrink

# Let the 2nd column get bigger, not smaller
table configure . c1 -resize expand

# Don't resize the first row
table configure . r0 -resize none
~~~~~

The following example packs a canvas, two scrollbars, and a title\.  The
rows and columns containing the scrollbars are frozen at their
requested size, so that even if the frame is resized, the scrollbars
will remain the same width\.  

~~~~~
table . \
    .title   0,0 -cspan 3 \
    .canvas  1,1 -fill both \
    .vscroll 1,2 -fill y \
    .hscroll 2,1 -fill x

# Don't let the scrollbars resize
table configure . c2 r2 -resize none

# Create an empty space to balance the scrollbar
table configure . c0 -width .vscroll
~~~~~

Note that the value of the __\-width__ option is the name of a widget
window\.  This indicates that the width of the column should be the same
as the requested width of \.vscroll\.  

Finally, the __forget__ operation removes widgets from the table\.

~~~~~
# Remove the windows from the table
table forget .quit .frame
~~~~~

It\'s not necessary to specify the container\.  The __table__ command
determines the container from the widget name\.  

OPERATIONS
==========

The following operations are available for the __table__:

__table__ *container* ?*widget* *index* *option* *value*?\.\.\.

:   Adds the widget *widget* to the table at *index*\.  *Index* is a
    row,column position in the table\.  It must be in the form
    *row*,*column* where *row* and *column* are the respective row and
    column numbers, starting from zero (0,0 is the upper leftmost
    position)\.  *Row* and *column* may also be numeric expressions that
    are recursively evaluated\.  If a table doesn\'t exist for
    *container*, one is created\.  *Widget* is the path name of the
    window, that must already exist, to be arranged inside of
    *container*\. *Option* and *value* are described in the __WIDGET OPTIONS__
    section\.  

__table arrange__ *container*

:   Forces the table to compute its layout immediately\.  Normally,
    the table geometry manager will wait until the next idle point,
    before calculating the size of its rows and columns\.  This is
    useful for collecting the *normal* sizes of rows and columns, that
    are based upon the requested widget sizes\.  

__table cget__ *container* ?*item*? *option*

:   Returns the current value of the configuration option specific
    to *item* given by *option*\.  *Item* is either a row or column index,
    or the path name of a widget\.  *Item* can be in any form describe
    in the __configure__ operation below\. If no *item* argument is
    provided, then the configuration option is for the table itself\.
    *Option* may be any one of the options described in the appropiate
    section for *item*\.  

__table configure__ *container* *item*\.\.\. ?*option* *value*?\.\.\.

:   Queries or modifies the configuration options specific to *item*\.
    If no *option* is specified, this command returns a list
    describing all of the available options for *item* If the argument
    *item* is omitted, then the specified configuration options are
    for the table itself\.  Otherwise *item* must be either a row or
    column specification, or the path name of a widget\.  The
    following *item* types are available\.  

    C*i*
    :   Specifies the column of *container* to be configured\.  *Item*
        must be in the form C*n*, where *i* is the index of the
        column\.  See the __COLUMN OPTIONS__ section\.

    R*i*
    :   Specifies the row of *container* to be configured\. *Item*
        must be in the form R*i*, where *i* is the index of the row\.
        See the __ROW OPTIONS__ section\.  

    *widget*
    :   Specifies a widget of *container* to be queried\.  *Widget* is
        the path name of a widget packed in *container*\.  See the
        __WIDGET OPTIONS__ section\.  

    No argument
    :   Specifies that the table itself is to be queried\.  See
        the __TABLE OPTIONS__ section for a description of the
        option\-value pairs for the table\.  

    The *option* *and* *value* pairs are specific to *item*\.  If *option* is
    specified with no *value*, then the command returns a list
    describing the one named option (this list will be identical to
    the corresponding sublist of the value returned if no *option* is
    specified)\.  If one or more *option\-value* pairs are specified,
    then the command modifies the given option(s) to have the given
    value(s); in this case the command returns the empty string\.

__table extents__ *container* *index*

:   Queries the location and dimensions of row and columns in the
    table\.  *Index* can be either a row or column index or a table
    index\.  Returns a list of the x,y coordinates (upperleft corner)
    and dimensions (width and height) of the cell, row, or column\.

__table forget__ *widget* ?*widget*?\.\.\.

:   Requests that *widget* no longer have its geometry managed\.
    *Widget* is the pathname of the window currently managed by some
    table\. The window will be unmapped so that it no longer appears
    on the screen\.  If *widget* is not currently managed by any table,
    an error message is returned, otherwise the empty string\.

__table info__ *container* *item*

:   Returns a list of the current configuration options for *item*\.
    The list returned is exactly in the form that might be specified
    to the __table__ command\.  It can be used to save and reset table
    configurations\. *Item* must be one of the following\.

    C*i*
    :   Specifies the column of *container* to be queried\.  *Item*
        must be in the form C*n*, where *n* is the index of the
        column\.  

    R*i*
    :   Specifies the row of *container* to be queried\. *Item* must
        be in the form R*i*, where *i* is the index of the row\.

    *widget*
    :   Specifies a widget of *container* to be queried\.  *Widget* is
        the path name of a widget packed in *container*\.

    No argument
    :   Specifies that the table itself is to be queried\.

__table locate__ *container* *x* *y*

:   Returns the table index (row,column) of the cell containing the
    given screen coordinates\.  The *x* and *y* arguments represent the x
    and y coordinates of the sample point to be tested\.

__table containers__ ?*switch* *arg*?

:   Returns a list of all container windows matching a given
    criteria (using *switch* and *arg*)\.  If no *switch* and *arg* arguments
    are given, the names of all container windows (only those using
    the __table__ command) are returned\.  The following are valid
    switches:  

    \-pattern *pattern*
    :   Returns a list of pathnames of all container windows
        matching *pattern*\.  

    \-slave *window*
    :   Returns the name of the container window of table
        managing *window*\.  *Window* must be the path name of widget\.
        If *window* is not managed by any table, the empty string
        is returned\.  

__table search__ *container* ?*switch* *arg*?\.\.\.

:   Returns the names of all the widgets in *container* matching the
    criteria given by *switch* and *arg*\.  *Container* is name of the
    container window associated with the table to be searched\.  The
    name of the widget is returned if any one *switch*\-*arg* criteria
    matches\. If no *switch*\-*arg* arguments are given, the names of all
    widgets managed by *container* are returned\.  The following are
    switches are available:  

    \-pattern *pattern*
    :   Returns the names of any names of the widgets matching
        *pattern*\.  

    \-span *index*
    :   Returns the names of widgets that span *index*\. A widget
        does not need to start at *index* to be included\.  *Index*
        must be in the form *row*,*column*, where *row* and *column* are
        valid row and column numbers\.  

    \-start *index*
    :   Returns the names of widgets that start at *index*\.  *Index*
        must be in the form *row*,*column*, where *row* and *column* are
        valid row and column numbers\.  

TABLE OPTIONS
=============

To configure the table itself, you omit the *item* argument when invoking
the __configure__ operation\.  

~~~~~
table configure container ?option value?...
~~~~~

The following options are available for the table:  

\-padx *pad*
:   Sets how much padding to add to the left and right
    exteriors of the table\.  *Pad* can be a list of one or two
    numbers\.  If *pad* has two elements, the left side of the
    table is padded by the first value and the right side by
    the second value\.  If *pad* has just one value, both the
    left and right sides are padded evenly by the value\.  The
    default is 0\.  

\-pady *pad*
:   Sets how much padding to add to the top and bottom
    exteriors of the table\.  *Pad* can be a list of one or two
    numbers\.  If *pad* has two elements, the area above the
    table is padded by the first value and the area below by
    the second value\.  If *pad* is just one number, both the
    top and bottom areas are padded by the value\.  The
    default is 0\.  

\-propagate *boolean*
:   Indicates if the table should override the requested
    width and height of the *container* window\.  If *boolean* is
    false, *container* will not be resized\.  *Container* will be
    its requested size\.  The default is 1\.  

WIDGET OPTIONS
==============

widgets are configured by specifying the name of the widget when
invoking the __configure__ operation\.  __table configure__ *container* *widget*
?*option* *value*?\.\.\.  *Widget* must be the path name of a window already
packed in the table associated with *container*\.  The following options
are available for widgets:  

\-anchor *anchor*
:   Anchors *widget* to a particular edge of the cell(s) it
    resides\.  This option has effect only if the space of the
    spans surrounding *widget* is larger than *widget*\. *Anchor*
    specifies how *widget* will be positioned in the space\.
    For example, if *anchor* is center then the window is
    centered in the rows and columns it spans; if *anchor* is w
    then the window will be aligned with the leftmost edge of
    the span\. The default is center\.  

\-columnspan *number*
:   Sets the number of columns *widget* will span\.  The default
    is 1\.  

\-columncontrol *control*
:   Specifies how the width of *widget* should control the
    width of the columns it spans\. *Control* is either normal,
    none, or full\.  The default is normal\.  

    none
    :   The width of *widget* is not considered\.

    full
    :   Only the width of *widget* will be considered
        when computing the widths of the columns\.

    normal
    :   Indicates that the widest widget spanning the
        column will determine the width of the span\.

\-fill *fill*
:   Specifies if *widget* should be stretched to fill any free
    space in the span surrounding *widget*\. *Fill* is either
    none, x, y, both\.  The default is none\.

    x
    :   The widget can grow horizontally\.

    y
    :   The widget can grow vertically\.

    both
    :   The widget can grow both vertically and
        horizontally\.  

    none
    :   The widget does not grow along with the span\.

\-ipadx *pixels*
:   Sets how much horizontal padding to add internally on the
    left and right sides of *widget*\.  *Pixels* must be a valid
    screen distance like 2 or 0\.3i\.  The default is 0\.

\-ipady *pixels*
:   Sets how much vertical padding to add internally on the
    top and bottom of *widget*\.  *Pixels* must be a valid screen
    distance like 2 or 0\.3i\.  The default is 0\.

\-padx *pad*
:   Sets how much padding to add to the left and right
    exteriors of *widget*\.  *Pad* can be a list of one or two
    numbers\.  If *pad* has two elements, the left side of
    *widget* is padded by the first value and the right side by
    the second value\.  If *pad* has just one value, both the
    left and right sides are padded evenly by the value\.  The
    default is 0\.  

\-pady *pad*
:   Sets how much padding to add to the top and bottom
    exteriors of *widget*\.  *Pad* can be a list of one or two
    numbers\.  If *pad* has two elements, the area above *widget*
    is padded by the first value and the area below by the
    second value\.  If *pad* is just one number, both the top
    and bottom areas are padded by the value\.  The default is
    0\.  

\-reqheight *height*
:   Specifies the limits of the requested height for *widget*\.
    *Height* is a list of bounding values\.  See the __BOUNDING__
    __SIZES__ section for a description of this list\.  By
    default, the height of *widget* is its requested height
    with its internal padding (see the __\-ipady__ option)\.  The
    bounds specified by *height* either override the height
    completely, or bound the height between two sizes\.  The
    default is ""\.  

\-reqwidth *width*
:   Specifies the limits of the requested width for *widget*\.
    *Width* is a list of bounding values\.  See the __BOUNDING__
    __SIZES__ section for a description of this list\.  By
    default, the width of *widget* is its requested width with
    its internal padding (set the __\-ipadx__ option)\.  The bounds
    specified by *width* either override the width completely,
    or bound the height between two sizes\.  The default is
    ""\.  

\-rowspan *number*
:   Sets the number of rows *widget* will span\. The default is
    1\.  

\-rowcontrol *control*
:   Specifies how the height of *widget* should control the
    height of the rows it spans\. *Control* is either normal,
    none, or full\.  The default is normal\.  

    none
    :   The height of *widget* is not considered\.

    full
    :   Only the height of *widget* will be considered
        when computing the heights of the rows\.

    normal
    :   Indicates that the tallest widget spanning the
        row will determine the height of the span\.

COLUMN OPTIONS
==============

To configure a column in the table, specify the column index as C*i*,
where *i* is the index of the column to be configured\.  __table configure__
*container* *Ci* ?*option* *value*?\.\.\.  If the index is specified as C\*, then
all columns of the table will be configured\.  The following options are
available for table columns\.  

\-padx *pad*
:   Sets the padding to the left and right of the column\.
    *Pad* can be a list of one or two numbers\.  If *pad* has two
    elements, the left side of the column is padded by the
    first value and the right side by the second value\.  If
    *pad* has just one value, both the left and right sides are
    padded evenly by the value\.  The default is 0\.

\-resize *mode*
:   Indicates that the column can expand or shrink from its
    requested width when the table is resized\.  *Mode* must be
    one of the following: none, expand, shrink, or both\.  If
    *mode* is expand the width of the column is expanded if
    there is extra space in the container window\. If *mode* is
    shrink its width may be reduced beyond its requested
    width if there is not enough space in the container\.  The
    default is none\.  

\-width *width*
:   Specifies the limits within that the width of the column
    may expand or shrink\.  *Width* is a list of bounding
    values\.  See the section __BOUNDING SIZES__ for a description
    of this list\.  By default there are no constraints\.

ROW OPTIONS
===========

To configure a row in the table, specify the row index as R*i*, where *i*
is the index of the row to be configured\.  __table configure__ *container* *Ri*
?*option* *value*?\.\.\.  If the index is specified as R\*, then all rows of
the table will be configured\.  The following options are available for
table rows\.  

\-height *height*
:   Specifies the limits of the height that the row may
    expand or shrink to\.  *Height* is a list of bounding
    values\.  See the section __BOUNDING SIZES__ for a description
    of this list\.  By default there are no constraints\.

\-pady *pad*
:   Sets the padding above and below the row\.  *Pad* can be a
    list of one or two numbers\.  If *pad* has two elements, the
    area above the row is padded by the first value and the
    area below by the second value\.  If *pad* is just one
    number, both the top and bottom areas are padded by the
    value\.  The default is 0\.  

\-resize *mode*
:   Indicates that the row can expand or shrink from its
    requested height when the table is resized\.  *Mode* must be
    one of the following: none, expand, shrink, or both\.  If
    *mode* is expand the height of the row is expanded if there
    is extra space in the container\. If *mode* is shrink its
    height may be reduced beyond its requested height if
    there is not enough space in the container\. The default
    is none\.  

BOUNDING SIZES
==============

Sometimes it\'s more useful to limit resizes to an acceptable range,
than to fix the size to a particular value or disallow resizing
altogether\.  Similar to the way the __wm__ command lets you specify a
__minsize__ and __maxsize__ for a toplevel window, you can bound the sizes the
container, a widget, row, or column may take\.  The __\-width__, __\-height__,
__\-reqwidth__, and __\-reqheight__ options, take a list of one, two, or three
values\.  We can take a previous example and instead preventing
resizing, bound the size of the scrollbars between two values\.

~~~~~
table . \
    .title   0,0 -cspan 3 \
    .canvas  1,1 -fill both \
    .vscroll 1,2 -fill y \
    .hscroll 2,1 -fill x

# Bound the scrollbars between 1/8 and 1/2 inch
table configure . c2 -width { 0.125 0.5 }
table configure . r2 -height { 0.125 0.5 }
table configure . vscroll .hscroll -fill both
~~~~~

The scrollbars will get no smaller than 1/8 of an inch, or bigger than
1/2 inch\.  The initial size will be their requested size, so long as it
is within the specified bounds\.  

How the elements of the list are interpreted is dependent upon the
number of elements in the list\.  

{}
:   Empty list\. No bounds are set\. The default sizing is
    performed\.  

{ *x* }
:   Fixes the size to *x*\.  The window or partition cannot
    grow or shrink\.  

{ *min* *max* }
:   Sets up minimum and maximum limits for the size of the
    window or partition\.  The window or partition can be
    reduced less than *min*, nor can it be stretched beyond
    *max*\.  

{ *min* *max* *nom* }
:   Specifies minimum and maximum size limits, but also
    specifies a nominal size *nom*\.  This overrides the
    calculated size of the window or partition\.

MISCELLANEOUS
=============

Another feature is that you can put two widgets in the same cell of the
table\.  This is useful when you want to add decorations around a
widget\.  

~~~~~
frame .frame -bd 1 -relief sunken
button .quit -text "Quit"

# Put both the frame and the button in the same cell.
table . \
    .quit  1,0 -padx 2 -pady 2 \
    .frame 1,0 -fill both
~~~~~

LIMITATIONS
===========

A long standing bug in Tk (circa 1993), there is no way to detect if a
window is already a container of a different geometry manager\. This is
usually done by accident, such as the following where all three widgets
are arranged in the same container "\.", but using different geometry
managers\.  

> table \.f1  

\.\.\.
:   pack \.f2

\.\.\.
:   grid \.f3

This leads to bizarre window resizing, as each geometry manager applies
its own brand of layout policies\.  When the container is a top level
window (such as "\."), your window manager may become locked as it
responds to the never\-ending stream of resize requests\.

KEYWORDS
========

frame, geometry manager, location, table, size  

