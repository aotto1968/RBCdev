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

option add *graph.Element.ScaleSymbols true

# test to show spline over-shooting

set tcl_precision 15

# Make and fill small vectors
vector x y
x seq 10 0 -0.5 
y expr sin(x^3)
x expr x*x
x sort y
vector x2 y1 y2 y3

# make and fill (x only) large vectors
x populate x2 10

# natural spline interpolation
spline natural x y x2 y1

# quadratic spline interpolation
spline quadratic x y x2 y2 

# make plot
graph .graph 
.graph xaxis configure -title "x^2" 
.graph yaxis configure -title "sin(y^3)"

.graph pen configure activeLine -pixels 5
.graph element create Original -x x -y y \
    -color red4 \
    -fill red \
    -pixels 5 \
    -symbol circle

.graph element create Natural -x x2 -y y1 \
    -color green4 \
    -fill green \
    -pixels 3 \
    -symbol triangle

.graph element create Quadratic -x x2 -y y2 \
    -color blue4 \
    -fill orange2 \
    -pixels 3 \
    -symbol arrow

table . .graph -fill both

Rbc_ZoomStack .graph
Rbc_Crosshairs .graph
Rbc_ActiveLegend .graph
Rbc_ClosestPoint .graph
Rbc_PrintKey .graph

.graph grid on
