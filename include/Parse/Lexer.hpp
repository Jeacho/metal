//--- Lexer.hpp - Metal Lexer ---------------------------------------- C++ ---//
//
//	This file defines the Lexer interface.
//
//--- -------------------------------------------------------------------- ---//

#ifndef CHIMP_PARSE_LEXER_HPP
#define CHIMP_PARSE_LEXER_HPP

#include <cerrno>
#include <cstring>
#include <ctype.h>

#include "ADT/StringRef.hpp"
#include "ADT/StringSwitch.hpp"
#include "Support/DiagnosticEngine.hpp"
#include "Basic/SourceManager.hpp"
#include "Parse/Token.hpp"

class Lexer {
    DiagnosticEngine *DiagEngine;

    const SourceManager &SourceMgr;

    // Keep Track of the MemoryBuffer.
    const unsigned BufferID;

    const char *BufferStart;
    const char *BufferEnd;

    // Pointer to the next character.
    const char *CurPtr;

    Token NextToken;

    // Lexer State
    bool Complete = false;

    Lexer(const Lexer&) = delete;
    void operator=(const Lexer&) = delete;

    inline void FormToken() {
    	NextToken = Token();
    }

    inline void FormToken(TokType Kind) {
    	NextToken = Token(Kind, StringRef(CurPtr - 1));
    }

    inline void FormToken(TokType Kind, size_t Len) {
        const char *Start = CurPtr - 1;

        for (size_t Idx = 0; Idx < Len; Idx++)
            ++CurPtr;

        NextToken = Token(Kind, StringRef(Start, Len + 1));
    }

    char LexCharacter();
    void MultilinedComment();

    void LexOctalLiteral();
    void LexBinaryLiteral();
    void LexHexdecimalLiteral();
    void LexNumber();
    void LexIdentifier();
    void LexStringLiteral();
    void LexCharacterLiteral();

public:
    Lexer(DiagnosticEngine *DE, const SourceManager &SM, unsigned BufID)
            : DiagEngine(DE), SourceMgr(SM), BufferID(BufID) {
        BufferStart = SourceMgr.GetMemoryBuffer(BufferID)->GetBufferStart();
        BufferEnd   = SourceMgr.GetMemoryBuffer(BufferID)->GetBufferEnd();
        CurPtr      = BufferStart;
        NextToken = Token();
    };

    void EmitDiags() {
        for (auto&& Diag : DiagEngine->GetDiags())
            DiagEngine->EmitDiagnostic(Diag);
    }

    void Lex();

    std::vector<Token> Tokenize();
};

#endif // METAL_PARSE_LEXER_HPP
