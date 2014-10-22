/*=======================================================================================
	Basic types and constants

	Copyright (c) 2001, Joel de Guzman
	Isis Technologies. All rights reserved.
	URL:	isis-tech.n3.net
	Email:	isis-tech@usa.net

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
#ifndef __Spirit_Basics__
#define __Spirit_Basics__
#include <climits>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

	typedef unsigned int	uint;	//	unsigned integer
	
	uint const	char_bits 	= CHAR_BIT;
	uint const	uint_bits 	= char_bits * sizeof(uint);
	uint const	max_uint 	= UINT_MAX;
	int const	max_int 	= INT_MAX;
	int const	min_int 	= INT_MIN;

	#ifndef nil
	#define nil 0
	#endif

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
