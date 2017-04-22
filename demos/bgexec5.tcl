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

set shell wish
if { [info exists tcl_platform] && $tcl_platform(platform) == "windows" } {
    set shell "$shell.exe"
}
if { [file executable "../src/$shell"] } {
    set shell "../src/$shell"
}

set count 0
foreach demo [glob barchart?.tcl] {
    bgexec var $shell $demo &
}

button .kill -text "Kill All" -command { set var 0 }
table . .kill -fill both 


