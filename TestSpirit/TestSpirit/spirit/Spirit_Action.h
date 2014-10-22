/*=======================================================================================
	Semantic actions

	Copyright (c) 2001, Joel de Guzman
	Isis Technologies. All rights reserved.
	URL:	isis-tech.n3.net
	Email:	isis-tech@usa.net

	Semantic actions

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
#ifndef __Spirit_Action__
#define __Spirit_Action__
#include <spirit/Spirit_Basics.h>
#include <spirit/Spirit_Composite.h>
#include <spirit/Spirit_Parser.h>
#include <spirit/Spirit_Scanner.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Action class 
//	
/////////////////////////////////////////////////////////////////////////////////////////
template <typename P, typename A>
class Action : public Unary<P>, public Parser<Action<P, A> > {

public:
	
	Action(P const& a, A const& action_) : Unary<P>(a), action(action_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		typedef Impl::IterOf<ScannerT> IterOf;
		typename IterOf::Iterator begin = IterOf::Get(scanner);
		if (Match match = this->Subject().Parse(scanner))
		{
			action(begin, IterOf::Get(scanner));
			return match;
		}
		return Match();
	}

private:

	A	action;
};

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
