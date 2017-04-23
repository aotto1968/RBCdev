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

proc ShowResult { name1 name2 how } {
    global var
    .l$name2 configure -text "$var($name2)"
    after 2000 "table forget .l$name2"
}
    
for { set i 1 } { $i <= 20 } { incr i } {
    label .l$i 
    table . .l$i $i,0
    set pid [bgexec var($i) du /usr/include &]
    .l$i configure -text "Starting #$i pid=$pid"
    trace variable var($i) w ShowResult
    update
    after 500
}

