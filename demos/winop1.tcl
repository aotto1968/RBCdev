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

if { [ file exists ./images/sample.gif] } {
    set src [image create photo -file ./images/sample.gif]  
} else {
    puts stderr "no image file"
    exit 0
}

set width [image width $src]
set height [image height $src]

option add *Label.font *helvetica*10*
option add *Label.background white
label .l0 -image $src
label .header0 -text "$width x $height"
label .footer0 -text "100%"
. configure -bg white

for { set i 2 } { $i <= 10 } { incr i } {
    set iw [expr $width / $i]
    set ih [expr $height / $i]
    set r [format %6g [expr 100.0 / $i]]
    image create photo r$i -width $iw -height $ih
    winop resample $src r$i sinc
    label .header$i -text "$iw x $ih"
    label .footer$i -text "$r%"
    label .l$i -image r$i
    table . \
	0,$i .header$i \
	1,$i .l$i \
	2,$i .footer$i
    update
}


