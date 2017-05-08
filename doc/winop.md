

NAME
====

winop \- Perform assorted window operations  

SYNOPSIS
========

__winop changes__ ?*window*?\.\.\.  

__winop colormap__ ?*window*?\.\.\.  

__winop convolve__ ?*srcPhoto* *destPhoto* *filter*?\.\.\.  

__winop image__ ?*args*?\.\.\.  

__winop lower__ ?*window*?\.\.\.  

__winop map__ ?*window*?\.\.\.  

__winop move__ *window* *x* *y*  

__winop quantize__ *srcPhoto* *destPhoto* *?nColors?*  

__winop query__  

__winop raise__ ?*window*?\.\.\.  

__winop readjpeg__ ?*fileName* *photoName*?\.\.\.  

__winop subsample__ ?*srcPhoto* *destPhoto* *?horzFilter* *vertFilter?*\.\.\.

__winop snap__ *window* *photoName* *?width* *height?*  

__winop subsample__ *srcPhoto* *destPhoto* *x* *y* *width* *height* *?horzFilter?*
*?vertFilter?*  

__winop unmap__ ?*window*?\.\.\.  

__winop warpto__ ?*window*?  

DESCRIPTION
===========

The __winop__ command performs various window operations on Tk windows
using low\-level Xlib function calls to work around window manager
pecularities\.  

INTRODUCTION
============

Tk has several commands for manipulating its windows: __raise__, __lower__, __wm__,
etc\.  These commands ask the window manager to perform operations on Tk
windows\.  In some cases, a particular window manager won\'t perform the
operation as expected\.  

For example, if you positioned a toplevel window using __wm geometry__, the
window may not actually be at those particular coordinates\.  The
position of the window may be offset by dimensions of the title bar
added by the window manager\.  

In situations like these, the __winop__ command can be used to workaround
these difficulties\.  Instead, it makes low\-level Xlib (such
__XRaiseWindow__ and __XMapWindow__) calls to perform these operations\.

~~~~~
toplevel .top
wm withdraw .top

# Set the geometry to make the window manager
# place the window.
wm geometry .top +100+100

# Move the window to the desired location
# and "update" to force the window manager
# to recognize it.
winop move .top 100 100
update

wm deiconify .top
winop move .top 100 100
~~~~~

OPERATIONS
==========

The following operations are available for the __winop__ command:

__winop lower__ ?*window*?\.\.\.

:   Lowers *window* to the bottom of the X window stack\.  *Window* is
    the path name of a Tk window\.  

__winop map__ ?*window*?\.\.\.

:   Maps *window* on the screen\.  *Window* is the path name of a Tk
    window\. If *window* is already mapped, this command has no effect\.

__winop move__ *window* *x* *y*

:   Move *window* to the screen location specified by *x* and *y*\. *Window*
    is the path name of a Tk window, while *x* and *y* are screen
    coordinates\.  This command returns the empty string\.

__winop raise__ ?*window*?\.\.\.

:   Raises *window* to the top of the X window stack\. *Window* must be a
    valid path name of a Tk window\.  This command returns the empty
    string\.  

__winop snap__ *window* *photoName*

:   Takes a snapshot of the *window* and stores the contents in the
    photo image *photoName*\. *Window* is the valid path name of a Tk
    window which must be totally visible (unobscured)\.  *PhotoName* is
    the name of a Tk photo image which must already exist\.  This
    command can fail if the window is obscured in any fashion, such
    as covered by another window or partially offscreen\.  In that
    case, an error message is returned\.  

__winop unmap__ ?*window*?\.\.\.

:   Unmaps *window* from the screen\. *Window* is the path name of a Tk
    window\.  

__winop warpto__ ?*window*?

:   Warps the pointer to *window*\. *Window* is the path name of a Tk
    window which must be mapped\. If *window* is in the form *\@x,y*,
    where *x* and *y* are root screen coordinates, the pointer is warped
    to that location on the screen\.  

    \[*I\'ve* *never* *heard* *a* *good* *case* *for* *warping* *the* *pointer* *in* *an*
    *application\.*  *It* *can* *be* *useful* *for* *testing,* *but* *in* *applications,*
    *it\'s* *always* *a* *bad* *idea\.*  *Simply* *stated,* *the* *user* *owns* *the*
    *pointer,* *not* *the* *application\.*  *If* *you* *have* *an* *application* *that*
    *needs* *it,* *I\'d* *like* *to* *hear* *about* *it\.*\]  

    If no *window* argument is present the current location of the
    pointer is returned\. The location is returned as a list in the
    form "*x* *y*", where *x* and *y* are the current coordinates of the
    pointer\.  

KEYWORDS
========

window, map, raise, lower, pointer, warp  

