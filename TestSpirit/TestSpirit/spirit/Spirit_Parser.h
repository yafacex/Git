/*=======================================================================================
	The Parser

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
#ifndef __Spirit_Parser__
#define __Spirit_Parser__
#include <spirit/Spirit_Basics.h>
#include <spirit/Spirit_Composite.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Parser class.
//
//	This class is a protocol base class for all parsers. This is 
//	essentially an interface contract. The Parser class does not 
//	really know how to parse anything but instead relies on the 
//	template parameter Derived (which obviously is assumed to be a 
//	subclass) to do the actual parsing. Concrete sub-classes 
//	inheriting from this must have a corresponding member function 
//	Parse(...) compatible with the conceptual Interface:
//
//		template <typename ScannerT>
//		Match
//		Parse(ScannerT& scanner) const;
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A> class FixedIterator;
template <typename A> class FiniteIterator;
template <typename A> class InfiniteIterator;
template <typename P, typename A> class Action;

struct More_ {};
More_ const more = More_();

//////////////////////////////////
template <typename Derived>
struct Parser {

	typedef FixedIterator<Derived>		FixedIter;
	typedef FiniteIterator<Derived>		FiniteIter;
	typedef InfiniteIterator<Derived>	InfiniteIter;

						Parser() {}

	template <typename A>
	Action<Derived, A>	operator [] (A const& action) const		{ return Action<Derived, A>(GetDerived(), action); }

	FixedIter			operator () (uint n) const				{ return FixedIter(GetDerived(), n); }
	FiniteIter			operator () (uint n1, uint n2) const	{ return FiniteIter(GetDerived(), n1, n2); }
	InfiniteIter		operator () (uint n, More_) const		{ return InfiniteIter(GetDerived(), n); }

	FixedIter			Repeat(uint n) const					{ return FixedIter(GetDerived(), n); }
	FiniteIter			Repeat(uint n1, uint n2) const			{ return FiniteIter(GetDerived(), n1, n2); }
	InfiniteIter		Repeat(uint n, More_) const				{ return InfiniteIter(GetDerived(), n); }

	Derived&			GetDerived()							{ return *static_cast<Derived*>(this); }
	Derived const&		GetDerived() const						{ return *static_cast<Derived const*>(this); }
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Match class. This is the class that the Parser's 
//	Parse(...) member function returns.
//
/////////////////////////////////////////////////////////////////////////////////////////
class Match {

public:
						Match()				: data(-1) {}
	explicit			Match(uint length)	: data(length) {}
	
						operator bool() const 				{ return data >= 0; }
	Match&				operator += (Match const& other)	{ data += other.data; return *this; }
	int					Length() const 						{ return data; }
					
private:

	int					data;
};

/////////////////////////////////////////////////////////////////////////////////////////
inline Match operator + (Match const& a, Match const& b)
{ return Match(a) += b; }

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif

