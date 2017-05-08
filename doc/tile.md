

NAME
====

tile \-  Tiling versions of Tk widgets  

SYNOPSIS
========

__tile::button__ *pathName* *option* *value*\.\.\.  

__tile::checkbutton__ *pathName* *option* *value*\.\.\.  

__tile::frame__ *pathName* *option* *value*\.\.\.  

__tile::label__ *pathName* *option* *value*\.\.\.  

__tile::radiobutton__ *pathName* *option* *value*\.\.\.  

__tile::scrollbar__ *pathName* *option* *value*\.\.\.  

__tile::toplevel__ *pathName* *option* *value*\.\.\.  


DESCRIPTION
===========

The tile widgets let you create textured backgrounds\.  The texture is a
Tk image which is tiled over the entire background of the widget\.

INTRODUCTION
============

With the advent of Tk 4\.0, images are now easy to create and use in
applications\.  Images add interest to applications and they convey more
information\.  But one area where Tk hasn\'t taken advantage of images is
using images as textures for widgets\.  Since tiling is a standard
feature of windowing systems, it\'s very easy to use images as textures\.

The tile widgets take the standard Tk 4\.0 widgets and add tiling
configuration options to them\.  Textures are specified by the name of
the image you wish to be tiled across the background of the widget\.

EXAMPLE
=======

To add tiling to a widget, you simply create an image using Tk\'s __image__
command and use the image name as the value for the __\-tile__ configuration
option of the widget\.  

~~~~~
image create photo my_texture -file tan_paper.gif
rbc::tile::frame .f -tile my_texture
~~~~~

The image my\_texture is added to the frame\.  If my\_texture is updated,
so will the widget background\.  

~~~~~
image create photo my_texture -file rain.gif
~~~~~

The tile widget commands reside in the "rbc::tile" namespace, so as not
to collide with the normal Tk widgets\.  An easy way to add tiling to
existing programs is to import the tile widget commands into the global
namespace\.  

~~~~~
image create photo my_texture -file tan_paper.gif
namespace import -force rbc::tile::*
frame .f -tile my_texture
~~~~~

To use one image for all texturing, you can use the "Tile" option class
name to specify the same image for all tile widgets\.  

~~~~~
image create photo my_texture -file tan_paper.gif
option add *Tile my_texture
~~~~~

OPTIONS
=======

The following configurations options are added to the widgets\. If a
__\-tile or \-activetile__ option is specified, it overrides the background
color of the widget\.  

\-activetile *image*
:   Specifies a textured background to display when the widget is
    active\.  This option is available for the __tilebutton__,
    __tilecheckbutton__, __tileradiobutton__, and __tilescrollbar__ widgets\.
    *Image* is the name an image created using Tk\'s __image__ command\.
    The background of the widget is tiled with *image*\.  If *image* is
    "", then the active background color is displayed\.  The default
    is ""\.  

\-tile *image*
:   Specifies a textured background to display for the widget\.
    *Image* is the name an image created using Tk\'s __image__ command\.
    The background of the widget is tiled with *image*\.  If *image* is
    "", then the normal background color is displayed\.  The default
    is ""\.  

KEYWORDS
========

tile, texture, button, label, radiobutton, checkbutton, scrollbar,
frame, toplevel  

