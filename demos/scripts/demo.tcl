# ----------------------------------------------------------------------------
#
#	The following code is solely a convenience so that you can test the 
#	RBC distribution without first installing it.
#
# ----------------------------------------------------------------------------

# If we're in the ./demos directory, we can simply specify
# "../library" as the library directory without having to install the
# files.

if { [file exists ../library/rbcGraph.pro] } {
    global rbc_library
    set rbc_library ../library
    set auto_path [linsert $auto_path 0 $rbc_library]
    auto_reset
}

# Add a binding for convenience to let you exit with pressing the
# "quit" button.

wm protocol . WM_DELETE_WINDOW { DoExit 0 }
bind all <Control-KeyPress-c> { DoExit 0 } 

proc DoExit { code } {
    destroy .
    #exit $code
}
