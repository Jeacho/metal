//--- SourceManager.cpp - Manager for Source Buffers ----------------- C++ ---//
/*
**	This file defines types used to reason about source locations and ranges.
*/
//--- -------------------------------------------------------------------- ---//

#include "Basic/SourceManager.hpp"

struct LineNoCacheTy {
    const char *LastQuery;
    unsigned LastQueryBufferID;
    unsigned LineNoOfQuery;
};

static LineNoCacheTy *GetCache(void *Ptr) {
    return (LineNoCacheTy*)Ptr;
}

SourceManager::~SourceManager() {
    delete GetCache(LineNoCache);
}

unsigned
SourceManager::AddIncludeFile(const char *const Filename) {
    ErrorOr<std::unique_ptr<MemoryBuffer>> Mem =
        MemoryBuffer::GetFile(Filename);

    if (std::error_code ec = Mem.getError()) {
        std::cerr << Filename << ": " << ec.message() << "\n";
        exit(errno);
    }

	IncludeDirectories.push_back(std::string(Filename));
    return AddNewSourceBuffer(std::move(*Mem), SourceLocation());
}

unsigned SourceManager::FindBufferContaining(SourceLocation Loc) const {
    for (unsigned i = 0, e = Buffers.size(); i != e; ++i)
    if (Loc.GetPointer() >= Buffers[i].Buffer->GetBufferStart() &&
        Loc.GetPointer() <= Buffers[i].Buffer->GetBufferEnd())
            return i + 1;
  return 0;
}

std::pair<unsigned, unsigned>
SourceManager::GetLineAndCol(SourceLocation Loc, unsigned BufferID) const {
    if (!BufferID)
        BufferID = FindBufferContaining(Loc);
    assert(BufferID && "Invaild Location!");

    const MemoryBuffer *MemBuf = GetMemoryBuffer(BufferID);
    unsigned Line   = 1;
    unsigned Offset = 0;

    const char *BufStart = MemBuf->GetBufferStart();
    const char *Ptr = BufStart;

    if (LineNoCacheTy *Cache = GetCache(LineNoCache)) {
        if (Cache->LastQueryBufferID == BufferID &&
            Cache->LastQuery <= Loc.GetPointer()) {
            Ptr = Cache->LastQuery;
            Line = Cache->LineNoOfQuery;
        }
    }

    for (; SourceLocation::GetFromPointer(Ptr) != Loc; Ptr++) {
        if (*Ptr == '\n') {
            Line++;
            Offset = 0;
        } else
            Offset++;
    }

    if (!LineNoCache)
        LineNoCache = new LineNoCacheTy();

    LineNoCacheTy &Cache = *GetCache(LineNoCache);
    Cache.LastQueryBufferID = BufferID;
    Cache.LastQuery = Ptr;
    Cache.LineNoOfQuery = Line;

    return std::make_pair(Line, Offset);
}

StringRef SourceManager::GetLine(unsigned Target, unsigned BufferID) {
    const MemoryBuffer *MemBuf = GetMemoryBuffer(BufferID);
    const char *LineStart   = MemBuf->GetBufferStart();
    const char *Ptr         = MemBuf->GetBufferStart();
    unsigned Line = 1;

    if (LineNoCacheTy *Cache = GetCache(LineNoCache)) {
        if (Cache->LastQueryBufferID == BufferID &&
            Cache->LineNoOfQuery <= Line) {
            Ptr = Cache->LastQuery;
            Line = Cache->LineNoOfQuery;
        }
    }

    do {
        if (*Ptr == '\n') {
            ++Line;

            if (Line == Target)
                LineStart = (Ptr + 1);
        }
    } while (Line < Target + 1 && Ptr++);

    if (!LineNoCache)
        LineNoCache = new LineNoCacheTy();

    LineNoCacheTy &Cache = *GetCache(LineNoCache);
    Cache.LastQueryBufferID = BufferID;
    Cache.LastQuery = Ptr;
    Cache.LineNoOfQuery = Line;

    return StringRef(LineStart, Ptr - LineStart);
}
