//--- TokenKind.hpp - Token flavor enum ------------------------------ C++ ---//
/*
** This file creates the TokType enum
*/
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_TOKEN_TOKENKIND_HPP
#define METAL_TOKEN_TOKENKIND_HPP

enum class TokType : uint32_t {
#define PUNCTUATOR(name, str) name,
#define OPERATOR(name, str) name,
#define KEYWORD(name, str) kw_ ## name,
#define LITERAL(name, str) name,
#define MISC(name, str) name,

#include "Parse/TokenKind.def"
};

#endif // METAL_TOKEN_TOKENKIND_HPP
