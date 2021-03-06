# RBC.winop.raise.M.tcl --
#
###Abstract
# This file contains the manual tests that test the raise 
# function of the winop BLT component.
#
###Copyright
# See the file "license.terms" for information on usage and
# redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
#
###Revision String
# SVN: $Id$

###Package Definition
package provide winop.raise

package require rbc
namespace import rbc::*

namespace eval winop.raise {
	# ------------------------------------------------------------------------------------
	# Purpose: Ensure the raise function of the winop component works correctly when given
	# a single window name.
	# ------------------------------------------------------------------------------------
	proc RBC.winop.raise.M.1.1.Setup {} {
		graph .graph1 -background blue
		graph .graph2 -background red
		pack .graph1
		pack .graph2
	}
	
	proc RBC.winop.raise.M.1.1.Body {} {
		winop move .graph2 0 100
		after 1000
		winop raise .graph1
	}
	
	proc RBC.winop.raise.M.1.1.Cleanup {} {
		destroy .graph2
		destroy .graph1
	}
	
	# ------------------------------------------------------------------------------------
	# Purpose: Ensure the raise function of the winop component works correctly when given
	# multiple window names.
	# ------------------------------------------------------------------------------------
	proc RBC.winop.raise.M.1.2.Setup {} {
		graph .graph1 -background blue
		graph .graph2 -background red
		graph .graph3 -background green
		pack .graph1
		pack .graph2
		pack .graph3
	}
	
	proc RBC.winop.raise.M.1.2.Body {} {
		winop move .graph2 0 100
		winop move .graph3 0 200
		after 1000
		winop raise .graph2 .graph1
	}
	
	proc RBC.winop.raise.M.1.2.Cleanup {} {
		destroy .graph3
		destroy .graph2
		destroy .graph1
	}
}
	