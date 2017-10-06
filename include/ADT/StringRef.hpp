//--- StringRef.hpp - C-String Wrapper ------------------------------- C++ ---//
//
//  This file defines the StringRef class which wraps a C-String with
// std::string methods.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_STRINGREF_HPP
#define METAL_ADT_STRINGREF_HPP

#include "ADT/IteratorRange.hpp"

#include <cassert>
#include <string>
#include <cstddef>

class StringRef {
public:
	static const size_t npos = ~size_t(0);

	using iterator = const char *;
	using const_iterator = const char *;
	using size_type = size_t;

private:
	/// The start of the string, in an external buffer.
	const char *StrData = nullptr;

	/// The length of the string.
	size_t Length;

public:
	/// Construct an empty string ref.
	/*implicit*/ StringRef() = default;

	/// Disable conversion from nullptr.  This prevents things like
	/// if (S == nullptr)
	StringRef(std::nullptr_t) = delete;

	inline StringRef(const char *StrData, size_t length = 1)
		: StrData(StrData), Length(length) { }

	// Name iterators
	iterator Begin() const { return StrData; }
	iterator End() const { return StrData + Length - 1; }

	const unsigned char *BytesBegin() const {
		return reinterpret_cast<const unsigned char *>(Begin());
	}

	const unsigned char *BytesEnd() const {
		return reinterpret_cast<const unsigned char *>(End());
	}

	iterator_range<const unsigned char *> Bytes() const {
		return make_range(BytesBegin(), BytesEnd());
	}

	inline const char *Data() const { return StrData; }

	std::string Str() const {
		if (!StrData) return std::string();
		return std::string(StrData, Length);
	}

	/// Disallow accidental assignment from a temporary std::string.
	///
	/// The declaration here is extra complicated so that `stringRef = {}`
	/// and `stringRef = "abc"` continue to select the move assignment operator.
	template <typename T>
	typename std::enable_if<std::is_same<T, std::string>::value,
							StringRef>::type &
	operator=(T &&Str) = delete;

	operator std::string() const {
		return Str();
	}

    char operator[](size_t Index) const {
        assert(Index < Length && "Invalid index!");
        return StrData[Index];
    }

    inline size_t Size() const { return Length; }

	inline StringRef Slice(size_t Start, size_t End) const {
		Start = std::min(Start, Length);
		End = std::min(std::max(Start, End), Length);
		return StringRef(StrData + Start, End - Start);
    }
};

#endif // METAL_ADT_STRINGREF_HPP
