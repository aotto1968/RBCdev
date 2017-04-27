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

set saved [pwd]

#rbc::rbcdebug 100

image create photo bgTexture -file ./images/rain.gif

set imageList {}
foreach f [glob ./images/mini-*.gif] {
    lappend imageList [image create photo -file $f]
}

#option add *Hierbox.Tile	bgTexture
option add *Hierbox.ScrollTile  yes

option add *xHierbox.openCommand	{
    if { [file isdirectory ..] } {
	cd ..
	set files [glob -nocomplain * */. ]
	if { $files != "" } {
	    %W insert -at %n end {*}$files
	}
    }
}

option add *xHierbox.closeCommand {
    eval %W delete %n 0 end
}

image create photo openFolder -file images/open.gif
image create photo closeFolder -file images/close.gif

option add *Hierbox.icons "closeFolder openFolder"

image create photo openFolder2 -file images/open2.gif
image create photo closeFolder2 -file images/close2.gif

option add *Hierbox.activeIcons "closeFolder2 openFolder2"

hierbox .h  \
    -activebackground lightblue \
    -yscrollcommand { .vs set } \
    -xscrollcommand { .hs set } 

scrollbar .vs -orient vertical -command { .h yview }
scrollbar .hs -orient horizontal -command { .h xview }
table . \
    0,0 .h  -fill both \
    0,1 .vs -fill y \
    1,0 .hs -fill x

table configure . c1 r1 -resize none

proc DoFind { dir path } {
    global fileList
    set saved [pwd]

    cd $dir
    lappend fileList $path
    foreach f [lsort [glob -nocomplain *]] {
	set entry [file join $path $f]
	lappend fileList $entry
	if { [file isdirectory $f] } {
	    DoFind $f $entry
	}
    }
    cd $saved
}

proc Find { dir } {
    global fileList
    set fileList {}
    DoFind $dir $dir
    return $fileList
}
set top ..
set trim "$top"

.h configure -separator "/" -autocreate yes 

proc GetAbsolutePath { dir } {
    set saved [pwd]
    cd $dir
    set path [pwd] 
    cd $saved
    return $path
}
.h entry configure root -label [file tail [GetAbsolutePath $top]] 
.h configure -bg grey90
update
regsub -all {\.\./*} [Find $top] {} fileList
.h insert end {*}$fileList
.h configure -bg white

.h find -glob -name *.gif -exec { 
     %W entry configure %n -image [image create photo -file $top/%P]
}

focus .h

set nodes [.h find -glob -name *.c]
.h entry configure {*}$nodes -labelcolor red 

cd $saved

