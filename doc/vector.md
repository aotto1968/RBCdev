

NAME
====

vector \-  Vector data type for Tcl  

SYNOPSIS
========

__vector create__ *vecName* ?*vecName*\.\.\.? ?*switches*?  

__vector destroy__ *vecName* ?*vecName*\.\.\.?  

__vector expr__ *expression*  

__vector names__ ?*pattern*\.\.\.?  

DESCRIPTION
===========

The __vector__ command creates a vector of floating point values\.  The
vector\'s components can be manipulated in three ways: through a Tcl
array variable, a Tcl command, or the C API\.  

INTRODUCTION
============

A vector is simply an ordered set of numbers\.  The components of a
vector are real numbers, indexed by counting numbers\.

Vectors are common data structures for many applications\.  For example,
a graph may use two vectors to represent the X\-Y coordinates of the
data plotted\.  The graph will automatically be redrawn when the vectors
are updated or changed\. By using vectors, you can separate data
analysis from the graph widget\.  This makes it easier, for example, to
add data transformations, such as splines\.  It\'s possible to plot the
same data to in multiple graphs, where each graph presents a different
view or scale of the data\.  

You could try to use Tcl\'s associative arrays as vectors\.  Tcl arrays
are easy to use\.  You can access individual elements randomly by
specifying the index, or the set the entire array by providing a list
of index and value pairs for each element\.  The disadvantages of
associative arrays as vectors lie in the fact they are implemented as
hash tables\.  

*   There\'s no implied ordering to the associative arrays\.  If you used
    vectors for plotting, you would want to insure the second component
    comes after the first, an so on\.  This isn\'t possible since arrays
    are actually hash tables\.  For example, you can\'t get a range of
    values between two indices\.  Nor can you sort an array\.

*   Arrays consume lots of memory when the number of elements becomes
    large (tens of thousands)\.  This is because each element\'s index and
    value are stored as strings in the hash table\.  

*   The C programming interface is unwieldy\.  Normally with vectors, you
    would like to view the Tcl array as you do a C array, as an array of
    floats or doubles\.  But with hash tables, you must convert both the
    index and value to and from decimal strings, just to access an
    element in the array\.  This makes it cumbersome to perform operations
    on the array as a whole\.  

The __vector__ command tries to overcome these disadvantages while still
retaining the ease of use of Tcl arrays\.  The __vector__ command creates
both a new Tcl command and associate array which are linked to the
vector components\.  You can randomly access vector components though
the elements of array\.  Not have all indices are generated for the
array, so printing the array (using the __parray__ procedure) does not
print out all the component values\.  You can use the Tcl command to
access the array as a whole\.  You can copy, append, or sort vector
using its command\.  If you need greater performance, or customized
behavior, you can write your own C code to manage vectors\.

EXAMPLE
=======

You create vectors using the __vector__ command and its __create__ operation\.

~~~~~
# Create a new vector.
vector create y(50)
~~~~~

This creates a new vector named y\.  It has fifty components, by
default, initialized to 0\.0\.  In addition, both a Tcl command and array
variable, both named y, are created\.  You can use either the command or
variable to query or modify components of the vector\.

~~~~~
# Set the first value.
set y(0) 9.25
puts "y has [y length] components"
~~~~~

The array y can be used to read or set individual components of the
vector\.  Vector components are indexed from zero\.  The array index must
be a number less than the number of components\.  For example, it\'s an
error if you try to set the 51st element of y\.  

~~~~~
# This is an error. The vector only has 50 components.
set y(50) 0.02
~~~~~

You can also specify a range of indices using a colon (:) to separate
the first and last indices of the range\.  

~~~~~
# Set the first six components of y
set y(0:5) 25.2
~~~~~

If you don\'t include an index, then it will default to the first and/or
last component of the vector\.  

~~~~~
# Print out all the components of y
puts "y = $y(:)"
~~~~~

There are special non\-numeric indices\.  The index end, specifies the
last component of the vector\.  It\'s an error to use this index if the
vector is empty (length is zero)\.  The index ++end can be used to
extend the vector by one component and initialize it to a specific
value\.  You can\'t read from the array using this index, though\.

~~~~~
# Extend the vector by one component.
set y(++end) 0.02
~~~~~

The other special indices are min and max\.  They return the current
smallest and largest components of the vector\.  

~~~~~
# Print the bounds of the vector
puts "min=$y(min) max=$y(max)"
~~~~~

To delete components from a vector, simply unset the corresponding
array element\. In the following example, the first component of y is
deleted\.  All the remaining components of y will be moved down by one
index as the length of the vector is reduced by one\.  

~~~~~
# Delete the first component
unset y(0)
puts "new first element is $y(0)"
~~~~~

The vector\'s Tcl command can also be used to query or set the vector\.

~~~~~
# Create and set the components of a new vector
vector create x
x set { 0.02 0.04 0.06 0.08 0.10 0.12 0.14 0.16 0.18 0.20 }
~~~~~

Here we\'ve created a vector x without a initial length specification\.
In this case, the length is zero\.  The __set__ operation resets the vector,
extending it and setting values for each new component\.

There are several operations for vectors\.  The __range__ operation lists
the components of a vector between two indices\.  

~~~~~
# List the components
puts "x = [x range 0 end]"
~~~~~

You can search for a particular value using the __search__ operation\.  It
returns a list of indices of the components with the same value\.  If no
component has the same value, it returns ""\.  

~~~~~
# Find the index of the biggest component
set indices [x search $x(max)]
~~~~~

Other operations copy, append, or sort vectors\.  You can append vectors
or new values onto an existing vector with the __append__ operation\.

~~~~~
# Append assorted vectors and values to x
x append x2 x3 { 2.3 4.5 } x4
~~~~~

The __sort__ operation sorts the vector\.  If any additional vectors are
specified, they are rearranged in the same order as the vector\.  For
example, you could use it to sort data points represented by x and y
vectors\.  

~~~~~
# Sort the data points
x sort y
~~~~~

The vector x is sorted while the components of y are rearranged so that
the original x,y coordinate pairs are retained\.  

The __expr__ operation lets you perform arithmetic on vectors\.  The result
is stored in the vector\.  

~~~~~
# Add the two vectors and a scalar
x expr { x + y }
x expr { x * 2 }
~~~~~

When a vector is modified, resized, or deleted, it may trigger call\-
backs to notify the clients of the vector\.  For example, when a vector
used in the __graph__ widget is updated, the vector automatically notifies
the widget that it has changed\.  The graph can then redrawn itself at
the next idle point\.  By default, the notification occurs when Tk is
next idle\.  This way you can modify the vector many times without
incurring the penalty of the graph redrawing itself for each change\.
You can change this behavior using the __notify__ operation\.

~~~~~
# Make vector x notify after every change
x notify always
  ...
# Never notify
x notify never
  ...
# Force notification now
x notify now
~~~~~

To delete a vector, use the __vector delete__ command\.  Both the vector and
its corresponding Tcl command are destroyed\.  

~~~~~
# Remove vector x
vector destroy x
~~~~~

SYNTAX
======

Vectors are created using the __vector create__ operation\.  Th __create__
operation can be invoked in one of three forms:  

vector create *vecName*
:   This creates a new vector *vecName* which initially has no
    components\.  

vector create *vecName*(*size*)
:   This second form creates a new vector which will contain *size*
    number of components\.  The components will be indexed starting
    from zero (0)\. The default value for the components is 0\.0\.

vector create *vecName*(*first*:*last*)
:   The last form creates a new vector of indexed *first* through
    *last*\.  *First* and *last* can be any integer value so long as *first*
    is less than *last*\.  

Vector names must start with a letter and consist of letters, digits,
or underscores\.  

~~~~~
# Error: must start with letter
vector create 1abc
~~~~~

You can automatically generate vector names using the "#auto" vector

name\.
:   The __create__ operation will generate a unique vector name\.

    set vec \[vector create #auto\]  
    puts "\$vec has \[\$vec length\] components"  

VECTOR INDICES
--------------

Vectors are indexed by integers\.  You can access the individual vector
components via its array variable or Tcl command\.  The string
representing the index can be an integer, a numeric expression, a
range, or a special keyword\.  

The index must lie within the current range of the vector, otherwise an
an error message is returned\.  Normally the indices of a vector are
start from 0\.  But you can use the __offset__ operation to change a
vector\'s indices on\-the\-fly\.  

~~~~~
puts $vecName(0)
vecName offset -5
puts $vecName(-5)
~~~~~

You can also use numeric expressions as indices\.  The result of the
expression must be an integer value\.  

~~~~~
set n 21
set vecName($n+3) 50.2
~~~~~

The following special non\-numeric indices are available: min, max, end,
and ++end\.  

~~~~~
puts "min = $vecName($min)"
set vecName(end) -1.2
~~~~~

The indices min and max will return the minimum and maximum values of
the vector\.  The index end returns the value of the last component in
the vector\.  The index ++end is used to append new value onto the
vector\.  It automatically extends the vector by one component and sets
its value\.  

~~~~~
# Append an new component to the end
set vecName(++end) 3.2
~~~~~

A range of indices can be indicated by a colon (:)\.  

~~~~~
# Set the first six components to 1.0
set vecName(0:5) 1.0
~~~~~

If no index is supplied the first or last component is assumed\.

~~~~~
# Print the values of all the components
puts $vecName(:)
~~~~~

VECTOR OPERATIONS
=================


__vector create__ *vecName*?(*size*)?\.\.\. ?*switches*?

:   The __create__ operation creates a new vector *vecName*\.  Both a Tcl
    command and array variable *vecName* are also created\.  The name
    *vecName* must be unique, so another Tcl command or array variable
    can not already exist in that scope\.  You can access the
    components of the vector using its variable\.  If you change a
    value in the array, or unset an array element, the vector is
    updated to reflect the changes\.  When the variable *vecName* is
    unset, the vector and its Tcl command are also destroyed\.

    The vector has optional switches that affect how the vector is
    created\. They are as follows:  

    \-variable *varName*
    :   Specifies the name of a Tcl variable to be mapped to the
        vector\. If the variable already exists, it is first
        deleted, then recreated\.  If *varName* is the empty string,
        then no variable will be mapped\.  You can always map a
        variable back to the vector using the vector\'s __variable__
        operation\.  

    \-command *cmdName*
    :   Maps a Tcl command to the vector\. The vector can be
        accessed using *cmdName* and one of the vector instance
        operations\.  A Tcl command by that name cannot already
        exist\.  If *cmdName* is the empty string, no command
        mapping will be made\.  

    \-watchunset *boolean*
    :   Indicates that the vector should automatically delete
        itself if the variable associated with the vector is
        unset\.  By default, the vector will not be deleted\.  This
        is different from previous releases\.  Set *boolean* to
        "true" to get the old behavior\.  

__vector destroy__ *vecName* ?*vecName\.\.\.*?

: …

__vector expr__ *expression*

:   All binary operators take vectors as operands (remember that
    numbers are treated as one\-component vectors)\.  The exact action
    of binary operators depends upon the length of the second
    operand\.  If the second operand has only one component, then
    each element of the first vector operand is computed by that
    value\.  For example, the expression "x \* 2" multiples all
    elements of the vector x by 2\.  If the second operand has more
    than one component, both operands must be the same length\.  Each
    pair of corresponding elements are computed\.  So "x + y" adds
    the the first components of x and y together, the second, and so
    on\.  

    The valid operators are listed below, grouped in decreasing
    order of precedence:  

    \-  \!
    :   Unary minus and logical NOT\.  The unary
        minus flips the sign of each component in
        the vector\.  The logical not operator
        returns a vector of whose values are 0\.0 or
        1\.0\.  For each non\-zero component 1\.0 is
        returned, 0\.0 otherwise\.  

    ^
    :   Exponentiation\.

    \*  /  %
    :   Multiply, divide, remainder\.

    +  \-
    :   Add and subtract\.

    \<\<  \>\>
    :   Left and right shift\.  Circularly shifts the
        values of the vector (not implemented yet)\.

    \<  \>  \<=  \>=
    :   Boolean less, greater, less than or equal,
        and greater than or equal\.  Each operator
        returns a vector of ones and zeros\.  If the
        condition is true, 1\.0 is the component
        value, 0\.0 otherwise\.  

    ==  \!=
    :   Boolean equal and not equal\.  Each operator
        returns a vector of ones and zeros\.  If the
        condition is true, 1\.0 is the component
        value, 0\.0 otherwise\.  

    |
    :   Bit\-wise OR\.  (Not implemented)\.

    &&
    :   Logical AND\.  Produces a 1 result if both
        operands are non\-zero, 0 otherwise\.

    ||
    :   Logical OR\.  Produces a 0 result if both
        operands are zero, 1 otherwise\.

    *x*?*y*:*z*
    :   If\-then\-else, as in C\.  (Not implemented
        yet)\.  

    See the C manual for more details on the results produced by
    each operator\.  All of the binary operators group left\-to\-right
    within the same precedence level\.  

    Several mathematical functions are supported for vectors\.  Each
    of the following functions invokes the math library function of
    the same name; see the manual entries for the library functions
    for details on what they do\.  The operation is applied to all
    elements of the vector returning the results\.  

    acos
    :   __cos         hypot      sinh__

    asin
    :   __cosh        log        sqrt__

    atan
    :   __exp         log10      tan__

    ceil
    :   __floor       sin        tanh__

    Additional functions are:  

    abs
    :   Returns the absolute value of each component\.

    random
    :   Returns a vector of non\-negative values uniformly
        distributed between \[0\.0, 1\.0) using *drand48*\.  The
        seed comes from the internal clock of the machine or
        may be set manual with the srandom function\.

    round
    :   Rounds each component of the vector\.

    srandom
    :   Initializes the random number generator using *srand48*\.
        The high order 32\-bits are set using the integral
        portion of the first vector component\. All other
        components are ignored\.  The low order 16\-bits are set
        to an arbitrary value\.  

    The following functions return a single value\.

    adev
    :   Returns the average deviation (defined as the sum of
        the absolute values of the differences between
        component and the mean, divided by the length of the
        vector)\.  

    kurtosis
    :   Returns the degree of peakedness (fourth moment) of
        the vector\.  

    length
    :   Returns the number of components in the vector\.

    max
    :   Returns the vector\'s maximum value\.

    mean
    :   Returns the mean value of the vector\.

    median
    :   Returns the median of the vector\.

    min
    :   Returns the vector\'s minimum value\.

    q1
    :   Returns the first quartile of the vector\.

    q3
    :   Returns the third quartile of the vector\.

    prod
    :   Returns the product of the components\.

    sdev
    :   Returns the standard deviation (defined as the square
        root of the variance) of the vector\.

    skew
    :   Returns the skewness (or third moment) of the vector\.
        This characterizes the degree of asymmetry of the
        vector about the mean\.  

    sum
    :   Returns the sum of the components\.

    var
    :   Returns the variance of the vector\. The sum of the
        squared differences between each component and the
        mean is computed\.  The variance is the sum divided by
        the length of the vector minus 1\.  

    The last set returns a vector of the same length as the
    argument\.  

    norm
    :   Scales the values of the vector to lie in the range
        \[0\.0\.\.1\.0\]\.  

    sort
    :   Returns the vector components sorted in ascending
        order\.  

__vector names__ ?*pattern*?

: …

INSTANCE OPERATIONS
===================

You can also use the vector\'s Tcl command to query or modify it\.  The
general form is *vecName* *operation* ?*arg*?\.\.\.  Both *operation* and its
arguments determine the exact behavior of the command\.  The operations
available for vectors are listed below\.  

*vecName* __append__ *item* ?*item*?\.\.\.

:   Appends the component values from *item* to *vecName*\.  *Item* can be
    either the name of a vector or a list of numeric values\.

*vecName* __binread__ *channel* ?*length*? ?*switches*?

:   Reads binary values from a Tcl channel\. Values are either
    appended to the end of the vector or placed at a given index
    (using the __\-at__ option), overwriting existing values\.  Data is
    read until EOF is found on the channel or a specified number of
    values *length* are read (note that this is not necessarily the
    same as the number of bytes)\. The following switches are
    supported:  

    \-swap
    :   Swap bytes and words\.  The default endian is the host
        machine\.  

    \-at *index*
    :   New values will start at vector index *index*\.  This will
        overwrite any current values\.  

    \-format *format*
    :   Specifies the format of the data\.  *Format* can be one of
        the following: "i1", "i2", "i4", "i8", "u1, "u2", "u4",
        "u8", "r4", "r8", or "r16"\.  The number indicates the
        number of bytes required for each value\.  The letter
        indicates the type: "i" for signed, "u" for unsigned, "r"
        or real\.  The default format is "r16"\.  

*vecName* __clear__

:   Clears the element indices from the array variable associated
    with *vecName*\.  This doesn\'t affect the components of the vector\.
    By default, the number of entries in the Tcl array doesn\'t match
    the number of components in the vector\.  This is because its too
    expensive to maintain decimal strings for both the index and
    value for each component\.  Instead, the index and value are
    saved only when you read or write an element with a new index\.
    This command removes the index and value strings from the array\.
    This is useful when the vector is large\.  

*vecName* __delete__ *index* ?*index*?\.\.\.

:   Deletes the *index*th component from the vector *vecName*\.  *Index* is
    the index of the element to be deleted\.  This is the same as
    unsetting the array variable element *index*\.  The vector is
    compacted after all the indices have been deleted\.

*vecName* __dup__ *destName*

:   Copies *vecName* to *destName*\. *DestName* is the name of a
    destination vector\.  If a vector *destName* already exists, it is
    overwritten with the components of *vecName*\.  Otherwise a new
    vector is created\.  

*vecName* __expr__ *expression*

:   Computes the expression and resets the values of the vector
    accordingly\.  Both scalar and vector math operations are
    allowed\.  All values in expressions are either real numbers or
    names of vectors\.  All numbers are treated as one component
    vectors\.  

*vecName* __length__ ?*newSize*?

:   Queries or resets the number of components in *vecName*\.  *NewSize*
    is a number specifying the new size of the vector\.  If *newSize*
    is smaller than the current size of *vecName*, *vecName* is
    truncated\.  If *newSize* is greater, the vector is extended and
    the new components are initialized to 0\.0\.  If no *newSize*
    argument is present, the current length of the vector is
    returned\.  

*vecName* __merge__ *srcName* ?*srcName*?\.\.\.

:   Merges the named vectors into a single vector\.  The resulting
    vector is formed by merging the components of each source vector
    one index at a time\.  

*vecName* __notify__ *keyword*

:   Controls how vector clients are notified of changes to the
    vector\.  The exact behavior is determined by *keyword*\.

    always
    :   Indicates that clients are to be notified immediately
        whenever the vector is updated\.  

    never
    :   Indicates that no clients are to be notified\.

    whenidle
    :   Indicates that clients are to be notified at the next
        idle point whenever the vector is updated\.

    now
    :   If any client notifications is currently pending, they
        are notified immediately\.  

    cancel
    :   Cancels pending notifications of clients using the
        vector\.  

    pending
    :   Returns 1 if a client notification is pending, and 0
        otherwise\.  

*vecName* __offset__ ?*value*?

:   Shifts the indices of the vector by the amount specified by
    *value*\.  *Value* is an integer number\.  If no *value* argument is
    given, the current offset is returned\.  

*vecName* __populate__ *destName* ?*density*?

:   Creates a vector *destName* which is a superset of *vecName*\.
    *DestName* will include all the components of *vecName*, in addition
    the interval between each of the original components will
    contain a *density* number of new components, whose values are
    evenly distributed between the original components values\.  This
    is useful for generating abscissas to be interpolated along a
    spline\.  

*vecName* __range__ *firstIndex* ?*lastIndex*?\.\.\.

:   Returns a list of numeric values representing the vector
    components between two indices\. Both *firstIndex* and *lastIndex*
    are indices representing the range of components to be returned\.
    If *lastIndex* is less than *firstIndex*, the components are listed
    in reverse order\.  

*vecName* __search__ *value* ?*value*?

:   Searches for a value or range of values among the components of
    *vecName*\.  If one *value* argument is given, a list of indices of
    the components which equal *value* is returned\.  If a second *value*
    is also provided, then the indices of all components which lie
    within the range of the two values are returned\.  If no
    components are found, then "" is returned\.  

*vecName* __set__ *item*

:   Resets the components of the vector to *item*\. *Item* can be either
    a list of numeric expressions or another vector\.

*vecName* __seq__ *start* ?*finish*? ?*step*?

:   Generates a sequence of values starting with the value *start*\.
    *Finish* indicates the terminating value of the sequence\.  The
    vector is automatically resized to contain just the sequence\.
    If three arguments are present, *step* designates the interval\.

    With only two arguments (no *finish* argument), the sequence will
    continue until the vector is filled\.  With one argument, the
    interval defaults to 1\.0\.  

*vecName* __sort__ ?__\-reverse__? ?*argName*?\.\.\.

:   Sorts the vector *vecName* in increasing order\.  If the __\-reverse__
    flag is present, the vector is sorted in decreasing order\.  If
    other arguments *argName* are present, they are the names of
    vectors which will be rearranged in the same manner as *vecName*\.
    Each vector must be the same length as *vecName*\.  You could use
    this to sort the x vector of a graph, while still retaining the
    same x,y coordinate pairs in a y vector\.  

*vecName* __variable__ *varName*

:   Maps a Tcl variable to the vector, creating another means for
    accessing the vector\.  The variable *varName* can\'t already exist\.
    This overrides any current variable mapping the vector may have\.

C LANGUAGE API
==============

You can create, modify, and destroy vectors from C code, using library

routines\.
:   You need to include the header file rbc\.h\. It contains the

definition
:   of the structure __Rbc\_Vector__, which represents the vector\.

It appears
:   below\.

~~~~~
typedef struct {
    double *valueArr;
    int numValues;
    int arraySize;
    double min, max;
} Rbc_Vector;
~~~~~

The field *valueArr* points to memory holding the vector components\.  The
components are stored in a double precision array, whose size size is
represented by *arraySize*\.  *NumValues* is the length of vector\.  The size
of the array is always equal to or larger than the length of the
vector\.  *Min* and *max* are minimum and maximum component values\.

LIBRARY ROUTINES
================

The following routines are available from C to manage vectors\.  Vectors
are identified by the vector name\.  

__Rbc\_CreateVector__  

Synopsis:  

int Rbc\_CreateVector (*interp*, *vecName*, *length*, *vecPtrPtr*)
:   Tcl\_Interp \**interp*;
    char \**vecName*;  
    int *length*;  
    Rbc\_Vector \*\**vecPtrPtr*;  

Description:
:   Creates a new vector *vecName* with a length of *length*\.
    __Rbc\_CreateVector__ creates both a new Tcl command and array
    variable *vecName*\.  Neither a command nor variable named
    *vecName* can already exist\.  A pointer to the vector is
    placed into *vecPtrPtr*\.  

Results:
:   Returns TCL\_OK if the vector is successfully created\.  If
    *length* is negative, a Tcl variable or command *vecName*
    already exists, or memory cannot be allocated for the
    vector, then TCL\_ERROR is returned and *interp\-\>result* will
    contain an error message\.  

__Rbc\_DeleteVectorByName__  

Synopsis:  

int Rbc\_DeleteVectorByName (*interp*, *vecName*)
:   Tcl\_Interp \**interp*;
    char \**vecName*;  

Description:
:   Removes the vector *vecName*\.  *VecName* is the name of a
    vector which must already exist\.  Both the Tcl command and
    array variable *vecName* are destroyed\.  All clients of the
    vector will be notified immediately that the vector has
    been destroyed\.  

Results:
:   Returns TCL\_OK if the vector is successfully deleted\.  If
    *vecName* is not the name a vector, then TCL\_ERROR is
    returned and *interp\-\>result* will contain an error message\.

__Rbc\_DeleteVector__  

Synopsis:  

int Rbc\_DeleteVector (*vecPtr*)
:   Rbc\_Vector \**vecPtr*;

Description:
:   Removes the vector pointed to by *vecPtr*\.  *VecPtr* is a
    pointer to a vector, typically set by __Rbc\_GetVector__ or
    __Rbc\_CreateVector__\.  Both the Tcl command and array variable
    of the vector are destroyed\.  All clients of the vector
    will be notified immediately that the vector has been
    destroyed\.  

Results:
:   Returns TCL\_OK if the vector is successfully deleted\.  If
    *vecName* is not the name a vector, then TCL\_ERROR is
    returned and *interp\-\>result* will contain an error message\.

__Rbc\_GetVector__  

Synopsis:  

int Rbc\_GetVector (*interp*, *vecName*, *vecPtrPtr*)
:   Tcl\_Interp \**interp*;
    char \**vecName*;  
    Rbc\_Vector \*\**vecPtrPtr*;  

Description:
:   Retrieves the vector *vecName*\.  *VecName* is the name of a
    vector which must already exist\.  *VecPtrPtr* will point be
    set to the address of the vector\.  

Results:
:   Returns TCL\_OK if the vector is successfully retrieved\.  If
    *vecName* is not the name of a vector, then TCL\_ERROR is
    returned and *interp\-\>result* will contain an error message\.

__Rbc\_ResetVector__  

Synopsis:  

int __Rbc\_ResetVector__ (*vecPtr*, *dataArr*,  

*numValues*, *arraySize*, *freeProc*)
:   Rbc\_Vector \**vecPtr*;
    double \**dataArr*;  
    int \**numValues*;  
    int \**arraySize*;  
    Tcl\_FreeProc \**freeProc*;  

Description:
:   Resets the components of the vector pointed to by *vecPtr*\.
    Calling __Rbc\_ResetVector__ will trigger the vector to dispatch
    notifications to its clients\. *DataArr* is the array of
    doubles which represents the vector data\. *NumValues* is the
    number of elements in the array\. *ArraySize* is the actual
    size of the array (the array may be bigger than the number
    of values stored in it)\. *FreeProc* indicates how the storage
    for the vector component array (*dataArr*) was allocated\.  It
    is used to determine how to reallocate memory when the
    vector is resized or destroyed\.  It must be TCL\_DYNAMIC,
    TCL\_STATIC, TCL\_VOLATILE, or a pointer to a function to
    free the memory allocated for the vector array\. If *freeProc*
    is TCL\_VOLATILE, it indicates that *dataArr* must be copied
    and saved\.  If *freeProc* is TCL\_DYNAMIC, it indicates that
    *dataArr* was dynamically allocated and that Tcl should free
    *dataArr* if necessary\.  Static indicates that nothing should
    be done to release storage for *dataArr*\.  

Results:
:   Returns TCL\_OK if the vector is successfully resized\.  If
    *newSize* is negative, a vector *vecName* does not exist, or
    memory cannot be allocated for the vector, then TCL\_ERROR
    is returned and *interp\-\>result* will contain an error
    message\.  

__Rbc\_ResizeVector__  

Synopsis:  

int Rbc\_ResizeVector (*vecPtr*, *newSize*)
:   Rbc\_Vector \**vecPtr*;
    int *newSize*;  

Description:
:   Resets the length of the vector pointed to by *vecPtr* to
    *newSize*\.  If *newSize* is smaller than the current size of
    the vector, it is truncated\.  If *newSize* is greater, the
    vector is extended and the new components are initialized
    to 0\.0\.  Calling __Rbc\_ResetVector__ will trigger the vector to
    dispatch notifications\.  

Results:
:   Returns TCL\_OK if the vector is successfully resized\.  If
    *newSize* is negative or memory can not be allocated for the
    vector, then TCL\_ERROR is returned and *interp\-\>result* will
    contain an error message\.  

__Rbc\_VectorExists__  

Synopsis:  

int Rbc\_VectorExists (*interp*, *vecName*)
:   Tcl\_Interp \**interp*;
    char \**vecName*;  

Description:
:   Indicates if a vector named *vecName* exists in *interp*\.

Results:
:   Returns 1 if a vector *vecName* exists and 0 otherwise\.

If your application needs to be notified when a vector changes, it
can allocate a unique *client* *identifier* for itself\.  Using this
identifier, you can then register a call\-back to be made whenever the
vector is updated or destroyed\.  By default, the call\-backs are made
at the next idle point\.  This can be changed to occur at the time the
vector is modified\.  An application can allocate more than one
identifier for any vector\.  When the client application is done with
the vector, it should free the identifier\.  

The call\-back routine must of the following type\.  

typedef void (Rbc\_VectorChangedProc) (Tcl\_Interp \**interp*,
:   ClientData *clientData*, Rbc\_VectorNotify *notify*);

*ClientData* is passed to this routine whenever it is called\.  You can
use this to pass information to the call\-back\.  The *notify* argument
indicates whether the vector has been updated of destroyed\. It is an
enumerated type\.  

typedef enum {
:   RBC\_VECTOR\_NOTIFY\_UPDATE=1,
    RBC\_VECTOR\_NOTIFY\_DESTROY=2  
} __Rbc\_VectorNotify__;  

__Rbc\_AllocVectorId__  

Synopsis:  

Rbc\_VectorId Rbc\_AllocVectorId (*interp*, *vecName*)
:   Tcl\_Interp \**interp*;
    char \**vecName*;  

Description:
:   Allocates an client identifier for with the vector
    *vecName*\.  This identifier can be used to specify a call\-
    back which is triggered when the vector is updated or
    destroyed\.  

Results:
:   Returns a client identifier if successful\.  If *vecName*
    is not the name of a vector, then NULL is returned and
    *interp\-\>result* will contain an error message\.

__Rbc\_GetVectorById__  

Synopsis:  

int Rbc\_GetVector (*interp*, *clientId*, *vecPtrPtr*)
:   Tcl\_Interp \**interp*;
    Rbc\_VectorId *clientId*;  
    Rbc\_Vector \*\**vecPtrPtr*;  

Description:
:   Retrieves the vector used by *clientId*\.  *ClientId* is a
    valid vector client identifier allocated by
    __Rbc\_AllocVectorId__\.  *VecPtrPtr* will point be set to the
    address of the vector\.  

Results:
:   Returns TCL\_OK if the vector is successfully retrieved\.

__Rbc\_SetVectorChangedProc__  

Synopsis:  

void Rbc\_SetVectorChangedProc (*clientId*, *proc*, *clientData*);
:   Rbc\_VectorId *clientId*;
    Rbc\_VectorChangedProc \**proc*;
    ClientData \**clientData*;  

Description:
:   Specifies a call\-back routine to be called whenever the
    vector associated with *clientId* is updated or deleted\.
    *Proc* is a pointer to call\-back routine and must be of
    the type __Rbc\_VectorChangedProc__\.  *ClientData* is a one\-
    word value to be passed to the routine when it is
    invoked\. If *proc* is NULL, then the client is not
    notified\.  

Results:
:   The designated call\-back procedure will be invoked when
    the vector is updated or destroyed\.  

__Rbc\_FreeVectorId__  

Synopsis:  

void Rbc\_FreeVectorId (*clientId*);
:   Rbc\_VectorId *clientId*;

Description:
:   Frees the client identifier\.  Memory allocated for the
    identifier is released\.  The client will no longer be
    notified when the vector is modified\.  

Results:
:   The designated call\-back procedure will be no longer be
    invoked when the vector is updated or destroyed\.

__Rbc\_NameOfVectorId__  

Synopsis:  

char \*Rbc\_NameOfVectorId (*clientId*);
:   Rbc\_VectorId *clientId*;

Description:
:   Retrieves the name of the vector associated with the
    client identifier *clientId*\.  

Results:
:   Returns the name of the vector associated with *clientId*\.
    If *clientId* is not an identifier or the vector has been
    destroyed, NULL is returned\.  

__Rbc\_InstallIndexProc__  

Synopsis:  

void Rbc\_InstallIndexProc (*indexName*, *procPtr*)
:   char \**indexName*;
    Rbc\_VectorIndexProc \**procPtr*;

Description:
:   Registers a function to be called to retrieved the index
    *indexName* from the vector\'s array variable\.

    typedef double Rbc\_VectorIndexProc(Vector \*vecPtr);

    The function will be passed a pointer to the vector\.
    The function must return a double representing the value
    at the index\.  

Results:
:   The new index is installed into the vector\.

C API EXAMPLE
=============

The following example opens a file of binary data and stores it in an
array of doubles\. The array size is computed from the size of the file\.
If the vector "data" exists, calling __Rbc\_VectorExists__, __Rbc\_GetVector__ is
called to get the pointer to the vector\.  Otherwise the routine
__Rbc\_CreateVector__ is called to create a new vector and returns a pointer
to it\. Just like the Tcl interface, both a new Tcl command and array
variable are created when a new vector is created\. It doesn\'t make any
difference what the initial size of the vector is since it will be
reset shortly\. The vector is updated when bc\_ResetVector is called\.
Rbc\_ResetVector makes the changes visible to the Tcl interface and
other vector clients (such as a graph widget)\.  

~~~~~
#include <tcl.h>
#include <rbc.h>
Rbc_Vector *vecPtr;
double *newArr;
FILE *f;
struct stat statBuf;
int numBytes, numValues;

f = fopen("binary.dat", "r");
fstat(fileno(f), &statBuf);
numBytes = (int)statBuf.st_size;

/* Allocate an array big enough to hold all the data */
newArr = (double *)malloc(numBytes);
numValues = numBytes / sizeof(double);
fread((void *)newArr, numValues, sizeof(double), f);
fclose(f);

if (Rbc_VectorExists(interp, "data"))  {
    if (Rbc_GetVector(interp, "data", &vecPtr) != TCL_OK) {
  return TCL_ERROR;
    }
} else {
   if (Rbc_CreateVector(interp, "data", 0, &vecPtr) != TCL_OK) {
  return TCL_ERROR;
   }
}
/*
 * Reset the vector. Clients will be notified when Tk is idle.
 * TCL_DYNAMIC tells the vector to free the memory allocated
 * if it needs to reallocate or destroy the vector.
 */
if (Rbc_ResetVector(vecPtr, newArr, numValues, numValues,
  TCL_DYNAMIC) != TCL_OK) {
    return TCL_ERROR;
}
~~~~~

INCOMPATIBILITIES
=================

In previous versions, if the array variable isn\'t global (i\.e\. local to
a Tcl procedure), the vector is automatically destroyed when the
procedure returns\.  

~~~~~
proc doit {} {
    # Temporary vector x
    vector x(10)
    set x(9) 2.0
      ...
}
~~~~~

This has changed\.  Variables are not automatically destroyed when their
variable is unset\.  You can restore the old behavior by setting the
"\-watchunset" switch\.  

KEYWORDS
========

vector, graph, widget  

