//--- DiagnosticEngine.cpp - Diagnostic Engine ----------------------- C++ ---//
/*
** 	Defines the DiagnosticEngine interface.
*/
//--- -------------------------------------------------------------------- ---//

#include <iostream>

#include "Support/Diagnostic.hpp"
#include "Support/DiagnosticEngine.hpp"

void DiagnosticEngine::EmitDiagnostic(Diagnostic Diag) {
	// Get the full path directory of the file containing the error.
	unsigned BufferID =
		this->SourceMgr.FindBufferContaining(Diag.Range.Start);
	std::string IncludeFile =
		this->SourceMgr.GetIncludeName(BufferID);

	//Get diagnostic location as string from it's source buffer.
	std::string StringLoc = this->SourceMgr.GetLocAsString(Diag.Range.Start);

	// Get color ASNI escape code color for the severity type.
	std::string FrontColorASNI = Diag.GetSeverityColor();

	StringRef SourceLine = this->SourceMgr.GetLine(
			this->SourceMgr.GetLineAndCol(Diag.Range.Start, BufferID).first,
			BufferID);

	// Trim line whitespace
	const char *LineStart = SourceLine.Data();
	while (isspace(*LineStart))
        ++LineStart;

	SourceLine =
		SourceLine.Slice(LineStart - SourceLine.Data(), SourceLine.Size());
		
	// Insert ANSI colors in SourceLine using the Diag's SourceRange.
	unsigned StartIdx	= Diag.Range.Start.GetPointer() - SourceLine.Begin();
	unsigned EndIdx		= Diag.Range.End.GetPointer() - SourceLine.Begin() + 1;

	std::string FmtBeginning = SourceLine.Slice(0, StartIdx);
	std::string FmtMiddle = SourceLine.Slice(StartIdx, EndIdx);
	std::string FmtEnd = SourceLine.Slice(EndIdx, SourceLine.Size());

	// Finally point to the start of the source range and underline the rest.
	std::string Spacing;
	for (unsigned Idx = 0; Idx < StartIdx; Idx++)
		Spacing += " ";

	std::string Underline = "^";
	for (unsigned Idx = 0; Idx < (EndIdx - StartIdx) - 1; Idx++)
		Underline += "~";

	//std::string LocLine = this->SourceMgr.GetLineFromPtr(Diag.GetLocation());

			// INCLUDEFILE:LINE:COLUMN:
	std::cout << "\033[1;37m" << IncludeFile << ":" << StringLoc << ":\033[0m "
		// [ERROR, WARNING, NOTE]:
		<< FrontColorASNI << Diag.GetSeverityAsString() << ":\033[0m "
		// The diagnostic message
		<< Diag.GetMessage() << "\n\t"
		// The line of the location this diagnostic occurs on
		<< FmtBeginning << FrontColorASNI << FmtMiddle << "\033[0m" << FmtEnd
		// Format the underline spacing
		<< "\n\t" << FrontColorASNI << Spacing << Underline << "\033[0m" << "\n"
		<< std::endl;
}
