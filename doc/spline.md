

NAME
====

spline \-  Fit curves with spline interpolation  

SYNOPSIS
========

__spline natural__ *x* *y* *sx* *sy*  

__spline quadratic__ *x* *y* *sx* *sy*  

DESCRIPTION
===========

The __spline__ command computes a spline fitting a set of data points (x
and y vectors) and produces a vector of the interpolated images (y\-
coordinates) at a given set of x\-coordinates\.  

INTRODUCTION
============

Curve fitting has many applications\.  In graphs, curve fitting can be
useful for displaying curves which are aesthetically pleasing to the
eye\.  Another advantage is that you can quickly generate arbitrary
points on the curve from a small set of data points\.  

A spline is a device used in drafting to produce smoothed curves\.  The
points of the curve, known as *knots*, are fixed and the *spline*,
typically a thin strip of wood or metal, is bent around the knots to
create the smoothed curve\.  Spline interpolation is the mathematical
equivalent\.  The curves between adjacent knots are piecewise functions
such that the resulting spline runs exactly through all the knots\.  The
order and coefficients of the polynominal determine the "looseness" or
"tightness" of the curve fit from the line segments formed by the
knots\.  

The __spline__ command performs spline interpolation using cubic
("natural") or quadratic polynomial functions\.  It computes the spline
based upon the knots, which are given as x and y vectors\.  The
interpolated new points are determined by another vector which
represents the abscissas (x\-coordinates) or the new points\.  The
ordinates (y\-coordinates) are interpolated using the spline and written
to another vector\.  

EXAMPLE
=======

Before we can use the __spline__ command, we need to create two RBC vectors
which will represent the knots (x and y coordinates) of the data that
we\'re going to fit\.  Obviously, both vectors must be the same length\.

~~~~~
# Create sample data of ten points.
vector x(10) y(10)

for {set i 10} {$i > 0} {incr i -1} {
    set x($i-1) [expr $i*$i]
    set y($i-1) [expr sin($i*$i*$i)]
}
~~~~~

We now have two vectors x and y representing the ten data points we\'re
trying to fit\.  The order of the values of x must be monotonically
increasing\.  We can use the vector\'s __sort__ operation to sort the
vectors\.  

~~~~~
x sort y
~~~~~

The components of x are sorted in increasing order\.  The components of
y are rearranged so that the original x,y coordinate pairings are
retained\.  

A third vector is needed to indicate the abscissas (x\-coordinates) of
the new points to be interpolated by the spline\.  Like the x vector,
the vector of abscissas must be monotonically increasing\.  All the
abscissas must lie between the first and last knots (x vector) forming
the spline\.  

How the abscissas are picked is arbitrary\.  But if we are going to plot
the spline, we will want to include the knots too\.  Since both the
quadratic and natural splines preserve the knots (an abscissa from the
x vector will always produce the corresponding ordinate from the y
vector), we can simply make the new vector a superset of x\.  It will
contain the same coordinates as x, but also the abscissas of the new
points we want interpolated\.  A simple way is to use the vector\'s
__populate__ operation\.  

~~~~~
x populate sx 10
~~~~~

This creates a new vector sx\.  It contains the abscissas of x, but in
addition sx will have ten evenly distributed values between each
abscissa\.  You can interpolate any points you wish, simply by setting
the vector values\.  

Finally, we generate the ordinates (the images of the spline) using the
__spline__ command\.  The ordinates are stored in a fourth vector\.

~~~~~
spline natural x y sx sy
~~~~~

This creates a new vector sy\.  It will have the same length as sx\.  The
vectors sx and sy represent the smoothed curve which we can now plot\.

~~~~~
graph .graph
.graph element create original -x x -y x -color blue
.graph element create spline -x sx -y sy -color red
table . .graph
~~~~~

The __natural__ operation employs a cubic interpolant when forming the
spline\.  In terms of the draftmen\'s spline, a *natural* *spline* requires
the least amount of energy to bend the spline (strip of wood), while
still passing through each knot\.  In mathematical terms, the second
derivatives of the first and last points are zero\.  

Alternatively, you can generate a spline using the __quadratic__ operation\.
Quadratic interpolation produces a spline which follows the line
segments of the data points much more closely\.  

~~~~~
spline quadratic x y sx sy
~~~~~

OPERATIONS
==========


spline natural *x* *y* *sx* *sy*
:   Computes a cubic spline from the data points represented by the
    vectors *x* and *y* and interpolates new points using vector *sx* as
    the x\-coordinates\.  The resulting y\-coordinates are written to a
    new vector *sy*\. The vectors *x* and *y* must be the same length and
    contain at least three components\.  The order of the components
    of *x* must be monotonically increasing\.  *Sx* is the vector
    containing the x\-coordinates of the points to be interpolated\.
    No component of *sx* can be less than first component of *x* or
    greater than the last component\.  The order of the components of
    *sx* must be monotonically increasing\.  *Sy* is the name of the
    vector where the calculated y\-coordinates will be stored\.  If *sy*
    does not already exist, a new vector will be created\.

spline quadratic *x* *y* *sx* *sy*
:   Computes a quadratic spline from the data points represented by
    the vectors *x* and *y* and interpolates new points using vector *sx*
    as the x\-coordinates\.  The resulting y\-coordinates are written
    to a new vector *sy*\.  The vectors *x* and *y* must be the same length
    and contain at least three components\.  The order of the
    components of *x* must be monotonically increasing\.  *Sx* is the
    vector containing the x\-coordinates of the points to be
    interpolated\. No component of *sx* can be less than first
    component of *x* or greater than the last component\.  The order of
    the components of *sx* must be monotonically increasing\.  *Sy* is
    the name of the vector where the calculated y\-coordinates are
    stored\.  If *sy* does not already exist, a new vector will be
    created\.  

REFERENCES
==========

Numerical Analysis  
by R\. Burden, J\. Faires and A\. Reynolds\.  
Prindle, Weber & Schmidt, 1981, pp\. 112  

Shape Preserving Quadratic Splines  
by D\.F\.Mcallister & J\.A\.Roulier  
Coded by S\.L\.Dodd & M\.Roulier N\.C\.State University\.  

The original code for the quadratric spline can be found in TOMS #574\.

KEYWORDS
========

spline, vector, graph  

