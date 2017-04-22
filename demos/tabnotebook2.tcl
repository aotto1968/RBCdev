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

image create photo bgTile -file ./images/smblue_rock.gif
image create photo label1 -file ./images/mini-book1.gif
image create photo label2 -file ./images/mini-book2.gif
image create photo testImage -file ./images/txtrflag.gif

scrollbar .s -command { .t view } -orient horizontal
tabnotebook .t \
    -relief sunken -bd 2 \
    -textside right \
    -samewidth yes -tiers 2 -slant right \
    -scrollcommand { .s set } \
    -tile bgTile 

label .t.l -image testImage

set attributes {
    graph1 "Graph \#1" red	.t.graph1  
    graph2 "Graph \#2" green	.t.graph2  
    graph3 "Graph \#3" cyan	.t.graph3  
    graph5 "Graph \#5" yellow	.t.graph5  
    graph6 one		orange	.t.l       
}

foreach { entry label color window } $attributes {
    .t insert end -text $label -fill both 
}

foreach label { there bunky another test of a widget } {
    set id [.t insert end -text $label]
}

set img [image create photo -file ./images/blt98.gif]
.t tab configure $id -image label2 -tile $img

table . \
    .t 0,0 -fill both \
    .s 1,0 -fill x 

table configure . r1 -resize none

set index 0
foreach file { graph1 graph2 graph3 graph5 } {
    namespace eval $file {
	set graph [graph .t.$file]
	source scripts/$file.tcl
	.t tab configure $index -window $graph
	incr index
    }
}

