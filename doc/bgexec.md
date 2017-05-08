

NAME
====

bgexec \- Run programs in the background while handling Tk events\.

SYNOPSIS
========

__rbc::bgexec__ *varName* ?*option* *value*?\.\.\. *program* ?*arg*?\.\.\.

DESCRIPTION
===========

The __bgexec__ command executes programs in the background, allowing Tk to
handle events\.  A global Tcl variable *varName* is set when the program
has completed\.  

INTRODUCTION
============

Tcl\'s __exec__ command is very useful for gathering information from the
operating system\.  It runs a program and returns the output as its
result\.  This works well for Tcl\-only applications\. But for Tk
applications, a problem occurs when the program takes time to process\.
Let\'s say we want the get the disk usage of a directory\.  We\'ll use the
Unix program du to get the summary\.  

~~~~~
set out [exec du -s $dir]
puts "Disk usage for $dir is $out"
~~~~~

While du is running, scrollbars won\'t respond\.  None of the Tk widgets
will be redrawn properly\.  The __send__ command won\'t work\.  And the worst
part is that the application appears hung up or dead\.  The problem is
that while __exec__ is waiting for *du* to finish, Tk is not able to handle X
events\.  

The __bgexec__ command performs the same functions as __exec__, but also allows
Tk to handle events\.  You can execute a long\-running program and the Tk
widgets will behave normally\.  When the program finishes, its output
and the exit status are written to Tcl variables\.  This makes it easy
to monitor and save the output of a program\.  

EXAMPLE
=======

Here is the disk usage example again, this time using __bgexec__\.  The
syntax to invoke "du" is exactly the same as the previous example, when
we used __exec__\.  

~~~~~
global myStatus myOutput
rbc::bgexec myStatus -output myOutput du -s $dir
puts "Disk usage for $dir is $myOutput"
~~~~~

Two global variables, myStatus and myOutput, will be set by __bgexec__ when
du has completed\. MyStatus will contain the program\'s exit status\.
MyOutput, specified by the __\-output__ option, will store the output of the
program\.  

You can also terminate the program by setting the variable myStatus\.
If myStatus is set before du has completed, the process is killed\.
Under Unix, this is done sending by a configurable signal (by default
it\'s SIGKILL)\. Under Win32, this is done by calling __TerminateProcess__\.
It makes no difference what myStatus is set to\.  

~~~~~
set myStatus {}
~~~~~

There are several __bgexec__ options to collect different types of
information\.  

~~~~~
global myStatus myOutput myErrs
rbc::bgexec myStatus -output myOutput -error myErrs du -s $dir
~~~~~

The __\-error__ option is similar to __\-output__\.  It sets a global variable
when the program completes\.  The variable will contain any data written
to stderr by the program\.  

The __\-output__ and __\-error__ variables are set only after the program
completes\.  But if the program takes a long time, to run you may want
to receive its partial output\.  You can gather data as it becomes
available using the __\-onoutput__ option\.  It specifies a Tcl command
prefix\.  Whenever new data is available, this command is executed, with
the data appended as an argument to the command\.  

~~~~~
proc GetInfo { data } {
    puts $data
}
rbc::bgexec myStatus -onoutput GetInfo du -s $dir
~~~~~

When output is available, the procedure GetInfo is called\.  The
__\-onerror__ option performs a similar function for the stderr data stream\.

Like __exec__, __bgexec__ returns an error if the exit code of the program is
not zero\.  If you think you may get a non\-zero exit code, you might
want to invoke __bgexec__ from within a __catch__\.  

~~~~~
catch { rbc::bgexec myStatus -output myOutput du -s $dir }
~~~~~

By default, __bgexec__ will wait for the program to finish\.  But you can
detach the program making ampersand (&) the last argument on the
command line\.  

~~~~~
global myStatus myOutput
rbc::bgexec myStatus -output myOutput du -s $dir &
~~~~~

__Bgexec__ will return immediately and its result will be a list of the
spawned process ids\.  If at some point you need to wait for the program
to finish up, you can use __tkwait__\.  When the program finishes, the
variable myStatus will be written to, breaking out the __tkwait__ command\.

~~~~~
global myStatus myOutput
rbc::bgexec myStatus -output myOutput du -s $dir &
  ...
tkwait variable myStatus
~~~~~

SYNTAX
======

The __bgexec__ command takes the following form:  

__rbc::bgexec__ *varName* ?*option* *value*?\.\.\. *program* ?*arg*?\.\.\.

*VarName* is the name of a global variable which is set when *program* has
finished executing\.  The exit status of will be stored in *varName*\.  The
exit status is a list of a status token, the process\-id of the program,
the exit code, and a status message\.  You can also prematurely
terminate the program by setting *varName*\.  Under Unix, the program will
be sent a signal to terminate it (by default the signal is a SIGKILL;
see the __\-killsignal__ option)\.  

*Program* is the name of the program to be executed and *args* are any
extra arguments for *program*\.  The syntax of *program* and *args* is the
same as the __exec__ command\. So you can redirect I/O, execute pipelines,
etc\. (see the __exec__ manual for further information) just like __exec__\.  If
the last argument is an ampersand (&), the program will be run
detached, and __bgexec__ will return immediately\.  *VarName* will still be
set with the return status when *program* completes\.  

OPTIONS
=======

*Option* refers to the switch name always beginning with a dash (\-)\.
*Value* is the value of the option\.  Option\-value pairs are terminated
either by the program name, or double dashes (\-\-)\.  The following
options are available for __bgexec__:  

\-decodeerror *encodingName*
:   Specifies the encoding of the stderr channel\.  This affects only
    data returned to the Tcl interpreter\.  No translation is done on
    file redirection\.  
    For example if data is to be converted from Unicode for use in
    Tcl, you would use the "unicode" encoding\. The default is that
    no tranlation is performed\.  

\-decodeoutput *encodingName*
:   Specifies the encoding of the stdout channels\.  This affects
    only data returned to the Tcl interpreter\.  No translation is
    done on file redirection\.  
    For example if data is to be converted from Unicode for use in
    Tcl, you would use the "unicode" encoding\. The default is that
    no tranlation is performed\.  

\-error *varName*
:   Specifies that a global variable *varName* is to be set with the
    contents of stderr after the program has completed\.

\-keepnewline *boolean*
:   Specifies that a trailing newline should be retained in the
    output\. If *boolean* is true, the trailing newline is truncated
    from the output of the __\-onoutput__ and __\-output__ variables\.  The
    default value is true\.  

\-killsignal *signal*
:   Specifies the signal to be sent to the program when terminating\.
    This is available only under Unix\.  *Signal* can either be a
    number (typically 1\-32) or a mnemonic (such as SIGINT)\. If
    *signal* is the empty string, then no signal is sent\.  The default
    signal is 9 (SIGKILL)\.  

\-lasterror *varName*
:   Specifies a variable *varName* that is updated whenever data
    becomes available from standard error of the program\.  *VarName*
    is a global variable\. Unlike the __\-error__ option, data is
    available as soon as it arrives\.  

\-lastoutput *varName*
:   Specifies a variable *varName* that is updated whenever data
    becomes available from standard output of the program\.  *VarName*
    is a global variable\. Unlike the __\-output__ option, data is
    available as soon as it arrives\.  

\-linebuffered *boolean*
:   Specifies that updates should be made on a line\-by\-line basis\.
    Normally when new data is available __bgexec__ will set the variable
    (__\-lastoutput__ and __\-lasterror__ options) or invoke the command
    (__\-onoutput__ and __\-onerror__ options) delivering all the new data
    currently available\.  If *boolean* is true, only one line at a
    time will be delivered\.  This can be useful when you want to
    process the output on a line\-by\-line basis\.  The default value
    is false\.  

\-output *varName*
:   Specifies that a global variable *varName* is to be set with the
    output of the program, once it has completed\.  If this option is
    not set, no output will be accumulated\.  

\-onerror *command*
:   Specifies the start of a Tcl command that will be executed
    whenever new data is available from standard error\. The data is
    appended to the command as an extra argument before it is
    executed\.  

\-onoutput *command*
:   Specifies the start of a Tcl command that will be executed
    whenever new data is available from standard output\. The data is
    appended to the command as an extra argument before it is
    executed\.  

\-update *varName*
:   Deprecated\. This option is replaced by __\-lasterror__\.

\-\-
:   This marks the end of the options\.  The following argument will
    be considered the name of a program even if it starts with a
    dash (__\-__)\.  

PREEMPTION
==========

Because __bgexec__ allows Tk to handle events while a program is running,
it\'s possible for an application to preempt itself with further user\-
interactions\.  Let\'s say your application has a button that runs the
disk usage example\.  And while the du program is running, the user
accidently presses the button again\.  A second __bgexec__ program will
preempt the first\.  What this means is that the first program can not
finish until the second program has completed\.  

Care must be taken to prevent an application from preempting itself by
blocking further user\-interactions (such as button clicks)\.  The RBC
__busy__ command is very useful for just these situations\.  See the __busy__
manual for details\.  

DIFFERENCES WITH FILEEVENT
==========================

Since Tk 4\.0, a subset of __bgexec__ can be also achieved using the
__fileevent__ command\.  The steps for running a program in the background
are:  

Execute the program with the __open__ command (using the "|" syntax) and
save the file handle\.  

~~~~~
global fileId
set fileId [open "|du -s $dir" r]
~~~~~

Next register a Tcl code snippet with __fileevent__ to be run whenever
output is available on the file handle\.  The code snippet will read
from the file handle and save the output in a variable\.

~~~~~
fileevent fileId readable {
    if { [gets $fileId line] < 0 } {
  close $fileId
  set output $temp
  unset fileId temp
    } else {
  append temp $line
    }
}
~~~~~

The biggest advantage of __bgexec__ is that, unlike __fileevent__, it requires
no additional Tcl code to run a program\.  It\'s simpler and less error
prone\.  You don\'t have to worry about non\-blocking I/O\.  It\'s handled
tranparently for you\.  

__Bgexec__ runs programs that __fileevent__ can not\.  __Fileevent__ assumes that
the when stdout is closed the program has completed\.  But some
programs, like the Unix compress program, reopen stdout, fooling
__fileevent__ into thinking the program has terminated\.  In the example
above, we assume that the program will write and flush its output line\-
by\-line\.  However running another program, your application may block
in the __gets__ command reading a partial line\.  

__Bgexec__ lets you get back the exit status of the program\. It also allows
you to collect data from both stdout and stderr simultaneously\.
Finally, since data collection is handled in C code, __bgexec__ is faster\.
You get back to the Tk event loop more quickly, making your application
seem more responsive\.  

SEE ALSO
========

busy, exec, tkwait  

KEYWORDS
========

exec, background, busy  

