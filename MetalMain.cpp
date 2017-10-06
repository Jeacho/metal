
#include "Parse/Parser.hpp"

int main() {
    SourceManager SourceMgr;
    unsigned BufferID =
        SourceMgr.AddIncludeFile("/Users/macadmin/Desktop/metal/samples/BufferTest.mtl");

    DiagnosticEngine DiagEngine(SourceMgr);

    Parser P(&DiagEngine, SourceMgr, BufferID);
    P.Parse();

    return 0;
}
