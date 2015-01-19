/*=======================================================================================
	Composite parsers

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
#ifndef __Spirit_Composite__
#define __Spirit_Composite__

#include <spirit/Spirit_Scanner.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

template <typename ScannerT = Scanner<> > class Rule; // forward declaration

#ifdef MSVC_SIMULATE_PARTIAL_SPECIALIZATION
namespace Impl {

	//////////////////////////////////
	//	Determine at compile time (without partial specialization) whether
	//	a given type is an instance of (or is derived from an instance of)
	//	the Rule template above.
	//////////////////////////////////
	template <typename T>
	class IsSpiritRule
	{
		template <typename S>
		static char Test_ (Rule<S>*);	// no implementation
		static int	Test_ ( ... );		// no implementation
	public:
		enum { Test = sizeof(char) == sizeof(Test_((T*)0)) };
	};

} // namespace Impl
#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION


/////////////////////////////////////////////////////////////////////////////////////////
//
//	EmbedTrait
//
/////////////////////////////////////////////////////////////////////////////////////////
#if ! defined(MSVC_SIMULATE_PARTIAL_SPECIALIZATION)

template <typename T>
struct EmbedTrait { typedef T Type; };

template <typename ScannerT>
struct EmbedTrait<Rule<ScannerT> > { typedef Rule<ScannerT> const& Type; };

#else // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

template <typename T>
struct EmbedTrait_Generic { typedef T Type; };

template <typename T>
struct EmbedTrait_Rule { typedef T const& Type; };

template <typename T>
struct EmbedTrait : Impl::If_< Impl::IsSpiritRule<T>::Test
							 , EmbedTrait_Rule<T>
							 , EmbedTrait_Generic<T>
							 >::Type
{ };

#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Unary class. Class composed of a single subject.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
struct Unary {

					Unary()				: a() {}
					Unary(A const& a_)	: a(a_) {}
	A&				Subject()			{ return a; }
	A const&		Subject() const		{ return a; }

private:

	typename EmbedTrait<A>::Type	a;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Binary class. Class composed of a pair.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Binary {

#ifdef MSVC_SIMULATE_PARTIAL_SPECIALIZATION
	typedef A TypeA;
	typedef B TypeB;
#endif

					Binary() {}
					Binary(A const& a_, B const& b_)
					: a(a_), b(b_) {}

	A&				SubjectA() 			{ return a; }
	A const&		SubjectA() const	{ return a; }
	B&				SubjectB() 			{ return b; }
	B const&		SubjectB() const	{ return b; }

private:

	typename EmbedTrait<A>::Type	a;
	typename EmbedTrait<B>::Type	b;
};

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
