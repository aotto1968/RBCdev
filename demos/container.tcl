#!/usr/bin/env wish

package require rbc
namespace import rbc::*

set cmd "xterm -geom +4000+4000"
#set cmd "xclock -name fred -geom +4000+4000"
eval bgexec myVar $cmd &
container .c 
pack .c -fill both -expand yes
#.c configure -relief raised -bd 2 -name fred
.c configure -relief raised -bd 2 -command $cmd


