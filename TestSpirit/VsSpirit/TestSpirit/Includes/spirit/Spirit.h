/*=======================================================================================
	Master header file

	Copyright (c) 2001, Joel de Guzman
	Isis Technologies. All rights reserved.
	URL:	isis-tech.n3.net
	Email:	isis-tech@usa.net

	MSVC code: Copyright (c) 2001, Bruce Florman

	This software is provided 'as-is', without any express or implied
	warranty. In no event will the copyright holder be held liable for 
	any damages arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute 
	it freely, subject to the following restrictions:

	1.	The origin of this software must not be misrepresented; you must 
		not claim that you wrote the original software. If you use this 
		software in a product, an acknowledgment in the product documentation 
		would be appreciated but is not required.

	2.	Altered source versions must be plainly marked as such, and must 
		not be misrepresented as being the original software.

	3.	This notice may not be removed or altered from any source 
		distribution.
=======================================================================================*/
#ifndef __Spirit__
#define __Spirit__

/////////////////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#	include "Spirit_Config_MSVC.h"
//#elif defined(__SOME_OTHER_COMPILER_NEEDING_MAJOR_CONFIGURATION__)
//#	include "Spirit_Config_SomeOtherCompiler.h"
#endif

#include <spirit/Spirit_Action.h>
#include <spirit/Spirit_Basics.h>
#include <spirit/Spirit_Composite.h>
#include <spirit/Spirit_Directives.h>
#include <spirit/Spirit_Operators.h>
#include <spirit/Spirit_Iterators.h>
#include <spirit/Spirit_Parser.h>
#include <spirit/Spirit_Primitives.h>
#include <spirit/Spirit_Rule.h>
#include <spirit/Spirit_Scanner.h>
#include <spirit/Spirit_Numerics.h>
/////////////////////////////////////////////////////////////////////////////////////////

#endif

/*=======================================================================================
	History
	
	JDG:		Joel de Guzman
	VP:			Vladimir Prus
	BF:			Bruce Florman
	CMP:		Colin McPhail
	DN:			Dan Nuffer
	CH:			Changze Han

	8/28/1999	Original Implementation [ run time polymorphic version ] (JDG)
	4/30/2001	Template meta-programming implementation (JDG)
	5/13/2001	Major redesign using iterators (JDG)
	5/25/2001	Port to G++3.0 and BCC 5.5.1 (VP)
	5/26/2001	Port to MSVC 6.0 + Stlport (BF)
	5/27/2001	Bug fixes in Difference and Xor classes (JDG)
	5/29/2001	Changed non-const extern globals to const (BF)
	5/30/2001	Added Iterators (JDG)
	5/26/2001	Port to GCC 2.95.2 (DN)
	6/1/2001	Bruce Florman's port without STLport (CH)
	6/1/2001	Bug Fix in Match class (CMP)
	6/1/2001	Bug Fix in Intersection class (BF)
	6/2/2001	Changed Action syntax to [] (JDG)
	6/2/2001	Added <Spirit_Numerics.h> (JDG)
	6/4/2001	Fixed Rule's copy constructor and assignment to allow aliasing. (JDG)
	6/5/2001	Common code base. Fused common compiler versions into a single
				code base. Tested on BCC 5.5.1, CW5.3 and GCC 2.95.2. (JDG)
	6/9/2001	Fused MSVC 6.0 code into the common code base (BF)
=======================================================================================*/
