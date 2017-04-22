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
if { $tcl_version >= 8.0 } {
    namespace import rbc::*
    namespace import -force rbc::tile::*
}

source scripts/demo.tcl

image create photo bgTile -file ./images/chalk.gif
image create photo label1 -file ./images/mini-book1.gif
image create photo label2 -file ./images/mini-book2.gif

tabset .t -relief raised \
    -activebackground yellow \
    -bg red -borderwidth 0 -highlightthickness 0 \
    -scrollcommand { .s set } \
    -width 3i 

#option add *iPadX 4
#option add *iPadY 2

.t insert end First \
    -image label1 \
    -anchor center \
    -selectbackground darkolivegreen2  \
    Again Next another test of \
    a -image label2 widget 

scrollbar .s -command { .t view } -orient horizontal
table . \
    .t 0,0 -fill both \
    .s 1,0 -fill x 

table configure . r1 -resize none
focus .t

