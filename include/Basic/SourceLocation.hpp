//--- SourceLocation.hpp - Source Locations and Ranges --------------- C++ ---//
//
//	This file defines types used to reason about source locations and ranges.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_BASIC_SOURCELOCATION_HPP
#define METAL_BASIC_SOURCELOCATION_HPP

#include "ADT/StringRef.hpp"

#include <iostream>
#include <cassert>

/// \brief Represents a location in a source file.
class SourceLocation {
private:
	const char *Ptr = nullptr;

public:
	SourceLocation() = default;
	SourceLocation(const char *P) : Ptr(P) { }

	bool IsValid() const {
		return Ptr != nullptr;
	}

	bool operator==(const SourceLocation &RHS) { return RHS.Ptr == Ptr; }
	bool operator!=(const SourceLocation &RHS) { return RHS.Ptr != Ptr; }

	const char *GetPointer() const { return Ptr; }

	/// Return a source location advanced a specified number of bytes.
	SourceLocation GetAdvancedLoc(int ByteOffset) const {
		assert(IsValid() && "Can't advance an invalid location");
		return SourceLocation(GetPointer() + ByteOffset);
	}

	static SourceLocation GetFromPointer(const char *Ptr) {
		SourceLocation L;
		L.Ptr = Ptr;
		return L;
	}
};

class SourceRange {
public:
	SourceLocation Start, End;

	SourceRange() = default;
	SourceRange(SourceLocation St, SourceLocation En) : Start(St), End(En) {
		assert(Start.IsValid() == End.IsValid() &&
	       "Start and end should either both be valid or both be invalid!");
	}

	SourceRange(SourceLocation St, int Len = 1)
		: Start(St), End(St.GetAdvancedLoc(Len)) {
		assert(Start.IsValid() == End.IsValid() &&
	       "Start and end should either both be valid or both be invalid!");
	}

	SourceRange(const char *St, const char *En)
		: Start(St), End(En) {
		assert(Start.IsValid() == End.IsValid() &&
	       "Start and end should either both be valid or both be invalid!");
	}

	SourceRange(const char *St, int Len = 1)
		: Start(St), End(Start.GetAdvancedLoc(Len)) {
		assert(Start.IsValid() == End.IsValid() &&
	       "Start and end should either both be valid or both be invalid!");
	}

	bool IsValid() { return Start.IsValid(); }

	static StringRef GetTextRange(const char *St, const char *En) {
		return StringRef(St, (size_t)(En - St));
	}

	const StringRef GetRange() {
		return GetTextRange(Start.GetPointer(), End.GetPointer());
	}
};

#endif // METAL_BASIC_SOURCELOCATION_HPP
