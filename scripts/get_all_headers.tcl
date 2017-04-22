#!/usr/bin/env tclsh

set ret [list]
foreach item \
  [exec makedepend -f- \
    -I/usr/lib64/gcc/x86_64-suse-linux/4.8/include \
      -I/usr/lib64/gcc/x86_64-suse-linux/4.8/include-fixed \
        -I../tk8.6.6/generic/ \
          -I../tcl8.6.6/generic/ \
            {*}[glob generic/*.c]] {

  if {[string index $item end] == ":"} continue
  if {![file exists $item]} continue
  set item [file normalize $item]
  lappend ret $item
}

puts [lsort -unique $ret]

