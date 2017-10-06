//--- Lexer.cpp - Lexer Interface ------------------------------------ C++ ---//
/*
**	This file defines the Lexer Interface
*/
//--- -------------------------------------------------------------------- ---//

#include "Support/DiagnosticEngine.hpp"
#include "Parse/Lexer.hpp"

char Lexer::LexCharacter() {
	char CharacterLit = *CurPtr;

	if (*CurPtr == '\\') {
		switch (*++CurPtr) {
		case 'T':
		case 't':
			CharacterLit = '\t';
			break;
		case 'N':
		case 'n':
			CharacterLit = '\n';
			break;
		case 'V':
		case 'v':
			CharacterLit = '\v';
			break;
		case '0':
			CharacterLit = '\0';
			break;
		case '\"':
			CharacterLit = '\'';
			break;
		case '\'':
			CharacterLit = '\'';
			break;
		case '\\':
			CharacterLit = '\\';
			break;
		default:
			DiagEngine->Diagnose(SourceRange(CurPtr - 1),
				DiagID::invalid_escape_character_seq,
				StringRef(CurPtr - 1, 2));
		}
	}

	return CharacterLit;
}

/* CHARACTER LITERAL
**	['][*][']
**	['][\][t,n,v,0,',\][']
*/
void Lexer::LexCharacterLiteral() {
	assert(*(CurPtr - 1) == '\'' && "Invalid start of Character Literal.");

	const char *CharStart = (CurPtr - 1);
	// The character literal to be stored as the token.
	char CharacterLit = LexCharacter();

	if (CharacterLit == '\'') {
		DiagEngine->Diagnose(SourceRange(CurPtr - 1),
			DiagID::empty_character_literal);
		++CurPtr;
	} else if (*++CurPtr != '\'') {
		while (CurPtr >= BufferStart && CurPtr <= BufferEnd) {
			// Failed to close initial single quote
			if (*CurPtr == '\0') {
				DiagEngine->Diagnose(SourceRange(CharStart),
					DiagID::unterminated_character_literal);
				break;
			// Multiple character literals inside signle quote, consume
			// first character as literal.
			} else if (*CurPtr == '\'') {
				DiagEngine->Diagnose(SourceRange(CharStart + 1, CurPtr - 1),
					DiagID::multicharacter_character_literal);
				break;
			}

			++CurPtr;
		}
	}

	FormToken(TokType::char_lit);
	++CurPtr;
}

/* STRING LITERAL
**	["][A-Z,a-z]["]
**	["][A-Z,a-z][\][t,n,v,0,',\]["]
*/
void Lexer::LexStringLiteral() {
	assert(*(CurPtr - 1) == '"' && "Invalid start of Character Literal.");

	const char *StrStart = CurPtr;
	// Handles escape sequences
	char C = LexCharacter();

	while (C != '\"') {
		if (*CurPtr == '\n' || *CurPtr == '\0') {
			DiagEngine->Diagnose(SourceRange(StrStart, CurPtr - 1),
				DiagID::unterminated_string);
			break;
		} else {
			++CurPtr;
			C = LexCharacter();
		}
	}

	NextToken = Token(TokType::string_lit,
		StringRef(StrStart, CurPtr - StrStart));
	// Consume trailing quote
	++CurPtr;
}

/* IDENTIFIER
**	[A-Z,a-z,_][A-Z,a-z,0-9,_]
*/
void Lexer::LexIdentifier() {
	assert((*(CurPtr - 1) == '_' || isalnum(*(CurPtr - 1)))
		&& "Invalid start of Identifier");

	const char *Start = CurPtr - 1;
    while (isalnum(*CurPtr) || *CurPtr == '_') {
        ++CurPtr;
	}

	StringRef Text(Start, CurPtr - Start);

	TokType Kind = StringSwitch<TokType>(Text)
	#define KEYWORD(kw, str) \
	    .Case(#kw, TokType::kw_##kw)
	#include "Parse/TokenKind.def"
	    .Default(TokType::identifier);

	NextToken = Token(Kind, Text);
}

void Lexer::LexHexdecimalLiteral() {
	assert((*CurPtr == 'x' || *CurPtr == 'X')
		&& "Invalid start of number literal.");

	TokType Kind = TokType::int_lit;
	const char *Start = CurPtr - 1;

	++CurPtr;

	while (isxdigit(*CurPtr))
		++CurPtr;

	if (isalnum(*CurPtr)) {
		DiagEngine->Diagnose(SourceRange(CurPtr, 0),
			DiagID::invalid_hexdecimal_character, StringRef(CurPtr));

		while (isalnum(*CurPtr))
			++CurPtr;

		return FormToken();
	}

	NextToken = Token(Kind, StringRef(Start, (CurPtr - Start)));
}

void Lexer::LexBinaryLiteral() {
	assert((*CurPtr == 'b' || *CurPtr == 'B')
		&& "Invalid start of binary literal.");

	TokType Kind = TokType::int_lit;
	const char *Start = CurPtr - 1;
	CurPtr++;

	while (*CurPtr == '0' || *CurPtr == '1')
		++CurPtr;

	if (isalnum(*CurPtr)) {
		DiagEngine->Diagnose(SourceRange(CurPtr, 0),
			DiagID::invalid_binary_character, StringRef(CurPtr));

		while (isalnum(*CurPtr))
			++CurPtr;

		return FormToken();
	}

	NextToken = Token(Kind, StringRef(Start, (CurPtr - Start)));
}

void Lexer::LexOctalLiteral() {
	assert(*(CurPtr - 1) == '0' && "Invalid start of octal literal.");

	TokType Kind = TokType::int_lit;
	const char *Start = CurPtr - 1;

	while (*CurPtr >= '0' && *CurPtr <= '7')
		++CurPtr;

	if (isalnum(*CurPtr)) {
		DiagEngine->Diagnose(SourceRange(CurPtr, 0),
			DiagID::invalid_octal_character, StringRef(CurPtr));

		while (isalnum(*CurPtr))
			++CurPtr;

		return FormToken();
	}

 	NextToken = Token(Kind, StringRef(Start, (CurPtr - Start)));
}

void Lexer::LexNumber() {
	assert(isdigit(*(CurPtr - 1)) || *(CurPtr - 1) == '.'
		&& "Invalid start of number literal.");

	bool FloatingType = false;
	const char *Start = CurPtr - 1;

	if (*Start == '.' && !isdigit(*CurPtr))
		return FormToken(TokType::period);

	if (*Start == '0' && isdigit(*CurPtr))
		return LexOctalLiteral();

	// Number systems
	switch (*CurPtr) {
	case 'x': case 'X':
		return LexHexdecimalLiteral();
	case 'b': case 'B':
		return LexBinaryLiteral();
	case '.':
		FloatingType = true;
		CurPtr++;
		break;
	default:
		if (isalpha(*CurPtr)) {
			DiagEngine->Diagnose(SourceRange(CurPtr, 0),
				DiagID::invalid_number_type_identifier, StringRef(CurPtr));

			while (isalnum(*CurPtr))
				++CurPtr;

			return FormToken();
		}
	}

	// Consume leading digits
	while (isdigit(*CurPtr) || *CurPtr == '.') {
		if (*CurPtr == '.') {
			if (FloatingType) {
				while (isdigit(*CurPtr) || *CurPtr == '.')
					++CurPtr;

				DiagEngine->Diagnose(SourceRange(Start, CurPtr - 1),
					DiagID::too_many_decimals);

				return FormToken();
			}

			FloatingType = true;
		}

		CurPtr++;
	}

	// If exponential, consume e and then consume numbers after
	if (*CurPtr == 'E' || *CurPtr == 'e') {
		FloatingType = true;
		++CurPtr;

		// Consume sign of exponent
		if (*CurPtr == '-' || *CurPtr == '+')
			++CurPtr;

		if (!isdigit(*CurPtr)) {
			while (isdigit(*CurPtr) || *CurPtr == '.')
				++CurPtr;

			DiagEngine->Diagnose(SourceRange(CurPtr, 0),
				DiagID::expected_exponent_number, StringRef(CurPtr - 1));

			return FormToken();
		}

		// Consume trailing digits in exponent
		while (isdigit(*CurPtr) || *CurPtr == '.') {
			if (*CurPtr == '.') {
				while (isdigit(*CurPtr) || *CurPtr == '.')
					++CurPtr;

				DiagEngine->Diagnose(SourceRange(Start, CurPtr - 1),
					DiagID::decimals_in_exponent);

				return FormToken();
			}

			CurPtr++;
		}
	}

	NextToken = Token(FloatingType ? TokType::float_lit :
			TokType::int_lit, StringRef(Start, (CurPtr - Start)));
}

void Lexer::MultilinedComment() {
	const char *StartOfComment = CurPtr - 1;
	bool FoundNewline = false;

	while (*CurPtr != ']' && *(CurPtr) != ']') {
		if (*(CurPtr + 1) == '\0') {
			DiagEngine->Diagnose(SourceRange(StartOfComment, 1),
				DiagID::unterminated_multilined_comment);

			Complete = true;
			return;
		}

		++CurPtr;
	}

	// Consume trailing ]]
	CurPtr += 2;
}

void Lexer::Lex() {
	assert(CurPtr >= BufferStart &&
         CurPtr <= BufferEnd && "Current pointer out of range!");

Restart:
	switch (*CurPtr++) {
	case ' ':
	case '\t':
	case '\f':
	case '\v':
	case '\r':
	case '\n':
		goto Restart;  // Skip whitespace.

	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
	case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
	case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
	case 'V': case 'W': case 'X': case 'Y': case 'Z':
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
	case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
	case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
	case 'v': case 'w': case 'x': case 'y': case 'z':
	case '_':
		return LexIdentifier();

	case '1': case '2': case '3':
	case '4': case '5': case '6':
	case '7': case '8': case '9':
	case '0': case '.':
		return LexNumber();

	case '\'':
		return LexCharacterLiteral();

	case '"':
		return LexStringLiteral();

	// Single lined comment
	case '#':
		while (*CurPtr != '\n' && *CurPtr != '\r' && *CurPtr != '\0')
			++CurPtr;
		goto Restart;

	case 0:
		if (CurPtr != BufferEnd) {
			DiagEngine->Diagnose(SourceRange(CurPtr, 0),
				DiagID::extranous_null_character, StringRef(CurPtr));
		}

		Complete = 1;
		return FormToken(TokType::eof);

	// ARITHMETIC OPERATORS
	case '+':
		if (*CurPtr == '=')
			return FormToken(TokType::add_equal, 1);
		else if (*CurPtr == '+')
			return FormToken(TokType::inc, 1);
		return FormToken(TokType::add);
	case '-':
		if (*(CurPtr) == '=')
			return FormToken(TokType::add_equal, 1);
		else if (*CurPtr == '-')
			return FormToken(TokType::dec, 1);
		return FormToken(TokType::add);
	case '*':
		if (*(CurPtr) == '=')
			return FormToken(TokType::mul_equal, 1);
		else if (*(CurPtr) == '/')
			DiagEngine->Diagnose(SourceRange(CurPtr - 1, 1),
				DiagID::extranous_multilined_comment_terminator);
		return FormToken(TokType::mul);
	case '/':
		if (*(CurPtr + 1) == '=')
			return FormToken(TokType::quo_equal, 1);
		else if (*CurPtr == '*') {
			MultilinedComment();
			goto Restart;
		}
		return FormToken(TokType::quo);
	case '%':
		if (*(CurPtr + 1) == '=')
			return FormToken(TokType::mod_equal, 1);
		return FormToken(TokType::modulo);

	// COMPARISON OPERATORS, BITSHIFT, COMPOUND BITSHIT
	case '<':
		if (*CurPtr == '<' && *(CurPtr + 1) == '=')
			return FormToken(TokType::left_bitshift_equal, 1);
		else if (*CurPtr == '=')
			return FormToken(TokType::les_equal, 1);
		return FormToken(TokType::lesser);
	case '>':
		if (*CurPtr == '>' && *(CurPtr + 1) == '=')
			return FormToken(TokType::right_bitshift_equal, 1);
		else if (*CurPtr == '=')
			return FormToken(TokType::gtr_equal, 1);
		return FormToken(TokType::greater);
	case '=':
		if (*CurPtr == '=')
			return FormToken(TokType::equal_to, 1);
		return FormToken(TokType::assign);

	// BITWISE OPERATORS, COMPOUND BITWISE OPERATORS
	case '|':
		if (*CurPtr == '|')
			return FormToken(TokType::logic_or, 1);
		else if (*CurPtr == '=')
			return FormToken(TokType::bit_or_equal, 1);
		return FormToken(TokType::bitwise_or, 1);
	case '&':
		if (*CurPtr == '&')
			return FormToken(TokType::logic_and, 1);
		else if (*CurPtr == '=')
			return FormToken(TokType::bit_and_equal, 1);
		return FormToken(TokType::bitwise_and);
	case '^':
		if (*CurPtr == '=')
			return FormToken(TokType::bit_xor_equal, 1);
		return FormToken(TokType::bitwise_xor);

	// MISC OPERATORS
	case '~':
		if (*CurPtr == '~' && *(CurPtr + 1) == '>')
			return FormToken(TokType::scope, 2);
		else {
			DiagEngine->Diagnose(SourceRange(CurPtr, 0),
				DiagID::nonexistant_operator, StringRef(CurPtr));
			return FormToken();
		}

	case '@': return FormToken(TokType::address);
	case ':': return FormToken(TokType::colon);
	case ';': return FormToken(TokType::semi_colon);
	case ',':
		return FormToken(TokType::comma);

	case '(': return FormToken(TokType::bracket_left);
    case ')': return FormToken(TokType::bracket_right);
    case '{': return FormToken(TokType::curly_left);
    case '}': return FormToken(TokType::curly_right);
    case '[':
		return FormToken(TokType::brace_left);

	case ']':
        return FormToken(TokType::brace_right);

	default:
		DiagEngine->Diagnose(SourceRange(CurPtr - 1, 0),
			DiagID::nonexistant_operator, StringRef(CurPtr - 1, 1));
		return FormToken(TokType::none);
	}
}

std::vector<Token> Lexer::Tokenize() {
	std::vector<Token> Ret;
	int i = 0;

	while (NextToken.IsNot(TokType::eof) && !Complete) {
		Lex();
		Ret.push_back(NextToken);
	}

	return Ret;
}
