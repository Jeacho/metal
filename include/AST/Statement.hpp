//--- Expression.hpp - Parser Expressions ---------------------------- C++ ---//
//
//	This file defines the interfaces for representing expressions when
// parsing expresions.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_AST_STATEMENT_HPP
#define METAL_AST_STATEMENT_HPP

#include "Parse/Token.hpp"

#include <vector>

enum StatementType {
    ScopeType,
    DeclType,
    ErrorStubType
};

class Statement {
public:
    Statement *Parent; // Scope
};

class ErrorStub : public Statement {
public:
    const StatementType Kind = StatementType::ErrorStubType;

    std::vector<Token> Tokens;

    ErrorStub(std::vector<Token> tokens) : Tokens(tokens) { }
};

class Scope : public Statement {
public:
    const StatementType Kind = StatementType::ScopeType;

    std::vector<Statement *> Statements;

    Scope() { }
};

class Declaration {
public:
    const StatementType Kind = StatementType::DeclType;

    Declaration() { }
};

#endif // METAL_AST_STATEMENT_HPP
