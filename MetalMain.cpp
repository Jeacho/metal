
#include "Parse/Parser.hpp"

int main() {
    SourceManager SourceMgr;
    unsigned BufferID =
        SourceMgr.AddIncludeFile("/home/jacob/Documents/metal/samples/BufferTest.mtl");

    DiagnosticEngine DiagEngine(SourceMgr);

    Parser P(&DiagEngine, SourceMgr, BufferID);
    P.Parse();

    return 0;
}
