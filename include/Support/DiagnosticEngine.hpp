//--- DiagnosticEngine.hpp - Diagnostic Engine ----------------------- C++ ---//
/*
**  This file defines the Diagnostic Engine, used for emitting errors, warnings
** and notes to an output stream.
*/
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_ADT_DIAGNOSTICENGINE_HPP
#define METAL_ADT_DIAGNOSTICENGINE_HPP

#include "Basic/SourceManager.hpp"
#include "Support/Diagnostic.hpp"

#include <vector>

class DiagnosticEngine {
	/// \brief Don't emit any warnings
    bool suppressWarnings = false;

    /// \brief Emit all warnings as errors
    bool warningsAsErrors = false;

    /// \brief Whether a fatal error has occurred
    bool fatalErrorOccurred = false;

    /// \brief Whether any error diagnostics have been emitted.
    bool anyErrorOccurred = false;

	SourceManager &SourceMgr;

	std::vector<Diagnostic> Diags;

public:
	DiagnosticEngine(SourceManager &SM) : SourceMgr(SM) { }

    std::vector<Diagnostic> GetDiags() {
        return Diags;
    }

    // Queues a diagnostic to be emitted.
    template <typename... Ts>
    Diagnostic Diagnose(SourceRange Range, DiagID ID, Ts&&... Args) {
        Diagnostic Diag(Range, ID, Args...);
        Diags.push_back(Diag);
        return Diag;
    }

    // Emits a diagnostic to output formatted with colors and arguments.
    void EmitDiagnostic(Diagnostic Diag);
};

#endif // METAL_ADT_DIAGNOSTICENGINE_HPP
