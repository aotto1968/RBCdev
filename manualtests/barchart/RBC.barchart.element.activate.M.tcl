# RBC.barchart.element.activate.M.tcl --
#
###Abstract
# This file contains the manual tests that test the element activate 
# function of the barchart BLT component.
#
###Copyright
# See the file "license.terms" for information on usage and
# redistribution of this file, and for a DISCLAIMER OF ALL WARRANTIES.
#
###Revision String
# SVN: $Id$

###Package Definition
package provide barchart.element

package require rbc
namespace import rbc::*

namespace eval barchart.element {
	# ------------------------------------------------------------------------------------
	# Purpose: Ensure the element activate command works correctly when given a valid
	# element name.
	# ------------------------------------------------------------------------------------
	proc RBC.barchart.element.activate.M.1.1.Setup {} {
		barchart .barchart1
		pack .barchart1
		.barchart1 element create Element1 -data {1 1 2 2 3 3}
	}
	
	proc RBC.barchart.element.activate.M.1.1.Body {} {
		.barchart1 element activate Element1
	}
	
	proc RBC.barchart.element.activate.M.1.1.Cleanup {} {
		.barchart1 element delete Element1
		destroy .barchart1
	}
}