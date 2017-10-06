//--- SourceManager.hpp - Manager for Source Buffers ----------------- C++ ---//
/*
**	This file defines SourceManager.
*/
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_BASIC_SOURCEMANAGER_HPP
#define METAL_BASIC_SOURCEMANAGER_HPP

#include <ctype.h>
#include <iostream>
#include <utility>
#include <memory>
#include <map>
#include <vector>

#include "ADT/ErrorOr.hpp"
#include "ADT/StringRef.hpp"
#include "Basic/MemoryBuffer.hpp"
#include "Basic/SourceLocation.hpp"

class SourceManager {
private:
	struct SrcBuffer {
		/// The memory buffer for the file.
		std::unique_ptr<MemoryBuffer> Buffer;

		/// This is the location of the parent include, or null if at the top level.
		SourceLocation IncludeLoc;
	};

	/// This is all of the buffers that we are reading from.
	std::vector<SrcBuffer> Buffers;

	// This is the list of directories we should search for include files in.
	std::vector<std::string> IncludeDirectories;

	mutable void *LineNoCache = nullptr;

public:
	SourceManager() = default;
	SourceManager(const SourceManager &) = delete;
	SourceManager &operator=(const SourceManager &) = delete;
	~SourceManager();

	bool IsValidBufferID(unsigned i) const { return i && i <= Buffers.size(); }

	void SetIncludeDirs(const std::vector<std::string> &Dirs) {
		IncludeDirectories = Dirs;
	}

	/// Add a new source buffer to this source manager. This takes ownership of
	/// the memory buffer.
	unsigned AddNewSourceBuffer(std::unique_ptr<MemoryBuffer> F,
	                      		SourceLocation IncludeLoc) {
		SrcBuffer NB;
		NB.Buffer = std::move(F);
		NB.IncludeLoc = IncludeLoc;
		Buffers.push_back(std::move(NB));
		return Buffers.size();
	}

	const MemoryBuffer *GetMemoryBuffer(unsigned i) const {
		assert(IsValidBufferID(i));
		return Buffers[i - 1].Buffer.get();
	}

	std::string GetIncludeName(unsigned i) const {
		assert(IsValidBufferID(i) && "Out of bounds access.");
		return IncludeDirectories[i - 1];
	}

	std::string GetLocAsString(SourceLocation Loc) {
		std::pair<unsigned, unsigned> LineAndCol =
			GetLineAndCol(Loc, FindBufferContaining(Loc));
		return (std::to_string(LineAndCol.first) + ":" +
				std::to_string(LineAndCol.second));
	}

	StringRef GetLine(unsigned Target, unsigned BufferID);

	// Finds the line and column of a Location using a source Location.
	std::pair<unsigned, unsigned>
	GetLineAndCol(SourceLocation Loc, unsigned BufferID) const;

	// Find a memory buffer containing a Location or a raw pointer.
	unsigned FindBufferContaining(SourceLocation Loc) const;

	// Tracks all file inclusions.
	unsigned AddIncludeFile(const char *const Filename);
};

#endif // METAL_BASIC_SOURCEMANAGER_HPP
