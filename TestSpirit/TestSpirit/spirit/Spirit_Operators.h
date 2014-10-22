/*=======================================================================================
	Parser operators

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
#ifndef __Spirit_Operators__
#define __Spirit_Operators__
#include <spirit/Spirit_Composite.h>
#include <spirit/Spirit_Primitives.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Sequence: a >> b; Matches a and b in sequence
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Sequence : public Binary<A, B>, public Parser<Sequence<A, B> > {

	Sequence(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	s = scanner;
		Match	ma, mb;
		if ((ma = this->SubjectA().Parse(s)) && (mb = this->SubjectB().Parse(s)))
		{
			scanner = s;
			return ma + mb;
		}
		return Match();
	}
};

//////////////////////////////////
template <typename A, typename B>
inline Sequence<A, B>
operator >> (Parser<A> const& a, Parser<B> const& b)
{
	return Sequence<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, ChLit<char> >
operator >> (Parser<A> const& a, char b)
{
	return Sequence<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<ChLit<char>, B>
operator >> (char a, Parser<B> const& b)
{
	return Sequence<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, StrLit<char> >
operator >> (Parser<A> const& a, char const* b)
{
	return Sequence<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<StrLit<char>, B>
operator >> (char const* a, Parser<B> const& b)
{
	return Sequence<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, ChLit<wchar_t> >
operator >> (Parser<A> const& a, wchar_t b)
{
	return Sequence<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<ChLit<wchar_t>, B>
operator >> (wchar_t a, Parser<B> const& b)
{
	return Sequence<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, StrLit<wchar_t> >
operator >> (Parser<A> const& a, wchar_t const* b)
{
	return Sequence<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<StrLit<wchar_t>, B>
operator >> (wchar_t const* a, Parser<B> const& b)
{
	return Sequence<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Sequential-and: a && b; Same as a >> b;
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
inline Sequence<A, B>
operator && (Parser<A> const& a, Parser<B> const& b)
{
	return Sequence<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, ChLit<char> >
operator && (Parser<A> const& a, char b)
{
	return Sequence<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<ChLit<char>, B>
operator && (char a, Parser<B> const& b)
{
	return Sequence<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, StrLit<char> >
operator && (Parser<A> const& a, char const* b)
{
	return Sequence<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<StrLit<char>, B>
operator && (char const* a, Parser<B> const& b)
{
	return Sequence<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, ChLit<wchar_t> >
operator && (Parser<A> const& a, wchar_t b)
{
	return Sequence<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<ChLit<wchar_t>, B>
operator && (wchar_t a, Parser<B> const& b)
{
	return Sequence<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Sequence<A, StrLit<wchar_t> >
operator && (Parser<A> const& a, wchar_t const* b)
{
	return Sequence<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Sequence<StrLit<wchar_t>, B>
operator && (wchar_t const* a, Parser<B> const& b)
{
	return Sequence<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Sequential-or: a || b; Matches a or b in sequence
//
//	Equivalent to:	a | b | a >> b;
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct SequentialOr : public Binary<A, B>, public Parser<SequentialOr<A, B> > {

	SequentialOr(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	s = scanner;
		Match	ma, mb;
		if ((ma = this->SubjectA().Parse(s)) || (mb = this->SubjectB().Parse(s)))
		{
			scanner = s;
			return ma + mb;
		}
		return Match();
	}
};

//////////////////////////////////
template <typename A, typename B>
inline SequentialOr<A, B>
operator || (Parser<A> const& a, Parser<B> const& b)
{
	return SequentialOr<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline SequentialOr<A, ChLit<char> >
operator || (Parser<A> const& a, char b)
{
	return SequentialOr<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline SequentialOr<ChLit<char>, B>
operator || (char a, Parser<B> const& b)
{
	return SequentialOr<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline SequentialOr<A, StrLit<char> >
operator || (Parser<A> const& a, char const* b)
{
	return SequentialOr<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline SequentialOr<StrLit<char>, B>
operator || (char const* a, Parser<B> const& b)
{
	return SequentialOr<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline SequentialOr<A, ChLit<wchar_t> >
operator || (Parser<A> const& a, wchar_t b)
{
	return SequentialOr<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline SequentialOr<ChLit<wchar_t>, B>
operator || (wchar_t a, Parser<B> const& b)
{
	return SequentialOr<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline SequentialOr<A, StrLit<wchar_t> >
operator || (Parser<A> const& a, wchar_t const* b)
{
	return SequentialOr<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline SequentialOr<StrLit<wchar_t>, B>
operator || (wchar_t const* a, Parser<B> const& b)
{
	return SequentialOr<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Alternative: a | b; Matches a or b.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Alternative : public Binary<A, B>, public Parser<Alternative<A, B> > {

	Alternative(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (Match match = this->SubjectA().Parse(scanner))
			return match;
		return this->SubjectB().Parse(scanner);
	}
};

//////////////////////////////////
template <typename A, typename B>
inline Alternative<A, B>
operator | (Parser<A> const& a, Parser<B> const& b)
{
	return Alternative<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Alternative<A, ChLit<char> >
operator | (Parser<A> const& a, char b)
{
	return Alternative<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Alternative<ChLit<char>, B>
operator | (char a, Parser<B> const& b)
{
	return Alternative<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Alternative<A, StrLit<char> >
operator | (Parser<A> const& a, char const* b)
{
	return Alternative<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Alternative<StrLit<char>, B>
operator | (char const* a, Parser<B> const& b)
{
	return Alternative<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Alternative<A, ChLit<wchar_t> >
operator | (Parser<A> const& a, wchar_t b)
{
	return Alternative<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Alternative<ChLit<wchar_t>, B>
operator | (wchar_t a, Parser<B> const& b)
{
	return Alternative<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Alternative<A, StrLit<wchar_t> >
operator | (Parser<A> const& a, wchar_t const* b)
{
	return Alternative<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Alternative<StrLit<wchar_t>, B>
operator | (wchar_t const* a, Parser<B> const& b)
{
	return Alternative<StrLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
#ifdef MSVC_SIMULATE_PARTIAL_SPECIALIZATION
namespace Impl {
	//////////////////////////////////
	//	Determine at compile time (without partial specialization) whether
	//	a given type is an instance of the Alternative<A,B> template above.
	//////////////////////////////////
	template <typename T>
	class IsSpiritAlternative
	{
		template <typename A, typename B>
		static char Test_ (Alternative<A,B>);	// no implementation
		static int	Test_ ( ... );				// no implementation
	public:
		enum { Test = sizeof(char) == sizeof(Test_(*(T*)0)) };
	};
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Intersection: a & b; Matches a and b.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Intersection : public Binary<A, B>, public Parser<Intersection<A, B> > {

	Intersection(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	ls = scanner;
		if (Match l = this->SubjectA().Parse(ls))
		{
			ScannerT	rs = scanner;
			if (Match r = this->SubjectB().Parse(rs))
			{
				bool	less = l.Length() < r.Length();
				scanner = less ? rs : ls;
				return less ? r : l;
			}
		}

		return Match();
	}
};

//////////////////////////////////
template <typename A, typename B>
inline Intersection<A, B>
operator & (Parser<A> const& a, Parser<B> const& b)
{
	return Intersection<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Intersection<A, ChLit<char> >
operator & (Parser<A> const& a, char b)
{
	return Intersection<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Intersection<ChLit<char>, B>
operator & (char a, Parser<B> const& b)
{
	return Intersection<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Intersection<A, StrLit<char> >
operator & (Parser<A> const& a, char const* b)
{
	return Intersection<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Intersection<StrLit<char>, B>
operator & (char const* a, Parser<B> const& b)
{
	return Intersection<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Intersection<A, ChLit<wchar_t> >
operator & (Parser<A> const& a, wchar_t b)
{
	return Intersection<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Intersection<ChLit<wchar_t>, B>
operator & (wchar_t a, Parser<B> const& b)
{
	return Intersection<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Intersection<A, StrLit<wchar_t> >
operator & (Parser<A> const& a, wchar_t const* b)
{
	return Intersection<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Intersection<StrLit<wchar_t>, B>
operator & (wchar_t const* a, Parser<B> const& b)
{
	return Intersection<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Difference: a - b; Matches a but not b
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Difference : public Binary<A, B>, public Parser<Difference<A, B> > {

	Difference(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	ls = scanner;
		ScannerT	rs = scanner;
		Match	match;
		if ((match = this->SubjectA().Parse(ls)) && !this->SubjectB().Parse(rs))
		{
			scanner = ls;
			return match;
		}
		return Match();
	}
};

//////////////////////////////////
template <typename A, typename B>
inline Difference<A, B>
operator - (Parser<A> const& a, Parser<B> const& b)
{
	return Difference<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Difference<A, ChLit<char> >
operator - (Parser<A> const& a, char b)
{
	return Difference<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Difference<ChLit<char>, B>
operator - (char a, Parser<B> const& b)
{
	return Difference<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Difference<A, StrLit<char> >
operator - (Parser<A> const& a, char const* b)
{
	return Difference<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Difference<StrLit<char>, B>
operator - (char const* a, Parser<B> const& b)
{
	return Difference<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Difference<A, ChLit<wchar_t> >
operator - (Parser<A> const& a, wchar_t b)
{
	return Difference<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Difference<ChLit<wchar_t>, B>
operator - (wchar_t a, Parser<B> const& b)
{
	return Difference<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Difference<A, StrLit<wchar_t> >
operator - (Parser<A> const& a, wchar_t const* b)
{
	return Difference<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Difference<StrLit<wchar_t>, B>
operator - (wchar_t const* a, Parser<B> const& b)
{
	return Difference<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Xor: a ~ b; Matches a or b but not both
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A, typename B>
struct Xor : public Binary<A, B>, public Parser<Xor<A, B> > {

	Xor(A const& a, B const& b) : Binary<A, B>(a, b) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		ScannerT	ls = scanner;
		ScannerT	rs = scanner;
		Match	l = this->SubjectA().Parse(ls);
		Match	r = this->SubjectB().Parse(rs);

		if (l ^ r)
		{
			scanner = l ? ls : rs;
			return l ? l : r;
		}
		
		return Match();
	}
};

//////////////////////////////////
template <typename A, typename B>
inline Xor<A, B>
operator ^ (Parser<A> const& a, Parser<B> const& b)
{
	return Xor<A, B>(a.GetDerived(), b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Xor<A, ChLit<char> >
operator ^ (Parser<A> const& a, char b)
{
	return Xor<A, ChLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Xor<ChLit<char>, B>
operator ^ (char a, Parser<B> const& b)
{
	return Xor<ChLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Xor<A, StrLit<char> >
operator ^ (Parser<A> const& a, char const* b)
{
	return Xor<A, StrLit<char> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Xor<StrLit<char>, B>
operator ^ (char const* a, Parser<B> const& b)
{
	return Xor<StrLit<char>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Xor<A, ChLit<wchar_t> >
operator ^ (Parser<A> const& a, wchar_t b)
{
	return Xor<A, ChLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Xor<ChLit<wchar_t>, B>
operator ^ (wchar_t a, Parser<B> const& b)
{
	return Xor<ChLit<wchar_t>, B>(a, b.GetDerived());
}

//////////////////////////////////
template <typename A>
inline Xor<A, StrLit<wchar_t> >
operator ^ (Parser<A> const& a, wchar_t const* b)
{
	return Xor<A, StrLit<wchar_t> >(a.GetDerived(), b);
}

//////////////////////////////////
template <typename B>
inline Xor<StrLit<wchar_t>, B>
operator ^ (wchar_t const* a, Parser<B> const& b)
{
	return Xor<StrLit<wchar_t>, B>(a, b.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Optional: !a; Matches a zero (0) or one (1) time.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
struct Optional : public Unary<A>, public Parser<Optional<A> > {

	Optional(A const& a) : Unary<A>(a) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		Match	r = this->Subject().Parse(scanner);
#ifdef __GNUC__
        if (r) return r; else return Match(0);
#else
		return r ? r : Match(0);
#endif
	}
};

//////////////////////////////////
template <typename A>
Optional<A>
operator ! (Parser<A> const& a)
{
	return Optional<A>(a.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	KleeneStar: *a; Matches a zero (0) or more times.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
struct KleeneStar : public Unary<A>, public Parser<KleeneStar<A> > {

	KleeneStar(A const& a) : Unary<A>(a) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		Match first(0);
		while (Match next = this->Subject().Parse(scanner))
			first += next;
		return first;
	}
};

//////////////////////////////////
template <typename A>
inline KleeneStar<A>
operator * (Parser<A> const& a)
{
	return KleeneStar<A>(a.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Positive: +a; Matches a one (1) or more times.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename A>
struct Positive : public Unary<A>, public Parser<Positive<A> > {

	Positive(A const& a) : Unary<A>(a) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		Match	first = this->Subject().Parse(scanner);
		if (first)
			while (Match next = this->Subject().Parse(scanner))
				first += next;
		return first;
	}
};

//////////////////////////////////
template <typename A>
inline Positive<A>
operator + (Parser<A> const& a)
{
	return Positive<A>(a.GetDerived());
}

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
