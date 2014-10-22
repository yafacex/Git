/*=======================================================================================
	The Production Rule

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
#ifndef __Spirit_Rule__
#define __Spirit_Rule__
#include <cassert>
#include <spirit/Spirit_Parser.h>
#include <spirit/Spirit_Basics.h>
#include <spirit/Spirit_Composite.h>
#include <spirit/Spirit_Operators.h>
#include <spirit/Spirit_Scanner.h>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

namespace Impl {

#if ! defined(MSVC_SIMULATE_PARTIAL_SPECIALIZATION)
	//////////////////////////////////
	template <typename ScannerT, typename Iterator = typename Impl::IterOf<ScannerT>::Iterator>
	class AbstractParser {

	public:
							AbstractParser() {}
		virtual				~AbstractParser() {}
		virtual Match		Parse(ScannerT& scanner) const = 0;
		virtual Match		Parse(Iterator& scanner) const = 0;
	};

	//////////////////////////////////
	template <typename ScannerT>
	class AbstractParser<ScannerT, ScannerT> {

	public:
							AbstractParser() {}
		virtual				~AbstractParser() {}
		virtual Match		Parse(ScannerT& scanner) const = 0;
	};

	//////////////////////////////////
	template <typename T, typename ScannerT, typename Iterator = typename Impl::IterOf<ScannerT>::Iterator>
	class ConcreteParser : public T, public AbstractParser<ScannerT, Iterator> {

	public:
							ConcreteParser(T const& parser) : T(parser) {}
		virtual				~ConcreteParser() {}
		virtual Match		Parse(ScannerT& scanner) const	{ return T::Parse(scanner); }
		virtual Match		Parse(Iterator& scanner) const	{ return T::Parse(scanner); }
	};

	//////////////////////////////////
	template <typename T, typename ScannerT>
	class ConcreteParser<T, ScannerT, ScannerT> : public T, public AbstractParser<ScannerT> {

	public:
							ConcreteParser(T const& parser) : T(parser) {}
		virtual				~ConcreteParser() {}
		virtual Match		Parse(ScannerT& scanner) const	{ return T::Parse(scanner); }
	};

	//////////////////////////////////
#else // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

	template <typename ScannerT, typename Iterator>
	class AbstractParser_2 {

	public:
							AbstractParser_2() {}
		virtual				~AbstractParser_2() {}
		virtual Match		Parse(ScannerT& scanner) const = 0;
		virtual Match		Parse(Iterator& scanner) const = 0;
	};

	//////////////////////////////////
	template <typename ScannerT>
	class AbstractParser_1 {

	public:
							AbstractParser_1() {}
		virtual				~AbstractParser_1() {}
		virtual Match		Parse(ScannerT& scanner) const = 0;
	};

	//////////////////////////////////
	template <typename ScannerT, typename Iterator = IterOf<ScannerT>::Iterator>
	class AbstractParser
	:	public If_< IsSameType<ScannerT, Iterator>::Test
				  , AbstractParser_1<ScannerT>
				  , AbstractParser_2<ScannerT, Iterator>
				  >::Type
	{ };

	//////////////////////////////////
	template <typename T, typename ScannerT, typename Iterator>
	class ConcreteParser_2 : public T, public AbstractParser<ScannerT, Iterator> {

	public:
							ConcreteParser_2(T const& parser) : T(parser) {}
		virtual				~ConcreteParser_2() {}
		virtual Match		Parse(ScannerT& scanner) const	{ return T::Parse(scanner); }
		virtual Match		Parse(Iterator& scanner) const	{ return T::Parse(scanner); }
	};

	//////////////////////////////////
	template <typename T, typename ScannerT>
	class ConcreteParser_1 : public T, public AbstractParser<ScannerT> {

	public:
							ConcreteParser_1(T const& parser) : T(parser) {}
		virtual				~ConcreteParser_1() {}
		virtual Match		Parse(ScannerT& scanner) const	{ return T::Parse(scanner); }
	};

	//////////////////////////////////
	template <typename T, typename ScannerT, typename Iterator = Impl::IterOf<ScannerT>::Iterator>
	class ConcreteParser
	:	public If_< IsSameType<ScannerT, Iterator>::Test
				  , ConcreteParser_1<T, ScannerT>
				  , ConcreteParser_2<T, ScannerT, Iterator>
				  >::Type
	{
		typedef If_< IsSameType<ScannerT, Iterator>::Test
				, ConcreteParser_1<T, ScannerT>
				, ConcreteParser_2<T, ScannerT, Iterator>
				>::Type Base;
	public:
		ConcreteParser (T const& parser)
		:	Base(parser)
		{
		}
	};

#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

} // namespace Impl

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Rule class.
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename ScannerT>
class Rule : public Parser<Rule<ScannerT> > {

public:

	typedef typename Impl::IterOf<ScannerT>::Iterator Iterator;

	Rule()
	:	isAlias(false),
		meta(nil)
	{
	}

	~Rule()
	{
		if (!isAlias)
			delete meta;
	}

	Rule(Rule const& rule)
	:	Parser<Rule<ScannerT> >(rule),
		isAlias(true),
		alias(&rule)
	{
	}

	Rule& operator = (Rule const& rule)
	{
		assert(meta == nil);
		alias = &rule;
		isAlias = true;
		return *this;
	}

	template <typename T>
	Rule(T const& parser)
	: 	isAlias(false),
		meta(new Impl::ConcreteParser<T, ScannerT>(parser))
	{
	}

	template <typename T>
	Rule& operator = (T const& parser)
	{
		assert(meta == nil);
		meta = new Impl::ConcreteParser<T, ScannerT>(parser);
		isAlias = false;
		return *this;
	}

	template <typename Scanner_>
	Match
	Parse(Scanner_& scanner) const
	{
		if (meta)
			return isAlias ? alias->Parse(scanner) : meta->Parse(scanner);
		return Match();
	}


public:
	// anon. union below is not a friend to this class, so Meta typedef is
	// not visible when declared in the union, unless Meta is public.
	typedef Impl::AbstractParser<ScannerT>	Meta;

private:

	union {

#ifdef __BORLANDC__
		mutable Meta*	meta;
#else
		Meta*			meta;
#endif
		Rule const*		alias;
	};
	
	bool	isAlias;
};

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
