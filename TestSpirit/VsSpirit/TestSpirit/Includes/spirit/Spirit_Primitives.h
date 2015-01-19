/*=======================================================================================
	Parser primitives

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
#ifndef __Spirit_Primitives__
#define __Spirit_Primitives__
#include <cassert>
#include <cctype>
#if __GNUC__ > 2
    #include <cwctype>
#endif
#include <string>
#include <spirit/Spirit_Basics.h>
#include <spirit/Spirit_Parser.h>
#include <spirit/Spirit_Scanner.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
//
//	ChLit class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class ChLit : public Parser<ChLit<Char> > {

public:
					ChLit(Char ch_)
					: ch(ch_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (ch == *scanner)
		{
			++scanner;
			return Match(1);
		}
		return Match();
	}

	private: Char	ch;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Range class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class Range : public Parser<Range<Char> > {

public:
					Range(Char first_, Char last_)
					: first(first_), last(last_) { assert(first <= last); }

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (bool r = (*scanner >= first) && (*scanner <= last))
		{
			++scanner;
			return Match(1);
		}
		return Match();
	}

private:

	Char	first;
	Char	last;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	StrLit class
//
//	[ Note:	StrLit objects do not hold unique copies of the string
//			passed to its constructors. Only the pointers are held. 
//			Typically StrLit objects are constructed with literal
//			strings. If not, it is the client's responsibility to 
//			ensure that the string passed in remains valid throughout 
//			the lifetime of the object.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class StrLit : public Parser<StrLit<Char> > {

public:
					StrLit(Char const* str, uint len) 
					: first(str), last(str + len) {}

					StrLit(Char const* str)
#if __GNUC__ == 2
					: first(str), last(str + std::string_char_traits<Char>::length(str)) {}
#else
					: first(str), last(str + std::char_traits<Char>::length(str)) {}
#endif

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
        typedef typename Impl::IterOf<ScannerT>::Iterator    Iter;
		Iter&	start = Impl::IterOf<ScannerT>::Get(scanner);
		Iter	iter = start;

		for (Char const* strFirst = first; strFirst < last; ++strFirst, ++iter)
			if (*strFirst != *iter)
				return Match();
		start = iter;
		return Match(last-first);
	}

private:
	
	Char const*	first;
	Char const*	last;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	NCChLit class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class NCChLit : public Parser<NCChLit<Char> > {

public:
					NCChLit(Char ch_)
					: ch(std::tolower(ch_)) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (ch == std::tolower(*scanner))
		{
			++scanner;
			return Match(1);
		}
		return Match();
	}

	private: Char	ch;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	NCRange class
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class NCRange : public Parser<NCRange<Char> > {

public:
					NCRange(Char first_, Char last_)
					: first(std::tolower(first_)), last(std::tolower(last_))
					{ assert(first <= last); }

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		Char	ch = std::tolower(*scanner);
		if (bool r = (ch >= first) && (ch <= last))
		{
			++scanner;
			return Match(1);
		}
		return Match();
	}

private:

	Char			first;
	Char			last;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	NCStrLit class.
//
//	[ Note:	NCStrLit objects do not hold unique copies of the string
//			passed to its constructors. Only the pointers are held. 
//			Typically NCStrLit objects are constructed with literal
//			strings. If not, it is the client's responsibility to 
//			ensure that the string passed in remains valid throughout 
//			the lifetime of the object.
//
//			The constructor expects a string in lower case. It is a 
//			checked run-time error to pass in a string with upper-case 
//			characters. ]
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename Char = char>
class NCStrLit : public Parser<NCStrLit<Char> > {

public:
					NCStrLit(Char const* str, uint len) 
					: first(str), last(str + len) { assert(CheckCase()); }

					NCStrLit(Char const* str)
#if __GNUC__ == 2
					: first(str), last(str + std::string_char_traits<Char>::length(str))
#else
					: first(str), last(str + std::char_traits<Char>::length(str))
#endif
					{ assert(CheckCase()); }
	
	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
        typedef typename Impl::IterOf<ScannerT>::Iterator    Iter;
		Iter&	start = Impl::IterOf<ScannerT>::Get(scanner);
		Iter	iter = start;

		for (Char const* strFirst = first; strFirst < last; ++strFirst, ++iter)
			if (*strFirst != std::tolower(*iter))
				return Match();
		start = iter;
		return Match(last-first);
	}

private:

	bool
	CheckCase() const
	{
		for (Char const* s = first; s != last; s++)
			if (*s != std::tolower(*s))
				return false;
		return true;
	}

	Char const*	first;
	Char const*	last;
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Predefined parser primitives
//
/////////////////////////////////////////////////////////////////////////////////////////
struct ChLitParserGen {

	template <typename Char>
	ChLit<Char> operator()(Char ch) const { return ChLit<Char>(ch); }
	
};

/////////////////////////////////////////////////////////////////////////////////////////
struct RangeParserGen {

	template <typename Char>
	Range<Char> operator()(Char first, Char last) const { return Range<Char>(first, last); }
	
};

struct StrLitParserGen {

	template <typename Char>
	StrLit<Char> operator()(Char const* str) const { return StrLit<Char>(str); }
	
};

/////////////////////////////////////////////////////////////////////////////////////////
struct NCChLitParserGen {

	template <typename Char>
	NCChLit<Char> operator()(Char ch) const { return NCChLit<Char>(ch); }
	
};

/////////////////////////////////////////////////////////////////////////////////////////
struct NCRangeParserGen {

	template <typename Char>
	NCRange<Char> operator()(Char first, Char last) const { return NCRange<Char>(first, last); }
	
};

struct NCStrLitParserGen {

	template <typename Char>
	NCStrLit<Char> operator()(Char const* str) const { return NCStrLit<Char>(str); }
	
};

/////////////////////////////////////////////////////////////////////////////////////////
template <typename Derived>
struct CharTest : public Parser<CharTest<Derived> > {

	Derived&		GetDerived()		{ return *static_cast<Derived*>(this); }
	Derived const&	GetDerived() const	{ return *static_cast<Derived const*>(this); }

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		if (bool r = GetDerived().Test(*scanner))
		{
			++scanner;
			return Match(1);
		}
		return Match();
	}
};

/////////////////////////////////////////////////////////////////////////////////////////
struct AnyChar_ : public Parser<AnyChar_> {

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		++scanner;
		return Match(1);
	}
};

/////////////////////////////////////////////////////////////////////////////////////////
struct Nothing_ : public Parser<Nothing_> {

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		return Match();
	}
};

/////////////////////////////////////////////////////////////////////////////////////////
struct Epsilon_ : public Parser<Epsilon_> {

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		return Match(0);
	}
};

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Convenience functions
//
/////////////////////////////////////////////////////////////////////////////////////////
// On some systems the is* functions are defined as macros
#ifndef isalnum
inline bool isalnum(char c)		{ return std::isalnum(c); }
#endif
#ifndef isalpha
inline bool isalpha(char c)		{ return std::isalpha(c); }
#endif
#ifndef iscntrl
inline bool iscntrl(char c)		{ return std::iscntrl(c); }
#endif
#ifndef isdigit
inline bool isdigit(char c)		{ return std::isdigit(c); }
#endif
#ifndef isgraph
inline bool isgraph(char c)		{ return std::isgraph(c); }
#endif
#ifndef islower
inline bool islower(char c)		{ return std::islower(c); }
#endif
#ifndef isprint
inline bool isprint(char c)		{ return std::isprint(c); }
#endif
#ifndef ispunct
inline bool ispunct(char c)		{ return std::ispunct(c); }
#endif
#ifndef isspace
inline bool isspace(char c)		{ return std::isspace(c); }
#endif
#ifndef isupper
inline bool isupper(char c)		{ return std::isupper(c); }
#endif
#ifndef isxdigit
inline bool isxdigit(char c)	{ return std::isxdigit(c); }
#endif

#ifndef isalnum
inline bool isalnum(wchar_t c)	{ return std::iswalnum(c); }
#endif
#ifndef isalpha
inline bool isalpha(wchar_t c)	{ return std::iswalpha(c); }
#endif
#ifndef iscntrl
inline bool iscntrl(wchar_t c)	{ return std::iswcntrl(c); }
#endif
#ifndef isdigit
inline bool isdigit(wchar_t c)	{ return std::iswdigit(c); }
#endif
#ifndef isgraph
inline bool isgraph(wchar_t c)	{ return std::iswgraph(c); }
#endif
#ifndef islower
inline bool islower(wchar_t c)	{ return std::iswlower(c); }
#endif
#ifndef isprint
inline bool isprint(wchar_t c)	{ return std::iswprint(c); }
#endif
#ifndef ispunct
inline bool ispunct(wchar_t c)	{ return std::iswpunct(c); }
#endif
#ifndef isspace
inline bool isspace(wchar_t c)	{ return std::iswspace(c); }
#endif
#ifndef isupper
inline bool isupper(wchar_t c)	{ return std::iswupper(c); }
#endif
#ifndef isxdigit
inline bool isxdigit(wchar_t c)	{ return std::iswxdigit(c); }
#endif

/////////////////////////////////////////////////////////////////////////////////////////
struct AlNum_ : public CharTest<AlNum_>
{ template <typename Char> bool Test(Char ch) const { return isalnum(ch); } };

struct Alpha_ : public CharTest<Alpha_>
{ template <typename Char> bool Test(Char ch) const { return isalpha(ch); } };

struct Cntrl_ : public CharTest<Cntrl_>
{ template <typename Char> bool Test(Char ch) const { return iscntrl(ch); } };

struct Digit_ : public CharTest<Digit_>
{ template <typename Char> bool Test(Char ch) const { return isdigit(ch); } };

struct Graph_ : public CharTest<Graph_>
{ template <typename Char> bool Test(Char ch) const { return isgraph(ch); } };

struct Lower_ : public CharTest<Lower_>
{ template <typename Char> bool Test(Char ch) const { return islower(ch); } };

struct Print_ : public CharTest<Print_>
{ template <typename Char> bool Test(Char ch) const { return isprint(ch); } };

struct Punct_ : public CharTest<Punct_>
{ template <typename Char> bool Test(Char ch) const { return ispunct(ch); } };

struct Space_ : public CharTest<Space_>
{ template <typename Char> bool Test(Char ch) const { return isspace(ch); } };

struct Upper_ : public CharTest<Upper_>
{ template <typename Char> bool Test(Char ch) const { return isupper(ch); } };

struct XDigit_ : public CharTest<XDigit_>
{ template <typename Char> bool Test(Char ch) const { return isxdigit(ch); } };

/////////////////////////////////////////////////////////////////////////////////////////
const ChLitParserGen	ch_p 		= ChLitParserGen();
const RangeParserGen	range_p		= RangeParserGen();
const StrLitParserGen	str_p 		= StrLitParserGen();
const NCChLitParserGen	ncch_p 		= NCChLitParserGen();
const NCRangeParserGen	ncrange_p	= NCRangeParserGen();
const NCStrLitParserGen	ncstr_p 	= NCStrLitParserGen();

const AnyChar_			anychar		= AnyChar_();
const Nothing_			nothing		= Nothing_();
const Epsilon_			epsilon		= Epsilon_();

const AlNum_			alnum 		= AlNum_();
const Alpha_			alpha 		= Alpha_();
const Cntrl_			cntrl 		= Cntrl_();
const Digit_			digit 		= Digit_();
const Graph_			graph 		= Graph_();
const Lower_			lower 		= Lower_();
const Print_			print 		= Print_();
const Punct_			punct 		= Punct_();
const Space_			space 		= Space_();
const Upper_			upper 		= Upper_();
const XDigit_			xdigit 		= XDigit_();

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
