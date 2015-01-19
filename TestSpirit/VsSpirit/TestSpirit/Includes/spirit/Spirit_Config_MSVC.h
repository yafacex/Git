/*=======================================================================================
	Copyright (c) 2001, Bruce Florman

	Configuration code for using Spirit with Microsoft Visual C++.

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
#ifndef __Spirit_Config_MSVC__
#define __Spirit_Config_MSVC__

#ifndef _MSC_VER
#error Configuration file does not match the compiler.
#endif

#pragma warning( disable : 4284 ) // return type for -> not a UDT
#pragma warning( disable : 4786 ) // identifier truncated in debug info
#pragma warning( disable : 4800 ) // int to bool performance warning

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cwctype>
#include <iterator>

#if _MSC_VER > 1200
#pragma message("%%% Does MSVC support partial specialization yet?")
#endif
#define MSVC_SIMULATE_PARTIAL_SPECIALIZATION

#if _MSC_VER > 1200
#pragma message("%%% Does MSVC put the C stdlib names in the std namespace yet?")
#endif
#if ! defined(__SGI_STL_PORT) \
 || ( __SGI_STL_PORT < 0x415 &&  ( defined(_STLPORT_NO_CSTD_FUNCTION_IMPORTS) \
								|| ! defined(_STLPORT_IMPORT_VENDOR_CSTD) \
								 ) ) \
 || ( __SGI_STL_PORT >= 0x415 && ( defined(_STLP_NO_CSTD_FUNCTION_IMPORTS) \
								|| ! defined(_STLP_IMPORT_VENDOR_CSTD) \
								 ) )
	#define MSVC_IMPORT_STDLIB_NAMES_INTO_STD
#endif

////////////////////////////////////////////////////////////////////////////////
namespace std {

#ifdef MSVC_IMPORT_STDLIB_NAMES_INTO_STD
    using ::isalnum;
    using ::isalpha;
    using ::iscntrl;
    using ::isdigit;
    using ::isgraph;
    using ::islower;
    using ::isprint;
    using ::ispunct;
    using ::isspace;
    using ::isupper;
    using ::isxdigit;
	using ::toupper;
	using ::tolower;

	using ::iswalnum;
	using ::iswalpha;
	using ::iswcntrl;
	using ::iswdigit;
	using ::iswgraph;
	using ::iswlower;
	using ::iswprint;
	using ::iswpunct;
	using ::iswspace;
	using ::iswupper;
	using ::iswxdigit;
	using ::towupper;
	using ::towlower;

	using ::memmove;
	using ::memcpy;
	using ::memchr;
	using ::strchr;
	using ::strpbrk;
	using ::strrchr;
	using ::strstr;
	using ::memcmp;
	using ::memset;
	using ::strcat;
	using ::strcmp;
	using ::strcoll;
	using ::strcpy;
	using ::strcspn;
	using ::strerror;
	using ::strlen;
	using ::strncat;
	using ::strncmp;
	using ::strncpy;
	using ::strspn;
	using ::strtok;
	using ::strxfrm;

	using ::acos;
	using ::asin;
	using ::atan2;
	using ::atan;
	using ::ceil;
	using ::cos;
	using ::cosh;
	using ::exp;
	using ::fabs;
	using ::floor;
	using ::fmod;
	using ::frexp;
	using ::ldexp;
	using ::log10;
	using ::log;
	using ::modf;
	using ::pow;
	using ::sin;
	using ::sinh;
	using ::sqrt;
	using ::tan;
	using ::tanh;

	using ::div_t;
	using ::ldiv_t;
	using ::size_t;
	using ::abort;
	using ::atexit;
	using ::exit;
	using ::getenv;
	using ::calloc;
	using ::free;
	using ::malloc;
	using ::realloc;
	using ::atof;
	using ::atoi;
	using ::atol;
	using ::mblen;
	using ::mbstowcs;
	using ::mbtowc;
	using ::strtod;
	using ::strtol;
	using ::strtoul;
	using ::system;
	using ::bsearch;
	using ::qsort;
	using ::abs;
	using ::div;
	using ::labs;
	using ::ldiv;
	using ::rand;
	using ::srand;
#endif // MSVC_IMPORT_STDLIB_NAMES_INTO_STD

	template<>
	struct iterator_traits<char const*>
	{
		typedef random_access_iterator_tag  iterator_category;
		typedef char                        value_type;
		typedef ptrdiff_t                   difference_type;
		typedef char const*                 pointer;
		typedef char const&                 reference;
	};

	template<>
	struct iterator_traits<char*>
	{
		typedef random_access_iterator_tag  iterator_category;
		typedef char                        value_type;
		typedef ptrdiff_t                   difference_type;
		typedef char*                       pointer;
		typedef char&                       reference;
	};

	template<>
	struct iterator_traits<wchar_t const*>
	{
		typedef random_access_iterator_tag  iterator_category;
		typedef wchar_t                     value_type;
		typedef ptrdiff_t                   difference_type;
		typedef wchar_t const*              pointer;
		typedef wchar_t const&              reference;
	};

	template<>
	struct iterator_traits<wchar_t*>
	{
		typedef random_access_iterator_tag  iterator_category;
		typedef wchar_t                     value_type;
		typedef ptrdiff_t                   difference_type;
		typedef wchar_t*                    pointer;
		typedef wchar_t&                    reference;
	};

} // namespace std

#ifdef MSVC_SIMULATE_PARTIAL_SPECIALIZATION
namespace Spirit {

	namespace Impl {

		// The technique for simulating partial specialization below is
		// used according to the Adobe Open Source License Version 1.0.
		//	 (c) Copyright 2000 Adobe Systems Incorporated and others.
		//	 All rights reserved.
		//	 Authors: Mat Marcus and Jesse Jones
		//	 The original version of this source code may be found at
		//	 http://opensource.adobe.com.
		//
		// This version and the original also contain functions derived
		// from chapter 10 of the book _Generative_Programming_ by
		// Krzysztof Czarnecki & Ulrich Eisenecker, which are
		//	 (c) Copyright 1998-2000 Krzysztof Czarnecki & Ulrich Eisenecker

		////////////////////////////////////////////////////////////////////////
		// Types to represent Boolean values to the type system.

		struct True_  { enum { Value = 1 }; };
		struct False_ { enum { Value = 0 }; };

		template<bool Cond_> struct BoolToType_ 	  { typedef False_ Type; };
		template<>			 struct BoolToType_<true> { typedef True_  Type; };

		////////////////////////////////////////////////////////////////////////
		// The type If_<Condition_,Then_,Else_>::Type is equivalent to either
		// the Then_ type or the Else_ type, depending on the (compile-time
		// constant) value of Condition_.

		template< bool Condition_, typename Then_, typename Else_ > struct If_;

		struct SelectThen
		{
			template< typename Then_, typename Else_ >
			struct One { typedef Then_ Type; };
		};

		struct SelectElse
		{
			template< typename Then_, typename Else_ >
			struct One { typedef Else_ Type; };
		};

		template< bool Cond_ > struct Select	   { typedef SelectElse Ret; };
		template<>			   struct Select<true> { typedef SelectThen Ret; };

		template< bool Condition_, typename Then_, typename Else_ >
		struct If_
		{
			// VC6sp4 chokes without the intermediate typedef here.
			typedef typename Select<Condition_>::Ret	  Sel;
			typedef typename Sel::One<Then_, Else_>::Type Type;
		};

		////////////////////////////////////////////////////////////////////////
		//	IsPtrType<T>
		//
		//	The expression IsPtrType<T>::Test is a compile-time constant
		//	with a value of either 1 or 0 depending on whether or not T is
		//	a pointer type.  As such, it is appropriate for use as the
		//	Condition_ parameter for the If_ template above.
		//
		//	The expression IsPtrType<T>::QueryType() has a type of either
		//	True_ or False_ depending on whether or not T is a pointer
		//	type.  This is useful for simulating partial specialization
		//	for function templates.

		template< typename T >
		class IsPtrType
		{	// The C++ language specifies that the compiler will implicitly
			// apply a maximum of one user-defined conversion.	The conversion
			// from void* to Shim below is a user-defined conversion, so a
			// user-defined type will not convert to Shim even if it provides
			// a conversion to const void*.
			struct Shim { Shim (void volatile const*); }; // no implementation
			static char Test_ (Shim);  // no implementation
			static int	Test_ ( ... ); // no implementation
		public:
			enum { Test = sizeof(char) == sizeof(Test_(*(T*)0)) };
			typedef typename BoolToType_<Test>::Type Type;
			static Type QueryType () { return Type(); }
		};

		////////////////////////////////////////////////////////////////////////
		//	IsSameType<A,B>
		//
		//	The expression IsSameType<A,B>::Test is a compile-time constant
		//	with a value of either 1 or 0 depending on whether or not A and
		//	B name the same type.  As such, it is appropriate for use as the
		//	Condition_ parameter for the If_ template above.
		//
		//	The expression IsSameType<A,B>::QueryType() has a type of either
		//	True_ or False_ depending on whether or not A and B name the same
		//	type.  This is useful for simulating partial specialization for
		//	function templates.

		template< typename A, typename B > struct IsSameType;

		template< typename A >
		struct CompareTypes_
		{
			template< typename B > struct With { typedef False_ Type; };

			template<> struct With<A> { typedef True_ Type; };
		};

		template< typename A, typename B >
		struct IsSameType
		{
			typedef typename CompareTypes_<A>::With<B>::Type Type;
			enum { Test = Type::Value };
			static Type QueryType () { return Type(); }
		};

		////////////////////////////////////////////////////////////////////////
		//	IsDerivedFrom<D,B>
		//
		//	The expression IsDerivedFrom<D,B>::Test is a compile-time constant
		//	with a value of either 1 or 0 depending on whether or not D is
		//	derived from B.  As such, it is appropriate for use as the
		//	Condition_ parameter for the If_ template above.
		//
		//	The expression IsDerivedFrom<A,B>::QueryType() has a type of either
		//	True_ or False_ depending on whether or not D is a type derived
		//	from B.  This is useful for simulating partial specialization for
		//	function templates.

		template< typename D, typename B >
		class IsDerivedFrom
		{
			struct Shim { Shim (B volatile const&); };	// no implementation
			static char Test_ (Shim);	// no implementation
			static int  Test_ ( ... );	// no implementation
		public:
			enum { Test = sizeof(char) == sizeof(Test_(*(D*)0)) };
			typedef typename BoolToType_<Test>::Type Type;
			static Type QueryType () { return Type(); }
		};

	} // namespace Impl

} // namespace Spirit
#endif // MSVC_SIMULATE_PARTIAL_SPECIALIZATION

////////////////////////////////////////////////////////////////////////////////
#endif // __Spirit_Config_MSVC__
