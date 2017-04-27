#!/usr/bin/env wish

package require rbc
namespace import rbc::*

#set cmd "xterm -name otto -geom +4000+4000"
set cmd [list [info nameofexecutable] demos/graph1.tcl -name otto -geom -4000-4000]
#set cmd "xclock -name fred -geom +4000+4000"
bgexec myVar {*}$cmd &
container .c 
pack .c -fill both -expand yes

## 1. using --command
#.c configure -relief raised -bd 2 -command "*xterm*"

## 2. using --name
.c configure -relief raised -bd 2 -name "otto"


