#!/usr/bin/env wish

package require rbc
# --------------------------------------------------------------------------
# Starting with Tcl 8.x, the RNC commands are stored in their own 
# namespace called "rbc".  The idea is to prevent name clashes with
# Tcl commands and variables from other packages, such as a "table"
# command in two different packages.  
#
# You can access the RNC commands in a couple of ways.  You can prefix
# all the RNC commands with the namespace qualifier "rbc::"
#  
#    rbc::graph .g
#    rbc::table . .g -resize both
# 
# or you can import all the command into the global namespace.
#
#    namespace import rbc::*
#    graph .g
#    table . .g -resize both
#
# --------------------------------------------------------------------------

namespace import rbc::*
cd [file dirname [info script]]

source scripts/demo.tcl

# Create a tabnotebook widget.  

tabnotebook .tnb

# The notebook is initially empty.  Insert tabs (pages) into the notebook.  

foreach label { First Second Third Fourth } {
    .tnb insert end -text $label
}

# Tabs are referred to by their index.  Tab indices can be one of the 
# following:
#
#	 number		Position of tab the notebook's list of tabs.
# 	 @x,y		Tab closest to the specified X-Y screen coordinates.
# 	 "active"	Tab currently under the mouse pointer.
# 	 "focus"	Tab that has focus.  
# 	 "select"	The currently selected tab.
# 	 "right"	Next tab from "focus".
# 	 "left"		Previous tab from "focus".
# 	 "up"		Next tab from "focus".
# 	 "down"		Previous tab from "focus".
# 	 "end"		Last tab in list.
#	 string		Tab identifier.  The "insert" operation returns 
#			a unique identifier for the new tab (e.g. "tab0").  
#			This ID is valid for the life of the tab, even if
#			the tabs are moved or reordered.  

# Each tab has a text label and an optional Tk image.

set image [image create photo -file ./images/mini-book1.gif]
.tnb tab configure 0 -image $image

#
# How to embed a widget into a page.  
#

# 1. The widget must be a child of the tabnotebook.

set image [image create photo -file ./images/rbc98.gif]
label .tnb.label -image $image -relief sunken -bd 2

# 2. Use the -window option to embed the widget.

.tnb tab configure 0 -window .tnb.label

# The tearoff perforation, displayed on the selected tab, is
# controlled by the tabnotebook's -tearoff option.  
#
# If you don't want tearoff pages, configure -tearoff to "no".

.tnb configure -tearoff yes

table . \
    0,0 .tnb -fill both 

focus .tnb

