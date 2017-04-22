#!/usr/bin/env tclsh

namespace eval rbc {
  proc bitmap {cmd args} {
    switch -exact $cmd {
      define {
        if {[llength $args] != 2} {
          error "usage: rbc::bitmap $cmd NAME DEF"
        }
        foreach {name def} $args break
        if {[string first #define $def] != -1} {
          set     img "image create bitmap $name -data \{\n"
          foreach line [split [string trim $def] \n] {
            append  img "  [string trim $line]\n"
          }
          append  img "\}\n"
        } else {
          if {[llength $def] != 2} {
            error "usage: rbc::bitmap $cmd $name {{WIDTH HIGH} DATA}"
          }
          foreach {geo data} $def break
          if {[llength $geo] != 2} {
            error "usage: rbc::bitmap $cmd $name {{WIDTH HIGH} $data}"
          }
          foreach {width high} $geo break
          set data [lmap x $data { set x "0x$x" }]
          set     img "image create bitmap $name -data \{\n"
          append  img "  #define ${name}_width $width\n"
          append  img "  #define ${name}_height $high\n"
          append  img "  static unsigned char otto_bits\[\] = \{\n"
          while {[llength $data]} {
            append img "    [join [lrange $data 0 11] {, }]"
            set data [lrange $data 12 end]
            if {[llength $data]} {
              append img  ",\n"
            } else {
              append img  "\n"
            }
          }
          append  img "  \};\n"
          append  img "\}\n"
        }
        puts $::out $img
      }
      default {
        error "rbc::bitmap: unknown command ´$cmd'"
      }
    }
  }
}

foreach arg $argv {
  if {![file readable $arg]} {
    puts "invalid file: $arg"
    continue
  }
  set i 0
  while {[file exists $arg.$i]} {
    incr i
  }
  file rename $arg $arg.$i
  set out [open $arg w]
  source $arg.$i
}

