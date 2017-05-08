

NAME
====

rbcdebug \- print Tcl commands before execution  

SYNOPSIS
========

__rbcdebug__ ?*level*?  

DESCRIPTION
===========

The __rbcdebug__ command is a simple tracing facility for Tcl commands\.
Each command line is printed before it is executed on standard error\.
The output consists of the command line both before and after
substitutions have occurred\.  *Level* indicates at what level to stop
tracing commands\.  If *level* is 0, no tracing is performed\. This is the
default\.  If no *level* argument is given, the current level is printed\.

KEYWORDS
========

debug  

