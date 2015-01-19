/*=======================================================================================
	Numeric parsers

	copyright (c) 2001, Joel de Guzman
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
#ifndef __Spirit_Numerics__
#define __Spirit_Numerics__
#include <cmath>
#include <spirit/Spirit_Primitives.h>
#include <spirit/Spirit_Scanner.h>


/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T = uint>
struct UIntParser : public Parser<UIntParser<T> > {

	UIntParser(T& n_)
	: n(n_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		n = 0;

		typename Impl::IterOf<ScannerT>::Iterator&	start = Impl::IterOf<ScannerT>::Get(scanner);
		typename Impl::IterOf<ScannerT>::Iterator 	iter = start;

		uint	count = 0;
		if (!isdigit(*iter))
			return Match();

		while (isdigit(*iter))
		{
			n *= 10;
			n += *iter - '0';
			++iter;
			++count;
		}

		start = iter;
		return Match(count);		
	}
	
	T&	n;
};

/////////////////////////////////////////////////////////////////////////////////////////
struct UIntParserGen {

	template <typename T>
	UIntParser<T> operator()(T& n) const { return UIntParser<T>(n); }
	
};

const UIntParserGen	uint_p = UIntParserGen();

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T = int>
struct IntParser : public Parser<IntParser<T> > {

	IntParser(T& n_)
	: n(n_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		n = 0;

		typename Impl::IterOf<ScannerT>::Iterator&	start = Impl::IterOf<ScannerT>::Get(scanner);
		typename Impl::IterOf<ScannerT>::Iterator 	iter = start;

		bool	neg = false;
		uint	count = 0;

		if (*iter == '-')
		{
			neg = true;
			++iter;
			++count;
		}

		else if (*iter == '+')
		{
			++iter;
			++count;
		}
			
		if (!isdigit(*iter))
			return Match();

		while (isdigit(*iter))
		{
			n *= 10;
			n += *iter - '0';
			++iter;
			++count;
		}

		if (neg)
			n = -n;

		start = iter;
		return Match(count);		
	}

	T&	n;
};


/////////////////////////////////////////////////////////////////////////////////////////
struct IntParserGen {

	template <typename T>
	IntParser<T> operator()(T& n) const { return IntParser<T>(n); }
	
};

const IntParserGen	int_p = IntParserGen();

/////////////////////////////////////////////////////////////////////////////////////////
template <typename T> struct RealTraits {};

#ifdef __MWERKS__

template <> struct RealTraits<float>		{ static float pow(float x, float y) { return std::powf(x, y); } };
template <> struct RealTraits<double>		{ static double pow(double x, double y) { return std::pow(x, y); } };
template <> struct RealTraits<long double>	{ static double pow(long double x, long double y) { return std::powl(x, y); } };

#else

template <> struct RealTraits<float>		{ static float pow(float x, float y) { return static_cast<float>(std::pow(x, y)); } };
template <> struct RealTraits<double>		{ static double pow(double x, double y) { return std::pow(x, y); } };
template <> struct RealTraits<long double>	{ static double pow(long double x, long double y) { return std::pow(x, y); } };

#endif
/////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct RealParser : public Parser<RealParser<T> > {

	RealParser(T& n_)
	: n(n_) {}

	template <typename ScannerT>
	Match
	Parse(ScannerT& scanner) const
	{
		n = 0;

		typename Impl::IterOf<ScannerT>::Iterator&	start = Impl::IterOf<ScannerT>::Get(scanner);
		typename Impl::IterOf<ScannerT>::Iterator 	iter = start;

		bool	neg = false;
		uint	count = 0;
		int		frac = 0;

		if (*iter == '-')
		{
			neg = true;
			++iter;
			++count;
		}

		else if (*iter == '+')
		{
			++iter;
			++count;
		}
			
		if (!(isdigit(*iter) || *iter == '.'))
			return Match();

		while (isdigit(*iter))
		{
			n *= 10;
			n += *iter - '0';
			++iter;
			++count;
		}

		if (*iter == '.')
		{
			++iter;
			++count;

			while (isdigit(*iter))
			{
				n *= 10;
				n += *iter - '0';
				++iter;
				++count;
				++frac;
			}
		}

		Match	match(count);
		int		exp = 0;

		if (Match mexp = (NCChLit<>('e') >> int_p(exp)).Parse(iter))
			match += mexp;

		n *= RealTraits<T>::pow(10, exp - frac);
		if (neg)
			n = -n;

		start = iter;
		return match;		
	}

	T&	n;
};

/////////////////////////////////////////////////////////////////////////////////////////
struct RealParserGen {

	template <typename T>
	RealParser<T> operator()(T& n) const { return RealParser<T>(n); }
	
};

const RealParserGen	real_p = RealParserGen();

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
