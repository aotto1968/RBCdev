# RBCdev
rework of the BLT toolkit using new name RBC
RBC - Refactored BLT Components

This is version 0.2 of the RBC library.  It should be considered alpha
quality software.

RBC is an extension of the Tcl/Tk toolkit and contains refactored
  components from version 2.4z of the BLT library.  These components
  were refactored so that they would function with version Tcl/Tk 8.5.

RBC is available from:
	https://github.com/aotto1968/RBCdev
	
More information on BLT is available from:
	http://www.sourceforge.net/projects/blt/files
	
RBC is intended to work with Tcl/Tk versions 8.4 and 8.5, although it
  may work with others.  RBC is a TEA compliant extension, although it
  is not (yet) entirely free of dependency on Tcl/Tk private structures.

RBC is a subset of BLT, contains the essential components for
  developing data graphing applications.  Some BLT components have been
  superseded by advances in Tcl and Tk, and some others have been
  extracted into separate extensions.  RBC contains the following BLT
  components:


NAME
       RBC - Introduction to the RBC library

DESCRIPTION
       RBC is a library of extensions to the Tk library.  It adds new commands
       and variables to the application's interpreter.

COMPOSITION COMMANDS

       The following commands are  added  to  the  interpreter  from  the  RBC
       library:

       table          A  table  geometry  manager  for Tk.  You specify window
                      placements as table row,column positions and windows can
                      also  span  multiple  rows or columns.  It also has many
                      options for setting and/or bounding window sizes.

       container      The container widget lets you embed an X11 window from a
                      foreign  application into your Tk application.  The for-
                      eign window is reparented inside of the widget. You  can
                      then  place  and arrange the container just as you would
                      any Tk widget.

       tabset         The tabset widget displays a series of overlapping fold-
                      ers.  Only  the contents of one folder at a time is dis-
                      played.  By clicking on the tab's of a folder,  you  can
                      view other folders.  Each folder may contain any Tk wid-
                      get that can be automatically positioned and resized  in
                      the folder.

       treeview       The treeview widget displays hierarchical data.  Data is
                      represented as nodes in a  general-ordered  tree.   Each
                      node  may have sub-nodes and these nodes can in turn has
                      their own children.  A node is displayed as a row  entry
                      in  the  widget.   Each entry has a text label and icon.
                      When a node has children, its  entry  is  drawn  with  a
                      small  button  to  the  left of the label.  Clicking the
                      mouse over this button opens or closes the node.  When a
                      node  is  open,  its  children  are exposed.  When it is
                      closed, the children and their  descedants  are  hidden.
                      The  button  is  normally  a  + or - symbol (ala Windows
                      Explorer), but can be replaced with a pair of Tk  images
                      (open  and closed images).  The treeview widget replaces
                      both the hiertable and hierbox widgets.

       htext          A simple hypertext widget.  Combines text and Tk widgets
                      into  a  single scroll-able window.  Tcl commands can be
                      embedded into text, which are invoked  as  the  text  is
                      parsed.   In addition, Tk widgets can be appended to the
                      window at the current point in the text.  Htext  can  be
                      also used to create scrolled windows of Tk widgets.

PLOTTING COMMANDS

       graph          A 2D plotting widget.  Plots two variable data in a win-
                      dow with an optional legend and annotations.   It has of
                      several  components; coordinate axes, crosshairs, a leg-
                      end, and a collection of elements and tags.

       stripchart     The stripchart command creates a strip chart  for  plot-
                      ting two-dimensional data (x,y coordinates). It has many
                      configurable components: coordinate axes, elements, leg-
                      end,  grid  lines,  cross hairs, etc.  They allow you to
                      customize the look and feel  of  the  strip  chart.  The
                      stripchart  is essentially the same as the graph widget.
                      The use of a strip chart differs in that the X-axis typ-
                      ically  refers to time points.  Data values are added at
                      intervals.  The strip chart lets you automatically main-
                      tain  a  view  of the most recent time points.  The axis
                      options -shiftby and -autorange control this.   You  can
                      specify  different  line styles for data points (see the
                      -styles option).

       spline         Computes a spline fitting a set of data points (x and  y
                      vectors)  and  produces  a  vector  of  the interpolated
                      images (y-coordinates) at a given set of x-coordinates.

       barchart       A barchart widget.  Plots two-variable data as rectangu-
                      lar bars in a window.  The x-coordinate values designate
                      the position of the bar along the x-axis, while  the  y-
                      coordinate values designate the magnitude.  The barchart
                      widget  has  of  several  components;  coordinate  axes,
                      crosshairs,  a  legend, and a collection of elements and
                      tags.

MISCELLANEOUS COMMANDS

       vector         Creates a vector of floating point values.  The vector's
                      components  can  be manipulated in three ways: through a
                      Tcl array variable, a Tcl command, or the C API.

       tree           The tree command creates  tree  data  objects.   A  tree
                      object  is general ordered tree of nodes.  Each node has
                      both a label and a key-value list of data.  Data can  be
                      heterogeneous,  since  nodes  do not have to contain the
                      same data keys.  It is associated  with  a  Tcl  command
                      that  you can use to access and modify the its structure
                      and data. Tree objects can also be managed via a C API.

       bgexec         Like Tcl's exec command, bgexec runs a pipeline of  Unix
                      commands  in the background.  Unlike exec, the output of
                      the last process is collected and a global Tcl  variable
                      is  set  upon  its  completion.  bgexec can be used with
                      tkwait to wait for Unix commands to finish  while  still
                      handling  expose  events.   Intermediate  output is also
                      available while the pipeline is active.

       bitmap         Reads and writes bitmaps from Tcl.  New X bitmaps can be
                      defined  on-the-fly from Tcl, obviating the need to copy
                      around bitmap files.  Other options query loaded X  bit-
                      map's dimensions and data.

       drag&drop      Provides  a  drag-and-drop facility for Tk.  Information
                      (represented by a token window) can be  dragged  to  and
                      from any Tk window, including those of another Tk appli-
                      cation.  drag&drop acts as a coordinator,  directing  Tk
                      send commands between (or within) TCL/Tk applications.

       winop          Raise,  lower, map, or, unmap any window.  The raise and
                      lower functions are useful for stacking windows above or
                      below "busy windows".

       watch          Arranges  for  Tcl procedures to be called before and/or
                      after the execution of every Tcl command.  This  command
                      may be used in the logging, profiling, or tracing of Tcl
                      code.

       rbcdebug       A simple Tcl command tracing facility useful for  debug-
                      ging  Tcl  code.   Displays  each Tcl command before and
                      after substitution along its level in the interpreter on
                      standard error.

VARIABLES
       The  following  Tcl  variables are either set or used by RBC at various
       times in its execution:

       rbc_library or ::rbc::library
                      This variable contains the name of a directory  contain-
                      ing  a library of Tcl scripts and other files related to
                      RBC.  Currently, this directory contains  the  drag&drop
                      protocol scripts and the PostScript prolog used by graph
                      and barchart.  The value of this variable is taken  from
                      the pkgIndex.tcl file at startup.

       ::rbc          Top  level  namespace of the rbc widget and tool collec-
                      tion

ADDING RBC TO YOUR APPLICATIONS
       It's easy to add RBC to an existing Tk application.   RBC  requires  no
       patches  or  edits  to the Tcl or Tk libraries.  To add RBC, simply add
       the following code snippet to your application's tcl file.

              package require rbc

       To compile the rbc use the following GNU standard procedure

              configure…
              make…
              make install…

       To start the demo use…

              make demo

       or

              make wish ARGS=demos/barchart1.tcl ?DEBUG=valgrind?

BUGS
       Send bug reports, requests, suggestions, etc. to
       https://github.com/aotto1968/RBCdev/

Building from Source:

RBC is a TEA compliant extension.  You should be able to unpack the
source code, and perform the usual configure / make / make install
procedure.  Making the test target will run the automated test suite.

Since RBC still depends on some Tcl/Tk private data structures, you
may experience some difficulty in bulding it against some Tcl
distributions which do not have the complete set of public and private
headers.

History:	

In order to fulfill degree requirements, the four of us undertook the
refactoring of a few commonly used BLT components.  The project was
proposed by an alumnus of the students' institute and was accepted by
the school's Computer Science and Software Engineering Department. The
project began in the Fall of 2008 and culminated on the students'
graduation in the Spring of 2009.  In addition to refactoring parts of
BLT, we also began developing a graphical data analysis tool that is
designed to work with RBC (and BLT) and be easily extensible.  For
more information see the GDAT project available at:
http://www.sourceforge.net/projects/gdat/

In keeping with the spirit of BLT, we have released this project to
the open source community in hopes that you will continue development
and add more components from the BLT library that are compatible with
version 8.5 and later of Tcl/Tk.
	
sjg,njh,sjs,jms
