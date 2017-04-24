#!/usr/bin/env tclsh

set ret [list]
foreach item [ exec make -s depend "DEPENDTARGET=-f-" ] {

  if {[string index $item end] == ":"} continue
  if {![file exists $item]} continue
  set item [file normalize $item]
  lappend ret $item
}

puts [lsort -unique $ret]

