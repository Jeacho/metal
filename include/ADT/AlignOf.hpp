//--- AlignOf.hpp - Class for Memory Alignment ----------------------- C++ ---//
//
//  Memory alignment with MSVC support.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_ALIGNOF_HPP
#define METAL_ADT_ALIGNOF_HPP

#include <cstddef>

#ifndef __has_feature
# define __has_feature(x) 0
#endif

/// \macro LLVM_GNUC_PREREQ
/// \brief Extend the default __GNUC_PREREQ even if glibc's features.h isn't
/// available.
#ifndef LLVM_GNUC_PREREQ
# if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#  define LLVM_GNUC_PREREQ(maj, min, patch) \
    ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) + __GNUC_PATCHLEVEL__ >= \
     ((maj) << 20) + ((min) << 10) + (patch))
# elif defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define LLVM_GNUC_PREREQ(maj, min, patch) \
    ((__GNUC__ << 20) + (__GNUC_MINOR__ << 10) >= ((maj) << 20) + ((min) << 10))
# else
#  define LLVM_GNUC_PREREQ(maj, min, patch) 0
# endif
#endif

/// \macro LLVM_ALIGNAS
/// \brief Used to specify a minimum alignment for a structure or variable.
#if __GNUC__ && !__has_feature(cxx_alignas) && !LLVM_GNUC_PREREQ(4, 8, 1)
# define LLVM_ALIGNAS(x) __attribute__((aligned(x)))
#else
# define LLVM_ALIGNAS(x) alignas(x)
#endif

/* \struct AlignedCharArray
** \brief Helper for building an aligned character array type.
**
** This template is used to explicitly build up a collection of aligned
** character array types. We have to build these up using a macro and explicit
** specialization to cope with MSVC (at least till 2015) where only an
** integer literal can be used to specify an alignment constraint. Once built
** up here, we can then begin to indirect between these using normal C++
** template parameters.
*/

// MSVC requires special handling here.
#ifndef _MSC_VER

template<std::size_t Alignment, std::size_t Size>
struct AlignedCharArray {
	LLVM_ALIGNAS(Alignment) char buffer[Size];
};

#else // _MSC_VER

/// \brief Create a type with an aligned char buffer.
template<std::size_t Alignment, std::size_t Size>
struct AlignedCharArray;

template<std::size_t Size>
struct AlignedCharArray<1, Size> {
	union {
		char aligned;
		char buffer[Size];
	};
};

template<std::size_t Size>
struct AlignedCharArray<2, Size> {
	union {
		short aligned;
		char buffer[Size];
	};
};

template<std::size_t Size>
struct AlignedCharArray<4, Size> {
	union {
		int aligned;
		char buffer[Size];
	};
};

template<std::size_t Size>
struct AlignedCharArray<8, Size> {
	union {
		double aligned;
		char buffer[Size];
	};
};

// The rest of these are provided with a __declspec(align(...)) and we simply
// can't pass them by-value as function arguments on MSVC.
#define LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(x) \
  template<std::size_t Size> \
  struct AlignedCharArray<x, Size> { \
    __declspec(align(x)) char buffer[Size]; \
  };

LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(16)
LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(32)
LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(64)
LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT(128)

#undef LLVM_ALIGNEDCHARARRAY_TEMPLATE_ALIGNMENT

#endif // _MSC_VER

namespace detail {
template <typename T1,
          typename T2 = char, typename T3 = char, typename T4 = char,
          typename T5 = char, typename T6 = char, typename T7 = char,
          typename T8 = char, typename T9 = char, typename T10 = char>
class AlignerImpl {
	T1 t1; T2 t2; T3 t3; T4 t4; T5 t5; T6 t6; T7 t7; T8 t8; T9 t9; T10 t10;

	AlignerImpl() = delete;
};

template <typename T1,
          typename T2 = char, typename T3 = char, typename T4 = char,
          typename T5 = char, typename T6 = char, typename T7 = char,
          typename T8 = char, typename T9 = char, typename T10 = char>
union SizerImpl {
	char arr1[sizeof(T1)], arr2[sizeof(T2)], arr3[sizeof(T3)], arr4[sizeof(T4)],
	     arr5[sizeof(T5)], arr6[sizeof(T6)], arr7[sizeof(T7)], arr8[sizeof(T8)],
	     arr9[sizeof(T9)], arr10[sizeof(T10)];
};
} // end namespace detail

/// \brief This union template exposes a suitably aligned and sized character
/// array member which can hold elements of any of up to ten types.
///
/// These types may be arrays, structs, or any other types. The goal is to
/// expose a char array buffer member which can be used as suitable storage for
/// a placement new of any of these types. Support for more than ten types can
/// be added at the cost of more boilerplate.
template <typename T1,
          typename T2 = char, typename T3 = char, typename T4 = char,
          typename T5 = char, typename T6 = char, typename T7 = char,
          typename T8 = char, typename T9 = char, typename T10 = char>
struct AlignedCharArrayUnion : AlignedCharArray<
    alignof(detail::AlignerImpl<T1, T2, T3, T4, T5,
                                      T6, T7, T8, T9, T10>),
    sizeof(detail::SizerImpl<T1, T2, T3, T4, T5,
                                     T6, T7, T8, T9, T10>)> {
};

#endif // METAL_ADT_ALIGNOF_HPP
