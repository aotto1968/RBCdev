#
# dnd.tcl
#
# ----------------------------------------------------------------------
# Bindings for the RBC drag&drop command
# ----------------------------------------------------------------------
#   AUTHOR:  George Howlett
#            Bell Labs Innovations for Lucent Technologies
#            gah@bell-labs.com
#            http://www.tcltk.com/rbc
# ----------------------------------------------------------------------
# Copyright (c) 1998  Lucent Technologies, Inc.
# ======================================================================
#
# Permission to use, copy, modify, and distribute this software and its
# documentation for any purpose and without fee is hereby granted,
# provided that the above copyright notice appear in all copies and that
# both that the copyright notice and warranty disclaimer appear in
# supporting documentation, and that the names of Lucent Technologies
# any of their entities not be used in advertising or publicity
# pertaining to distribution of the software without specific, written
# prior permission.
#
# Lucent Technologies disclaims all warranties with regard to this
# software, including all implied warranties of merchantability and
# fitness.  In no event shall Lucent be liable for any special, indirect
# or consequential damages or any damages whatsoever resulting from loss
# of use, data or profits, whether in an action of contract, negligence
# or other tortuous action, arising out of or in connection with the use
# or performance of this software.
#
# ======================================================================

set cmd rbc::dnd
for { set i 1 } { $i <= 5 } { incr i } {
    bind RbcDndButton$i <ButtonPress-$i>  [list $cmd select %W %X %Y %t]
    bind RbcDndButton$i <B$i-Motion>	  [list $cmd drag %W %X %Y]
    bind RbcDndButton$i <ButtonRelease-$i> [list $cmd drop %W %X %Y]
}

# ----------------------------------------------------------------------
#
# DndInit --
#
#	Invoked from C whenever a new drag&drop source is created.
#	Sets up the default bindings for the drag&drop source.
#
#	<ButtonPress-?>	 Starts the drag operation.
#	<B?-Motion>	 Updates the drag.
#	<ButtonRelease-?> Drop the data on the target.
#
# Arguments:	
#	widget		source widget
#	button		Mouse button used to activate drag.
#	cmd		"dragdrop" or "rbc::dragdrop"
#
# ----------------------------------------------------------------------

proc rbc::DndInit { widget button } {
    set tagList {}
    if { $button > 0 } {
	lappend tagList RbcDndButton$button
    }
    foreach tag [bindtags $widget] {
	if { ![string match RbcDndButton* $tag] } {
	    lappend tagList $tag
	}
    }
    bindtags $widget $tagList
}

proc rbc::DndStdDrop { widget args } {
    array set info $args
    set fmt [lindex $info(formats) 0]
    dnd pull $widget $fmt 
    return 0
}

proc rbc::PrintInfo { array } {
    upvar $array state

    parray state
    if { $info(state) & 0x01 } {
	puts "Shift-Drop"
    }
    if { $info(state) & 0x02 } {
	puts "CapsLock-Drop"
    }
    if { $info(state) & 0x04 } {
	puts "Control-Drop"
    }
    if { $info(state) & 0x08 } {
	puts "Alt-Drop"
    }
    if { $info(state) & 0x10 } {
	puts "NumLock-Drop"
    }
}
