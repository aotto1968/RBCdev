

NAME
====

watch \- call Tcl procedures before and after each command

SYNOPSIS
========

__watch create__ *watchName* ?*options*?  

__watch activate__ *watchName*  

__watch deactivate__ *watchName*  

__watch delete__ *watchName*  

__watch configure__ *watchName* ?*options*  

__watch info__ *watchName*  

__watch names__  

DESCRIPTION
===========

The __watch__ command arranges for Tcl procedures to be invoked before and
after the execution of each Tcl command\.  

INTRODUCTION
============

When an error occurs in Tcl, the global variable *errorInfo* will contain
a stack\-trace of the active procedures when the error occured\.
Sometimes, however, the stack trace is insufficient\.  You may need to
know exactly where in the program\'s execution the error occured\.  In
cases like this, a more general tracing facility would be useful\.

The __watch__ command lets you designate Tcl procedures to be invoked
before and after the execution of each Tcl command\.  This means you can
display the command line and its results for each command as it
executes\.  Another use is to profile your Tcl commands\.  You can
profile any Tcl command (like __if__ and __set__), not just Tcl procedures\.

EXAMPLE
=======

The following example use __watch__ to trace Tcl commands (printing to
standard error) both before and after they are executed\.

~~~~~
proc preCmd { level command argv } {
    set name [lindex $argv 0]
    puts stderr "$level $name => $command"
}

proc postCmd { level command argv retcode results } {
    set name [lindex $argv 0]
    puts stderr "$level $name => $argv0= ($retcode) $results"
}
watch create trace \
  -postcmd postCmd -precmd preCmd
~~~~~

OPERATIONS
==========

The following operations are available for the __watch__ command:

__watch activate__ *watchName*

:   Activates the watch, causing Tcl commands the be traced to the
    maximum depth selected\.  

__watch create__ *watchName* ?*options*?\.\.\.

:   Creates a new watch *watchName*\. It\'s an error if another watch
    *watchName* already exists and an error message will be returned\.
    *Options* may have any of the values accepted by the __watch__
    __configure__ command\.  This command returns the empty string\.

__watch configure__ *watchName* ?*options\.\.\.*?

:   Queries or modifies the configuration options of the watch
    *watchName*\.  *WatchName* is the name of a watch\.  *Options* may have
    any of the following values:  

    \-active *boolean*
    :   Specifies if the watch is active\.  By default, watches
        are active when created\.  

    \-postcmd *string*
    :   Specifies a Tcl procedure to be called immediately after
        each Tcl command\.  *String* is name of a Tcl procedure and
        any extra arguments to be passed to it\.  Before *string* is
        invoked, five more arguments are appended: 1) the current
        level 2) the current command line 3) a list containing
        the command after substitutions and split into words 4)
        the return code of the command, and 5) the results of the
        command\.  The return status of the postcmd procedure is
        always ignored\.  

    \-precmd *string*
    :   Specifies a Tcl procedure to be called immediately before
        each Tcl command\.  *String* is name of a Tcl procedure and
        any extra arguments to be passed to it\.  Before *string* is
        invoked, three arguments are appended: 1) the current
        level 2) the current command line, and 3) a list
        containing the command after substitutions and split into
        words\.  The return status of the __\-precmd__ procedure is
        always ignored\.  

    \-maxlevel *number*
    :   Specifies the maximum evaluation depth to watch Tcl
        commands\.  The default maximum level is 10000\.

__watch deactivate__ *watchName*

:   Deactivates the watch\.  The __\-precmd__ and __\-postcmd__ procedures will
    no longer be invoked\.  

__watch info__ *watchName*

:   Returns the configuration information associated with the watch
    *watchName*\.  *WatchName* is the name of a watch\.  

__watch names__ ?*state*?

:   Lists the names of the watches for a given state\.  *State* may be
    one of the following: active, idle, or ignore\.  If a *state*
    argument isn\'t specified,  
    all watches are listed\.  

KEYWORDS
========

debug, profile  

