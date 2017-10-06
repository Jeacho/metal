//--- StringSwitch.hpp - Switch on Literal String Construct ---------- C++ ---//
/*
**	This file implements the StringSwitch template, which mimics a switch()
**  statement whose cases are string literals.
*/
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_STRINGSWITCH_HPP
#define METAL_ADT_STRINGSWITCH_HPP

#include <string>
#include <memory>
#include <cassert>
#include <cstring>

template<typename T, typename R = T>
class StringSwitch {
private:
	// String to be be compared in the switch statement.
	std::string Cond;

	// Result of the switch statement.
	const T *Result;

public:
	 StringSwitch(std::string S) : Cond(S), Result(nullptr) { }

	// StringSwitch is not copyable.
	StringSwitch(const StringSwitch &) = delete;
	void operator=(const StringSwitch &) = delete;

	StringSwitch(StringSwitch &&other) {
		*this = std::move(other);
	}

	StringSwitch &operator=(StringSwitch &&other) {
		Cond = other.Cond;
		Result = other.Result;
		return *this;
	}

	~StringSwitch() = default;

	// Case-sensitive case matchers
	template<unsigned N>
	inline StringSwitch& Case(const char (&S)[N], const T& Value) {
		assert(N);
		if (!Result && N-1 == Cond.size() &&
			(N == 1 || std::memcmp(S, Cond.data(), N-1) == 0)) {
			Result = &Value;
		}
		return *this;
	}

	R Default(const T &Val) const {
		if (Result)
			return *Result;
		return Val;
	}

	operator R() const {
	    assert(Result && "Fell off the end of a string-switch");
	    return *Result;
	}
};

#endif // METAL_ADT_STRINGSWITCH_HPP
