//--- Parser.hpp - Metal Parser -------------------------------------- C++ ---//
//
//	This file defines the Parser interface.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_PARSE_PARSER_HPP
#define METAL_PARSE_PARSER_HPP

#include "AST/Statement.hpp"
#include "AST/Expression.hpp"
#include "Parse/Lexer.hpp"

#include <stack>

typedef struct TypeAttributes {
    // Value represents a pointer, if true the pointer is const
    std::vector<bool> PointerAttributes;

    uint32_t Modifiers = 0;
} TypeAttributes;

typedef struct Symbol {
    // Type Mods and Type Specificer
    TypeAttributes Attributes;

    // Token this symbol represents
    Token Identifier;

    Statement *Value;

    Symbol(TypeAttributes attributes, Token ident, Statement *ptr) { }
} Symbol;

class Parser {
    // DiagnosticEngine for emitting Parser Diagnostics
    DiagnosticEngine *DiagEngine;

    // Source Manager and the ID for the buffer this is Parsing
    const SourceManager &SourceMgr;
    const unsigned BufferID;

    // Lexer for collecting a token stream from the source this is parsing
    Lexer L;
    std::vector<Token> Tokens;

    unsigned TokIdx;

    // AST formation
    Scope *GlobalScope;

    std::stack<Token> TokStack;

    // Parsing sub-routines
    template<typename ...T>
    Statement *ParseErrorStub(T ...OtherTypes);
    Statement *ParseDeclaration();

    std::map<char *, Symbol> SymbolTable;

public:
    Parser(DiagnosticEngine *DE, const SourceManager &SM, unsigned BufID)
        : DiagEngine(DE), SourceMgr(SM), BufferID(BufID),
          L(DiagEngine, SourceMgr, BufferID), Tokens(L.Tokenize()) {
        GlobalScope = new Scope();
        TokIdx = 0;
    }

    // Builds AST and populates AST
    void Parse();
};

#endif // METAL_PARSE_PARSER_HPP
