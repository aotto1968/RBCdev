

NAME
====

cutbuffer \- Manipulate X cut buffer properties  

SYNOPSIS
========

__cutbuffer__ *get* *?number?*  
__cutbuffer__ *rotate* *?count?*  
__cutbuffer__ *set* *value* *?number?*  

DESCRIPTION
===========

The __cutbuffer__ command allows you to read or modify the eight X cut
buffer properties\. You can also rotate the buffers properties\.

OPERATIONS
==========

The following operations are available for the __cutbuffer__ command:

__cutbuffer get__ *?number?*

:   Returns the value of a cutbuffer *number*\.  *Number* must be a
    number between 0 and 7\.  The default is 0\.  The cutbuffer is
    returned exactly, except that NUL bytes are converted to \'\@\'
    characters\.  If a cut buffer *number* does not exist, then "" is
    returned\.  

__cutbuffer rotate__ *?count?*

:   Rotates the cut buffers by *count*\. *Count* must be a number between
    \-7 and 7\. The default is 1\.  

__cutbuffer set__ *value* ?*number*?

:   Sets the cutbuffer *number* to *value*\.  *Number* must be a number
    between 0 and 7\.  The default is 0\.  

KEYWORDS
========

cut buffer, property  

