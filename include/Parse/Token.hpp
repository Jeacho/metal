//--- Lexer.hpp - Token Interface ------------------------------------ C++ ---//
/*
**	This file defines the Token interface.
*/
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_PARSE_TOKEN_HPP
#define METAL_PARSE_TOKEN_HPP

#include "ADT/StringRef.hpp"
#include "Parse/TokenKind.hpp"
#include "Basic/SourceLocation.hpp"

class Token {
private:
	// The kind of Token this is.
	TokType Kind;

	// The string representing the this Token.
	StringRef Text;

public:
	Token() : Kind(TokType::none), Text("Empty token") { };

	Token(TokType K, const char *const Str)
		: Kind(K), Text(Str) { };

	Token(TokType K, StringRef Str)
		: Kind(K), Text(Str) { };

	// Getters/Setters for this Token's Kind.
	TokType GetKind() const { return Kind; }
	void SetKind(TokType K) { Kind = K; }

	// Token Kind comparisons: if (Tok.Is(FLT_LIT))
	bool Is(TokType K) const { return Kind == K; }
	bool IsNot(TokType K) const { return Kind != K; }

	bool IsAny(TokType K1) const {
		return Is(K1);
	}

	template <typename ...T>
	bool IsAny(TokType K1, TokType K2, T... K) const {
		if (Is(K1))
			return true;
		return IsAny(K2, K...);
	}

	template <typename ...T>
	bool IsNot(TokType K1, T... K) const { return !IsAny(K1, K...); }

	const std::string Str() const {
		std::string KindString;

		switch (Kind) {
		#define KEYWORD(kw, str) \
		    case TokType::kw_ ## kw: KindString = #str; break;
		#define OPERATOR(kw, str) \
		    case TokType::kw: KindString = #str; break;
		#define MISC(kw, str) \
		    case TokType::kw: KindString = #str; break;
		#define PUNCTUATOR(kw, str) \
		    case TokType::kw: KindString = #str; break;
		#define LITERAL(kw, str) \
		    case TokType::kw: KindString = #str; break;
		#include "Parse/TokenKind.def"
		default:
			assert("invalid token type");
		}

		return "\"" + Text.Str() + "\" (" + KindString + ")";
	}

	// Generate Source Location from this Tokens Pointer.
	SourceLocation GetLoc() const {
		return SourceLocation::GetFromPointer(Text.Data());
	}

	// Generate Source range encompassing the entire token.
	SourceRange GetRange() const {
		return SourceRange(Text.Begin(), Text.End());
	}

	StringRef GetText() const {
		return Text;
	}
};

#endif // METAL_PARSE_TOKEN_HPP
