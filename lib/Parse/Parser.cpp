
#include "Parse/Parser.hpp"

#include <map>

namespace Attributes {
    static const uint32_t mod_const         = 0x1;
    static const uint32_t mod_static        = 0x2;
    static const uint32_t mod_unsigned      = 0x4;
    static const uint32_t mod_signed        = 0x8;

    static const uint32_t type_char         = 0x10;
    static const uint32_t type_int          = 0x20;
    static const uint32_t type_float        = 0x40;
    static const uint32_t type_double       = 0x80;
    static const uint32_t type_bool         = 0x100;
    static const uint32_t type_short        = 0x200;
    static const uint32_t type_void         = 0x300;
}

//--- -------------------------------------------------------------------- ---//
//--- --------------------- PARSER IMPLEMENTATION ------------------------ ---//
//--- -------------------------------------------------------------------- ---//

// Found bad token, parse till semi-colon
template<typename ...T>
Statement *Parser::ParseErrorStub(T ...OtherTypes) {
    std::vector<Token> Toks;

    while (Tokens[TokIdx].IsNot(TokType::semi_colon,
            TokType::curly_left, TokType::eof, OtherTypes...))
        Toks.push_back(Tokens[TokIdx++]);

    return new ErrorStub(Tokens);
}

Expression *Parser::ParseExpression() {
    // Stack for formation of Expression Nodes
    std::stack<Token> TokStack;
    Expression *Ret = nullptr;

    if (Tokens[TokIdx].Is(TokType::logic_not)) {
        Ret = new UnaryExpr(Tokens[TokIdx++], ParseExpression());
    } else if (Tokens[TokIdx].Is(TokType::identifier)) {
        Ret = new TermExpr(Tokens[TokIdx++]);
    }

    return Ret;
}

Statement *Parser::ParseDeclaration() {
    TypeAttributes TypeMod;

    unsigned DeclarationStart = TokIdx;

    while (Tokens[TokIdx].IsAny(TokType::kw_unsigned, TokType::kw_signed,
            TokType::kw_const, TokType::kw_static, TokType::kw_char,
            TokType::kw_int, TokType::kw_float, TokType::kw_double,
            TokType::kw_bool, TokType::kw_short, TokType::kw_void)) {

        switch (Tokens[TokIdx].GetKind()) {
        case TokType::kw_unsigned:
            if ((TypeMod.Modifiers & Attributes::mod_unsigned) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::duplicate_unsigned);

            TypeMod.Modifiers |= Attributes::mod_unsigned;
            break;

        case TokType::kw_signed:
            if ((TypeMod.Modifiers & Attributes::mod_signed) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::duplicate_signed);

            TypeMod.Modifiers |= Attributes::mod_signed;
            break;

        case TokType::kw_const:
            if ((TypeMod.Modifiers & Attributes::mod_const) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::duplicate_const);

            TypeMod.Modifiers |= Attributes::mod_const;
            break;

        case TokType::kw_static:
            if ((TypeMod.Modifiers & Attributes::mod_static) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::duplicate_static);

            TypeMod.Modifiers |= Attributes::mod_static;
            break;

        case TokType::kw_char:
            if ((TypeMod.Modifiers & Attributes::type_char) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_char;
            break;

        case TokType::kw_int:
            if ((TypeMod.Modifiers & Attributes::type_int) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_int;
            break;

        case TokType::kw_short:
            if ((TypeMod.Modifiers & Attributes::type_short) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_short;
            break;

        case TokType::kw_double:
            if ((TypeMod.Modifiers & Attributes::type_double) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_double;
            break;

        case TokType::kw_float:
            if ((TypeMod.Modifiers & Attributes::type_float) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_float;
            break;

        case TokType::kw_bool:
            if ((TypeMod.Modifiers & Attributes::type_bool) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_bool;
            break;

        case TokType::kw_void:
            if ((TypeMod.Modifiers & Attributes::type_void) != 0)
                DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                    DiagID::same_type_specificed, Tokens[TokIdx].GetText());

            TypeMod.Modifiers |= Attributes::type_void;
            break;

        default:
            DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                DiagID::duplicate_static);
        }

        ++TokIdx;
    }

    // Consume pointer types
    while (Tokens[TokIdx].Is(TokType::mul)) {
         ++TokIdx;

         if (Tokens[TokIdx].IsNot(TokType::kw_const, TokType::mul,
                TokType::identifier)) {
            DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                DiagID::invalid_ptr_modifier, Tokens[TokIdx].GetText());

            DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                DiagID::this_was_ignored, Tokens[TokIdx].GetText());
        }

        if (Tokens[TokIdx].IsNot(TokType::mul, TokType::identifier))
            ++TokIdx;

        TypeMod.PointerAttributes.push_back(Tokens[TokIdx].Is(TokType::kw_const) ? 0 : 1);
    }

    if (Tokens[TokIdx].Is(TokType::identifier)) {
        bool FoundFlag = false;

        for (uint16_t Idx = 0x10; (Idx >= 0x10 && Idx < 0x400); Idx <<= 1) {
            // More than two flags have been set, Diagnose multiple declartions.
            if ((TypeMod.Modifiers & Idx) != 0 && FoundFlag) {
                DiagEngine->Diagnose(SourceRange(Tokens[DeclarationStart].GetText().Begin(),
                    Tokens[TokIdx - 1].GetText().End()),
                    DiagID::multiple_type_declarations, Tokens[TokIdx].GetText());

                break;
            }

            FoundFlag = (TypeMod.Modifiers & Idx) != 0 || FoundFlag;
        }

        // Found that unsigned and signed were both declared for this Identifier
        if (((TypeMod.Modifiers & Attributes::mod_unsigned) != 0) &&
                ((TypeMod.Modifiers & Attributes::mod_signed) != 0))
            DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
                DiagID::signed_and_unsigned_together,
                Tokens[TokIdx].GetText());

        // Consume identifier
        ++TokIdx;

        if (Tokens[TokIdx].Is(TokType::semi_colon)) {
            SymbolTable.insert(std::pair<const char *, Symbol>
                (Tokens[TokIdx].GetText().Data(),
                Symbol(TypeMod, Tokens[TokIdx - 1], nullptr)));

            ++TokIdx;

        } else if (Tokens[TokIdx].Is(TokType::assign)) {
            // Consume assign.
            ++TokIdx;

            SymbolTable.insert(std::pair<const char *, Symbol>
                (Tokens[TokIdx].GetText().Data(),
                Symbol(TypeMod, Tokens[TokIdx - 1], ParseExpression())));

        } else {
            // Dont think this is possible because of statment parsing but
            // we'll see

            std::cout << "lala" << '\n';
        }

    } else if (Tokens[TokIdx].IsAny(TokType::semi_colon, TokType::eof)) {
        DiagEngine->Diagnose(SourceRange(Tokens[DeclarationStart].GetText().Begin(),
            Tokens[TokIdx - 1].GetText().End()), DiagID::declaration_does_not_declare);
        return ParseErrorStub();
    } else {
        DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
            DiagID::expected_identifier, Tokens[TokIdx].GetText());
        return ParseErrorStub();
    }
}

void Parser::Parse() {
    switch (Tokens[TokIdx].GetKind()) {

    // Modifiers
    case TokType::kw_unsigned: case TokType::kw_signed: case TokType::kw_const:
    case TokType::kw_static:
    // Types
    case TokType::kw_void: case TokType::kw_double: case TokType::kw_float:
    case TokType::kw_int: case TokType::kw_short: case TokType::kw_char:
        GlobalScope->Statements.push_back(ParseDeclaration());
        break;

    case TokType::eof:
        break;

    default:
        DiagEngine->Diagnose(Tokens[TokIdx].GetRange(),
            DiagID::expected_identifier);
    }

    for (Diagnostic Diag : DiagEngine->GetDiags())
        DiagEngine->EmitDiagnostic(Diag);
}
