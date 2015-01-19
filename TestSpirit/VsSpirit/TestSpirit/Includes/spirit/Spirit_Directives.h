/*=======================================================================================
	Parser directives

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
======================================================================================*/
#ifndef __Spirit_Directives__
#define __Spirit_Directives__
#include <spirit/Spirit_Composite.h>
#include <spirit/Spirit_Operators.h>
#include <spirit/Spirit_Parser.h>
#include <spirit/Spirit_Scanner.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Contiguous class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
struct Contiguous 
: 	public Unary<A>, 
	public Parser<Contiguous<A> > {

	Contiguous(A const& a) : Unary<A>(a) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		return this->Subject().Parse(Impl::IterOf<ScannerT>::Get(scanner));
	}
};

//////////////////////////////////
struct Lexeme_ {

	template <typename A>
	Contiguous<A>
	operator [] (Parser<A> const& a) const
	{
		return Contiguous<A>(a.GetDerived());
	}

};

const Lexeme_ Lexeme = Lexeme_();

/////////////////////////////////////////////////////////////////////////////////////////
//
//	LongestAlt class
//
/////////////////////////////////////////////////////////////////////////////////////////

template <typename A, typename B>
struct LongestAlt 
:	public Binary<A, B>, 
	public Parser<LongestAlt<A, B> > {

	LongestAlt(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	ls = scanner;
		ScannerT	rs = scanner;
		Match	l = this->SubjectA().Parse(ls);
		Match	r = this->SubjectB().Parse(rs);

		if (l || r)
		{
			bool less = l.Length() < r.Length();
			scanner = less ? rs : ls;
			return less ? r : l;
		}

		return Match();
	}
};

//////////////////////////////////
namespace Impl {

#if ! defined(MSVC_SIMULATE_PARTIAL_SPECIALIZATION)

	//////////////////////////////////
	template <typename T>
	struct ToLongest {

		typedef T RT;

		static RT const& Convert(T const& a) { return a; }
	};

	//////////////////////////////////
	template <typename A, typename B>
	struct ToLongest<Alternative<A, B> > {

		typedef typename ToLongest<A>::RT	AT;
		typedef typename ToLongest<B>::RT	BT;
		typedef LongestAlt<AT, BT>	RT;

		static RT Convert(Alternative<A, B> const& alt)
		{
			return RT(ToLongest<A>::Convert(alt.SubjectA()), ToLongest<B>::Convert(alt.SubjectB()));
		}
	};

		//////////////////////////////////
#else	// MSVC_SIMULATE_PARTIAL_SPECIALIZATION
		//////////////////////////////////

	template <typename T> struct Select_ToLongest;

	template <typename T>
	struct ToLongest {

		typedef typename Select_ToLongest<T>::RT	RT;

		static RT Convert(T const& a);

		typedef typename Select_ToLongest<T>::XT	XT;
		typedef typename Select_ToLongest<T>::YT	YT;
	};

	//////////////////////////////////
	template <typename T>
	struct ToLongest_Generic {

		typedef T const&	RT;
		typedef T			XT;
		typedef False_		YT;
	};

	template <typename T>
	inline T const&
	ToLongestConvert(T const& a, False_) { return a; }

	//////////////////////////////////
	template <typename T>
	struct ToLongest_Alternative {

		typedef typename ToLongest<T::TypeA>::XT	AT;
		typedef typename ToLongest<T::TypeB>::XT	BT;
		typedef LongestAlt<AT, BT>	RT;

		typedef RT					XT;
		typedef True_				YT;
	};

	template <typename A, typename B>
	inline typename ToLongest<Alternative<A, B> >::RT
	ToLongestConvert(Alternative<A, B> const& alt, True_)
	{
		typedef typename ToLongest<Alternative<A, B> >::RT RT;
		return RT(ToLongest<A>::Convert(alt.SubjectA()), ToLongest<B>::Convert(alt.SubjectB()));
	}

	//////////////////////////////////
	template <typename T>
	inline typename ToLongest<T>::RT
	ToLongest<T>::Convert (T const& a)
	{
		return ToLongestConvert(a, ToLongest<T>::YT());
	}

	//////////////////////////////////
	template <typename T>
	struct Select_ToLongest {

		typedef typename If_< IsSpiritAlternative<T>::Test
							, ToLongest_Alternative<T>
							, ToLongest_Generic<T>
							>::Type Type;

		typedef typename Type::RT RT;
		typedef typename Type::XT XT;
		typedef typename Type::YT YT;
	};

#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

} // namespace Impl;

//////////////////////////////////
struct Longest_ {

	template <typename A, typename B>
	typename Impl::ToLongest<Alternative<A, B> >::RT
	operator [] (Alternative<A, B> const& alt) const
	{
		return Impl::ToLongest<Alternative<A, B> >::Convert(alt);
	}

};

const Longest_ Longest = Longest_();

/////////////////////////////////////////////////////////////////////////////////////////
//
//	ShortestAlt class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct ShortestAlt 
: 	public Binary<A, B>, 
	public Parser<ShortestAlt<A, B> > {

	ShortestAlt(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	ls = scanner;
		ScannerT	rs = scanner;
		Match	l = this->SubjectA().Parse(ls);
		Match	r = this->SubjectB().Parse(rs);

		if (l || r)
		{
			bool less = l.Length() < r.Length();
			scanner = less ? ls : rs;
			return less ? l : r;
		}

		return Match();
	}
};

//////////////////////////////////
namespace Impl {

#if ! defined(MSVC_SIMULATE_PARTIAL_SPECIALIZATION)

	//////////////////////////////////
	template <typename T>
	struct ToShortest {

		typedef T RT;

		static RT const& Convert(T const& a) { return a; }
	};

	//////////////////////////////////
	template <typename A, typename B>
	struct ToShortest<Alternative<A, B> > {

		typedef typename ToShortest<A>::RT	AT;
		typedef typename ToShortest<B>::RT	BT;
		typedef ShortestAlt<AT, BT>	RT;

		static RT Convert(Alternative<A, B> const& alt)
		{
			return RT(ToShortest<A>::Convert(alt.SubjectA()), ToShortest<B>::Convert(alt.SubjectB()));
		}
	};

		//////////////////////////////////
#else	// MSVC_SIMULATE_PARTIAL_SPECIALIZATION
		//////////////////////////////////

	template <typename T> struct Select_ToShortest;

	template <typename T>
	struct ToShortest {

		typedef typename Select_ToShortest<T>::RT	RT;

		static RT Convert(T const& a);

		typedef typename Select_ToShortest<T>::XT	XT;
		typedef typename Select_ToShortest<T>::YT	YT;
	};

	//////////////////////////////////
	template <typename T>
	struct ToShortest_Generic {

		typedef T const&	RT;
		typedef	T			XT;
		typedef False_		YT;
	};

	template <typename T>
	inline T const&
	ToShortestConvert(T const& a, False_) { return a; }

	//////////////////////////////////
	template <typename T>
	struct ToShortest_Alternative {

		typedef typename ToShortest<T::TypeA>::XT	AT;
		typedef typename ToShortest<T::TypeB>::XT	BT;
		typedef ShortestAlt<AT, BT>	RT;

		typedef RT					XT;
		typedef True_				YT;
	};

	template <typename A, typename B>
	inline typename ToShortest<Alternative<A, B> >::RT
	ToShortestConvert(Alternative<A, B> const& alt, True_)
	{
		typedef typename ToShortest<Alternative<A, B> >::RT RT;
		return RT(ToShortest<A>::Convert(alt.SubjectA()), ToShortest<B>::Convert(alt.SubjectB()));
	}

	//////////////////////////////////
	template <typename T>
	inline typename ToShortest<T>::RT
	ToShortest<T>::Convert (T const& a)
	{
		return ToShortestConvert(a, ToShortest<T>::YT());
	}

	//////////////////////////////////
	template <typename T>
	struct Select_ToShortest {

		typedef typename If_< IsSpiritAlternative<T>::Test
							, ToShortest_Alternative<T>
							, ToShortest_Generic<T>
							>::Type Type;

		typedef typename Type::RT RT;
		typedef typename Type::XT XT;
		typedef typename Type::YT YT;
	};

#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

} // namespace Impl

//////////////////////////////////
struct Shortest_ {

	template <typename A, typename B>
	typename Impl::ToShortest<Alternative<A, B> >::RT
	operator [] (Alternative<A, B> const& alt) const
	{
		return Impl::ToShortest<Alternative<A, B> >::Convert(alt);
	}

};

const Shortest_ Shortest = Shortest_();

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
