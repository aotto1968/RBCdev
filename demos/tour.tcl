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
option add *Scrollbar.relief	flat

#set tcl_traceExec 1

array set started {
  current.app ""
  current.cmd ""
}
proc RunDemo { program } {
    global started
    set script $program.tcl
    if {![file exists $script]} {
      puts "msg: $script is not a file"
      return
    }
    if {![info exists started($program)]} {
      set started($program) "no"
    }

    if {$started($program) == "yes" } {
      if {[catch {send "demo:$program" wm deiconify .} err]} {
        puts "send demo:$program wm deiconify . → $err"
        set started($program) "no"
      }
    }
    if {$started($program) == "no" } {
      #set cmd [list $script -name "demo:$program" -geom -4000-4000]
      set started($program.cmd) [list $script -name "demo:$program"]
      bgexec started($program.out) \
        -onoutput puts -onerror [list puts stderr] \
          [info nameofexecutable] {*}$started($program.cmd) &
      set started($program) "yes"
    }
    
    #puts stderr [.top.tab.f1 find -name "demo:$program"]

    # update the tabset
    set started(current.cmd) $started($program.cmd)
    if {[catch { .top.tab.f1 configure -name "demo:$program"} err]} {
      puts ".top.tab.f1 configure -name demo:$program → $err"
      set started($program.cmd) "no"
      return [RunDemo $program]
    }
    SeeCode $script
    SeeMan  $program

    # cleanup old app
    if {$started(current.app) != ""} {
      send -async $started(current.app) wm iconify .
    }
    set started(current.app) demo:$program
}

proc SeeCode {fn} {
  set f [open $fn r]
  set data [read $f]
  close $f

  .top.tab.c1.t delete 0.0 end
  .top.tab.c1.t insert 0.0 $data
}

proc SeeMan {pr} {
  set pr "[string trimright $pr {0123456789}].n"
  set dr [file join .. doc]
  set mp [file join $dr $pr]
  set cm [list man -7l $mp]
  if {[file exists $mp]} {
    if {[catch {exec {*}$cm |& cat} data]} {
      puts stderr $data
      set data "sorry… ´$cm´ not working"
    }
  } else {
    set data "sorry… man page ´$mp´ not found"
  }

  .top.tab.m1.t delete 0.0 end
  .top.tab.m1.t insert 0.0 $data
}


#set tcl_traceExec 1

frame .top
hierbox .top.hier -separator "." -xscrollincrement 1 \
    -yscrollcommand { .top.yscroll set } -xscrollcommand { .top.xscroll set } \
    -selectcommand { 
	set index [.top.hier curselection]
	set label [.top.hier entry cget $index -label]
	.top.title configure -text $label
	.top.tab tab configure Example -window .top.tab.f1 
        RunDemo $label
    }
	
scrollbar .top.yscroll -command { .top.hier yview }
scrollbar .top.xscroll -command { .top.hier xview } -orient horizontal
label .top.mesg -relief groove -borderwidth 2 \
  -textvariable started(current.cmd) \
    -font { Courier 12 bold }
label .top.title -text "Synopsis" -highlightthickness 0
tabset .top.tab -side bottom -relief flat -bd 0 -highlightthickness 0 \
    -pageheight 4i

.top.tab insert end \
    "Example" \
    "See Code" \
    "Manual"
 
if 0 {
image create photo dummy -file images/rbc98.gif
image create photo graph.img -width 50 -height 50
winop resample dummy graph.img box box

image create photo dummy -file images/mini-book2.gif
image create photo barchart.img -width 50 -height 50
winop resample dummy barchart.img box box
}

.top.hier entry configure root -label "RBC"
.top.hier insert end \
    "Plotting" \
    "Plotting.graph" \
    "Plotting.graph.graph1" \
    "Plotting.graph.graph2" \
    "Plotting.graph.graph3" \
    "Plotting.graph.graph4" \
    "Plotting.graph.graph5" \
    "Plotting.graph.graph6" \
    "Plotting.graph.graph7" \
    \
    "Plotting.barchart" \
    "Plotting.barchart.barchart1" \
    "Plotting.barchart.barchart2" \
    "Plotting.barchart.barchart3" \
    "Plotting.barchart.barchart4" \
    "Plotting.barchart.barchart5" \
    \
    "Plotting.stripchart1" \
    "Plotting.spline1" \
    \
    "Composition" \
    "Composition.htext1" \
    "Composition.tabset" \
    "Composition.tabset.tabset1" \
    "Composition.tabset.tabset2" \
    "Composition.tabset.tabset3" \
    "Composition.tabset.tabset4" \
    \
    "Composition.hiertable" \
    "Composition.hiertable.hiertable1" \
    "Composition.hiertable.hiertable2" \
    "Composition.hiertable.hiertable3" \
    \
    "Composition.hierbox" \
    "Composition.hierbox.hierbox1" \
    "Composition.hierbox.hierbox2" \
    "Composition.hierbox.hierbox3" \
    "Composition.hierbox.hierbox4" \
    \
    "Composition.container" \
    "Composition.container.container1" \
    "Composition.container.container2" \
    \
    "Composition.treeview" \
    "Composition.treeview.treeview1" \
    \
    "Composition.tabnotebook" \
    "Composition.tabnotebook.tabnotebook1" \
    "Composition.tabnotebook.tabnotebook2" \
    "Composition.tabnotebook.tabnotebook3" \
    \
    "Miscellaneous" \
    "Miscellaneous.bgexec" \
    "Miscellaneous.bgexec.bgexec1" \
    "Miscellaneous.bgexec.bgexec2" \
    "Miscellaneous.bgexec.bgexec3" \
    "Miscellaneous.bgexec.bgexec4" \
    "Miscellaneous.bgexec.bgexec5" \
    \
    "Miscellaneous.bitmap" \
    "Miscellaneous.bitmap.bitmap1" \
    "Miscellaneous.bitmap.bitmap2" 

option add *Hierbox.labelFont {*-helvetica*-bold-r-*-14-*}

# configure the nodes (directories)
.top.hier open -r root
.top.hier entry configure root -labelfont *-helvetica*-bold-r-*-18-* \
    -labelcolor red -labelshadow red3

.top.hier entry configure "Plotting" "Composition" "Miscellaneous" \
    -labelcolor blue4 -labelshadow blue2 \
      -labelfont {*-helvetica*-bold-r-*-14-*}

.top.hier entry configure \
    "Plotting.graph" "Plotting.barchart" "Composition.tabset" \
    "Composition.hiertable" "Composition.hierbox" "Composition.container" \
    "Composition.treeview" "Composition.tabnotebook" "Miscellaneous.bgexec" \
    "Miscellaneous.bitmap" \
      -labelcolor green4 -labelshadow green2 \
        -labelfont {*-helvetica*-bold-r-*-12-*}

.top.hier entry configure "Plotting.graph" \
    -label "X-Y Graph" 
.top.hier entry configure "Plotting.barchart" \
    -label "Bar Chart"

# pack the widgets
table .top \
    0,0 .top.hier -fill both -rspan 2 \
    0,1 .top.yscroll -fill y -rspan 2 \
    0,2 .top.mesg -padx 2 -pady { 8 2 } -fill both \
    0,2 .top.title -anchor nw -padx { 8 8 }  \
    1,2 .top.tab -fill both -rspan 2 \
    2,0 .top.xscroll -fill x 

table configure .top c0 c1 r0 r2 -resize none
table configure .top c0 -width { 3i {} }
table configure .top c2 -width { 4i {} }
table . \
    .top -fill both

proc DoExit { code } {
    global progStatus
    set progStatus 1
    exit $code
}

# demo application
container .top.tab.f1 -relief raised -bd 2 -takefocus 0
.top.tab tab configure "Example" -window .top.tab.f1 -fill both

# source code
frame .top.tab.c1 -relief raised -bd 2 -takefocus 0
text  .top.tab.c1.t -yscrollcommand {.top.tab.c1.s set} \
        -font { Courier 10 bold }
scrollbar .top.tab.c1.s -command        {.top.tab.c1.t yview}
pack .top.tab.c1.s -side right -fill y
pack .top.tab.c1.t -side left -fill both -expand 1
.top.tab tab configure "See Code" -window .top.tab.c1 -fill both

# man pages
frame .top.tab.m1 -relief raised -bd 2 -takefocus 0
text  .top.tab.m1.t -yscrollcommand {.top.tab.c1.s set} \
        -font { Courier 10 bold }
scrollbar .top.tab.m1.s -command        {.top.tab.c1.t yview}
pack .top.tab.m1.s -side right -fill y
pack .top.tab.m1.t -side left -fill both -expand 1
.top.tab tab configure "Manual" -window .top.tab.m1 -fill both

#container .top.tab.m1 -relief raised -bd 2 -takefocus 0
#.top.tab tab configure Example -window .top.tab.f1 -fill both

if 0 {
    set cmd "xterm -fn fixed -geom +4000+4000"
    eval bgexec programInfo(xterm) $cmd &
    set programInfo(lastProgram) xterm
    .top.tab.f1 configure -command $cmd 
} 
wm protocol . WM_DELETE_WINDOW { destroy . }
