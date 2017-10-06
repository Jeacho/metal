//--- Diagnostic.cpp - Diagnostic Interface -------------------------- C++ ---//
//
//  This file defines the Diagnostic Interface it also expands the
// DiagnosticKind definition file.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_DIAGNOSTIC_HPP
#define METAL_ADT_DIAGNOSTIC_HPP

#include <iostream>
#include <vector>
#include <string>

#include "ADT/StringRef.hpp"
#include "Basic/SourceLocation.hpp"

// Forward Declarations
    class DiagnosticEngine;

// Enum for qualifing Diagnostic as either a Note, Warning or Error.
enum DiagType {
    Note,
    Warning,
    Error
};

enum DiagOpts {
    None = 0,
    Fatal
};

// Expanding and storing diagnostic information.
struct DiagnosticInfo {
    // Type of Diagnostic(Note, Error, Warning)
    const DiagType Type;

    const DiagOpts Opts;

    // The message for this diagnostic.
    const char *const Text;

    DiagnosticInfo(DiagType T, DiagOpts O, const char *const S)
        : Type(T), Opts(O), Text(S) { }
};

//  Enum for Identifing each diagnostic for mapping to it's respective
// diagnostic message.
enum class DiagID : uint32_t {
    // DiagnosticKind.def expansion
#define DIAG(DIAGTYPE, DIAGID, TEXT, OPTIONS, ARGS) DIAGID,
#include "Support/DiagnosticList.def"
};

// Diagnostic messages
static const DiagnosticInfo StoredDiagInfo[] = {
#define DIAG(DIAGTYPE, DIAGID, TEXT, OPTIONS, ARGS) \
    DiagnosticInfo(DiagType::DIAGTYPE, DiagOpts::OPTIONS, TEXT),
#include "Support/DiagnosticList.def"
};

// Diagnostic Argument types.
enum class DiagArgumentKind {
	Integer,
	Unsigned,
	CharPtr,
	StringRef,
    Char
};

// Hold a diagnostic arugment and what type it is.
class DiagArgument {
	DiagArgumentKind Kind;

    union {
        char CharVal;
		StringRef StringRefVal;
		char *CharPtrVal;
        int IntegerVal;
        unsigned UnsignedVal;
    };
public:
    DiagArgument(int Int)
        : Kind(DiagArgumentKind::Integer), IntegerVal(Int) { }

    DiagArgument(unsigned Unsigned)
        : Kind(DiagArgumentKind::Unsigned), UnsignedVal(Unsigned) { }

    // String wrapper class StringRef
    DiagArgument(StringRef Str)
        : Kind(DiagArgumentKind::StringRef), StringRefVal(Str) { }

    DiagArgument(char *Str)
        : Kind(DiagArgumentKind::CharPtr), CharPtrVal(Str) { }

    DiagArgument(char Char)
        : Kind(DiagArgumentKind::Char), CharVal(Char) { }

    DiagArgumentKind GetKind() {
        return Kind;
    }

    int GetAsInteger() {
        assert(Kind == DiagArgumentKind::Integer);
        return IntegerVal;
    }

    unsigned GetAsUnsigned() {
        assert(Kind == DiagArgumentKind::Unsigned);
        return UnsignedVal;
    }

    char GetAsChar() {
        assert(Kind == DiagArgumentKind::Char);
        return CharVal;
    }

	StringRef GetAsStringRef() {
		assert(Kind == DiagArgumentKind::StringRef);
		return StringRefVal;
	}

	char *GetAsCharPtr() {
		assert(Kind == DiagArgumentKind::CharPtr);
		return CharPtrVal;
	}
};

// Diagnostic Implementation
class Diagnostic {
    friend class DiagnosticEngine;

    DiagID ID;

    SourceRange Range;

    std::vector<DiagArgument> Args;
    unsigned NumArgs = 0;

    void insert() { }

	template <typename T, typename... Ts>
	void insert(T&& v, Ts&&... args) {
		Args.push_back(std::forward<T>(v));
		insert(std::forward<Ts>(Args)...);
        NumArgs++;
	}

public:
    template <typename... Ts>
    Diagnostic(SourceRange L, DiagID ID, Ts&&... _Args)
        : ID(ID), Range(L) {
        insert(std::forward<Ts>(_Args)...);
    }

    const DiagID GetID() const { return ID; }

    const std::vector<DiagArgument> &GetArguments() const {
        return Args;
    }

    const DiagArgument &GetArgument(unsigned Idx) const {
        return Args[Idx];
    }

	DiagType GetSeverity() const {
		return StoredDiagInfo[static_cast<int>(ID)].Type;
	}

    SourceRange GetRange() const {
        return Range;
    }

    std::string GetSeverityAsString() const {
        switch (GetSeverity()) {
        case DiagType::Error:
            return "error";
        case DiagType::Warning:
            return "warning";
        case DiagType::Note:
            return "note";
        }
    }

	DiagOpts GetOptions() const {
		return StoredDiagInfo[static_cast<int>(ID)].Opts;
	}

    bool IsFatal() {
        return StoredDiagInfo[static_cast<int>(ID)].Opts == DiagOpts::Fatal;
    }

    std::string GetSeverityColor();

    std::string GetMessage();
};

#endif // METAL_ADT_DIAGNOSTIC_HPP
