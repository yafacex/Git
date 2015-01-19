/*=======================================================================================
	The Scanner

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
#ifndef __Spirit_Scanner__
#define __Spirit_Scanner__
#include <iterator>

/////////////////////////////////////////////////////////////////////////////////////////
namespace Spirit {

struct Space_;
/////////////////////////////////////////////////////////////////////////////////////////
//
//	Scanner class declaration
//
/////////////////////////////////////////////////////////////////////////////////////////
template <typename ParserType_ = Space_, typename Iterator_ = char const*>
class Scanner {

public:

	typedef Iterator_						Iterator;
	typedef ParserType_						ParserType;
	typedef std::iterator_traits<Iterator>	IterTraits;

	typedef typename IterTraits::difference_type	difference_type;
	typedef typename IterTraits::value_type			value_type;
	typedef typename IterTraits::pointer			pointer;
	typedef typename IterTraits::reference			reference;
	typedef typename IterTraits::iterator_category	iterator_category;

						Scanner(Iterator const& start, ParserType const& skip);

	Iterator&			Iter() const;
	reference			operator * () const;
	pointer				operator -> () const;
	Scanner&			operator ++ ();
	Scanner				operator ++ (int);

	friend bool			operator == (Scanner const& a, Scanner const& b) 	{ return a.start == b.start; }
	friend bool			operator != (Scanner const& a, Scanner const& b) 	{ return a.start != b.start; }

private:

	void				Next() const;
	pointer				Get() const;
		
	ParserType const*	skip;
	mutable bool		dirty;
	mutable Iterator	start;
};

#ifdef MSVC_SIMULATE_PARTIAL_SPECIALIZATION
	//////////////////////////////////
	//	Determine at compile time (without partial specialization) whether
	//	a given type is an instance of the Scanner template above.
	//////////////////////////////////
namespace Impl {
	template <typename S_>
	class IsSpiritScanner
	{
		template <typename P_, typename I_>
		static char Test_ (Scanner<P_,I_>);	// no implementation
		static int	Test_ ( ... );			// no implementation
	public:
		enum { Test = sizeof(char) == sizeof(Test_(*(S_*)0)) };
	};
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////
//
//	Implementation
//
/////////////////////////////////////////////////////////////////////////////////////////
namespace Impl {

#if ! defined(MSVC_SIMULATE_PARTIAL_SPECIALIZATION)

	//////////////////////////////////
	//	Helper class to strip the scanner 
	//	wrapper off an iterator.
	//////////////////////////////////
	template <typename T>
	struct IterOf {

		typedef T Iterator;

		static Iterator&
		Get(Iterator& ptr)
		{ return ptr; }
	};

	//////////////////////////////////
	template <typename ParserType, typename Iterator_>
	struct IterOf<Scanner<ParserType, Iterator_> > {

		typedef typename Scanner<ParserType, Iterator_>::Iterator Iterator;

		static Iterator&
		Get(Scanner<ParserType, Iterator> const& scanner)
		{ return scanner.Iter(); }
	};

#else // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

	//////////////////////////////////
	template <typename T>
	struct IterOf_Generic {

		typedef T Iterator;

		static Iterator&
		Get(Iterator& ptr)
		{ return ptr; }
	};

	//////////////////////////////////
	template <typename T>
	struct IterOf_Scanner {

		typedef typename T::Iterator Iterator;

		static Iterator&
		Get(T const& scanner)
		{ return scanner.Iter(); }
	};

	//////////////////////////////////
	template <typename T>
	struct IterOf : If_< IsSpiritScanner<T>::Test
					   , IterOf_Scanner<T>
					   , IterOf_Generic<T>
					   >::Type
	{ };

#endif // ! MSVC_SIMULATE_PARTIAL_SPECIALIZATION

} // namespace Impl

//////////////////////////////////
template <typename ParserType, typename Iterator>
inline Scanner<ParserType, Iterator>::Scanner(
	Iterator const& start_, ParserType const& skip_)
: skip(&skip_), dirty(true), start(start_) {}

//////////////////////////////////
template <typename ParserType, typename Iterator>
inline void	Scanner<ParserType, Iterator>::Next() const
{
	if (dirty)
	{
		dirty = false; 
		while (skip->Parse(start)) 
			;
	}
}

//////////////////////////////////
template <typename ParserType, typename Iterator>
inline typename Scanner<ParserType, Iterator>::pointer
Scanner<ParserType, Iterator>::Get() const
{
	Next(); 
	return start;
}

//////////////////////////////////
template <typename ParserType, typename Iterator>
inline Iterator&
Scanner<ParserType, Iterator>::Iter() const			
{
	Next();
	dirty = true;
	return start;
}
	
//////////////////////////////////
template <typename ParserType, typename Iterator>
inline typename Scanner<ParserType, Iterator>::reference
Scanner<ParserType, Iterator>::operator * () const		
{
	return *Get();
}
	
//////////////////////////////////
template <typename ParserType, typename Iterator>
inline typename Scanner<ParserType, Iterator>::pointer
Scanner<ParserType, Iterator>::operator -> () const	
{
	return Get();
}
	
//////////////////////////////////
template <typename ParserType, typename Iterator>
inline Scanner<ParserType, Iterator>&
Scanner<ParserType, Iterator>::operator ++ ()			
{
	++start; 
	dirty = true; 
	return *this;
}
	
//////////////////////////////////
template <typename ParserType, typename Iterator>
inline Scanner<ParserType, Iterator>
Scanner<ParserType, Iterator>::operator ++ (int)		
{
	Scanner sc(*this); 
	++start; 
	dirty = true; 
	return sc;
}

/////////////////////////////////////////////////////////////////////////////////////////
}	//	namespace Spirit

#endif
