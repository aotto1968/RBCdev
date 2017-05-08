

NAME
====

eps \-  Encapsulated PostScript canvas item\.  

SYNOPSIS
========

*canvas* __create eps__ *x* *y* ?*option* *value*?\.\.\.  

DESCRIPTION
===========

The __eps__ canvas item lets you place encapulated PostScript (EPS) on a
canvas, controlling its size and placement\.  The EPS item is displayed
either as a solid rectangle or a preview image\.  The preview image is
designated in one of two ways: 1) the EPS file contains an ASCII
hexidecimal preview, or 2) a Tk photo image\.  When the canvas generates
PostScript output, the EPS will be inserted with the proper translation
and scaling to match that of the EPS item\. So can use the canvas widget
as a page layout tool\.  

EXAMPLE
=======

Let\'s say you have for PostScript files of four graphs which you want
to tile two\-by\-two on a single page\.  Maybe you\'d like to annotate the
graphs by putting a caption at the bottom of each graph\.

Normally, you would have to resort to an external tool or write your
own PostScript program\.  The __eps__ canvas item lets you do this through
Tk\'s canvas widget\.  An __eps__ item displays an image (or rectangle)
representing the encapsulated PostScript file\.  It also scales and
translates the EPS file when the canvas is printed\.  

SYNTAX
======

*canvas* __create eps__ *x* *y* ?*option* *value*?\.\.\.  The __eps__ item creates a new
canvas item\. *Canvas* is the name of a __canvas__ widget\.  You must supply
the X\-Y coordinate of the new eps item\.  How the coordinate is exactly
interpretered is controlled by the __\-anchor__ option (see below)\.

Additional options may be specified on the command line to configure
aspects of the eps item such as its color, stipple, and font\.  The
following *option* and *value* pairs are valid\.  

\-anchor *anchor*
:   Tells how to position the EPS item relative to its X\-Y
    coordinate\.  The default is center\.  

\-background *color*
:   Sets the background color of the EPS rectangle\.

\-borderwidth *pixels*
:   Sets the width of the 3\-D border around the outside edge of the
    item\.  The __\-relief__ option determines if the border is to be
    drawn\.  The default is 0\.  

\-file *fileName*
:   Specifies the name of the EPS file\.  The first line of an EPS
    file must start with "%\!PS" and contain a "EPS" version
    specification\.  The other requirement is that there be a
    "%%BoundingBox:" entry which contains four integers representing
    the lower\-left and upper\-right coordinates of the area bounding
    the EPS\.  The default is ""\.  

\-font *fontName*
:   Specifies the font of the title\. The default is \*\-Helvetica\-
    Bold\-R\-Normal\-\*\-18\-180\-\*\.  

\-foreground *color*
:   Specifies the foreground color of the EPS rectangle\.  The option
    matters only when the __\-stipple__ option is set\.  The default is
    white\.  

\-height *pixels*
:   Specifies the height EPS item\.  If *pixels* is 0, then the height
    is determined from the PostScript "BoundingBox:" entry in the
    EPS file\.  The default is 0\.  

\-image *photo*
:   Specifies the name of a Tk photo image to be displayed as in the
    item as a preview image\.  This option overrides any preview
    specification found in the EPS file\.  The default is ""\.

\-justify *justify*
:   Specifies how the title should be justified\.  This matters only
    when the title contains more than one line of text\. *Justify* must
    be left, right, or center\.  The default is center\.

\-relief *relief*
:   Specifies the 3\-D effect for the EPS item\.  *Relief* specifies how
    the item should appear relative to canvas; for example, raised
    means the item should appear to protrude\.  The default is flat\.

\-shadowcolor *color*
:   Specifies the color of the drop shadow used for the title\.  The
    option with the __\-shadowoffset__ option control how the title\'s
    drop shadow appears\.  The default is grey\.  

\-shadowoffset *pixels*
:   Specifies the offset of the drop shadow from the title\'s text\.
    If *pixels* is 0, no shadow will be seen\.  The default is 0\.

\-showimage *boolean*
:   Indicates whether to display the image preview (if one exists),
    or a simple rectangle\.  The default is yes\.  

\-stipple *bitmap*
:   Specifies a bitmap to used to stipple the rectangle representing
    the EPS item\.  The default is ""\.  

\-title *string*
:   Sets the title of the EPS item\.  If *string* is "", then the title
    specified by the PostScript "Title:" entry is used\.  You can set
    the string a single space to display no title\.  The default is
    ""\.  

\-titleanchor *anchor*
:   Tells how to position the title within EPS item\.  The default is
    n\.  

\-titlecolor *color*
:   Specifies the color of the title\.  The default is white\.

\-titlerotate *degrees*
:   Sets the rotation of the title\.  *Degrees* is a real number
    representing the angle of rotation\.  The title is first rotated
    in space and then placed according to the __\-titleanchor__ position\.
    The default rotation is 0\.0\.  

\-width *pixels*
:   Specifies the width EPS item\.  If *pixels* is 0, then the width is
    determined from the PostScript "BoundingBox:" entry in the EPS
    file\.  The default is 0\.  5i\.  

