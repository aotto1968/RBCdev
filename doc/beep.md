

NAME
====

beep \- ring the bell  

SYNOPSIS
========

__beep__ ?*percent*?  

DESCRIPTION
===========

The __beep__ command rings the keyboard bell\.  *Percent* is relative to the
base volume of the keyboard bell and can range from \-100 to 100
inclusive\.  

If *percent* is nonnegative then the bell volume is:  

~~~~~
base - [(base * percent) / 100] + percent
~~~~~

If *percent* is negative then the bell volume is:  

~~~~~
base + [(base * percent) / 100]
~~~~~

The default *percent* is 50\.  

EXAMPLE
=======

~~~~~
beep
~~~~~

KEYWORDS
========

bell, beep  

