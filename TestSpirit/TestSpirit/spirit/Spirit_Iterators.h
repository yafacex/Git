/*=======================================================================================
	The Parser Iterators

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
#ifndef __Spirit_Iterators__
#define __Spirit_Iterators__
#include <cassert>
#include <spirit/Spirit_Parser.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
class FixedIterator : public Unary<A>, public Parser<FixedIterator<A> > {

public:
					FixedIterator(A const& a, uint n_)
					: Unary<A>(a), n(n_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (n == 0)
			return Match();

		ScannerT	s = scanner;
		Match 	match(0);

		for (uint i = 0; i < n; ++i)
		{
			Match next = this->Subject().Parse(s);
			if (!next)
				return Match();
			match += next;
		}

		scanner = s;
		return match;
	}

private:

	uint	n;
};


/////////////////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
class FiniteIterator : public Unary<A>, public Parser<FiniteIterator<A> > {

public:
					FiniteIterator(A const& a, uint from_, uint until_)
					: Unary<A>(a), from(from_), until(until_) { assert(from < until); }

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	s = scanner;
		Match 	match(0);

		for (uint i = 0; i < until; ++i)
		{
			Match next = this->Subject().Parse(s);
			if (!next)
				if (i >= from)
					break;
				else
					return Match();
			match += next;
		}

		scanner = s;
		return match;
	}

private:

	uint	from;
	uint	until;
};


/////////////////////////////////////////////////////////////////////////////////////////
//
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
class InfiniteIterator : public Unary<A>, public Parser<InfiniteIterator<A> > {

public:
					InfiniteIterator(A const& a, uint n_)
					: Unary<A>(a), n(n_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	s = scanner;
		Match 	match(0);

		for (uint i = 0;; ++i)
		{
			Match next = this->Subject().Parse(s);
			if (!next)
				if (i >= n)
					break;
				else
					return Match();
			match += next;
		}

		scanner = s;
		return match;
	}

private:

	uint	n;
};


/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif

