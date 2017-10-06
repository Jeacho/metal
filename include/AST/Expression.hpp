//--- Expression.hpp - Parser Expressions ---------------------------- C++ ---//
//
//	This file defines the interfaces for representing expressions when
// parsing expresions.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_AST_EXPRESSION_HPP
#define METAL_AST_EXPRESSION_HPP

#include "Parse/Token.hpp"

enum ExprType {
    Term,
    Binary,
    Enclosed,
    Unary
};

class Expression {
public:
    Expression *Parent;
};

class TermExpr : public Expression {
public:
    const ExprType Kind = ExprType::Term;

    Token Tok;

    TermExpr(Token tok) : Tok(tok) { }
};

class BinaryExpr : public Expression {
public:
    const ExprType Kind = ExprType::Binary;

    Expression *LHS, *RHS;

    Token BinaryToken;

    BinaryExpr(Expression *lhs, Token tok, Expression *rhs)
        : LHS(lhs), BinaryToken(tok), RHS(rhs) {
        LHS->Parent = this;
        RHS->Parent = this;
    }
};

class EnclosedExpr : public Expression {
public:
    const ExprType Kind = ExprType::Enclosed;

    Token LHP, RHP;

    Expression *Expr;

    EnclosedExpr(Token lhp, Expression *expr, Token rhp)
        : LHP(lhp), Expr(expr), RHP(rhp) {
        Expr->Parent = this;
    }
};

class UnaryExpr : public Expression {
public:
    const ExprType Kind = ExprType::Unary;

    Token Operator;

    Expression *Operand;

    UnaryExpr(Token tok, Expression *expr)
        : Operator(tok), Operand(expr) {
        Operand->Parent = this;
    }
};

#endif // METAL_PARSE_PARSER_HPP
