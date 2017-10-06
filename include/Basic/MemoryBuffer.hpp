//--- MemoryBuffer.hpp - Manager for Source Buffers ------------------ C++ ---//
//
// This file defines the class for storing files into memory.
//
//--- -------------------------------------------------------------------- ---//

#ifndef METAL_BASIC_MEMORYBUFFER_HPP
#define METAL_BASIC_MEMORYBUFFER_HPP

#include "ADT/StringRef.hpp"
#include "ADT/ErrorOr.hpp"

#include <memory>
#include <string>

class MemoryBuffer {
private:
	const char *BufferStart; // Start of the buffer.
	const char *BufferEnd;   // End of the buffer.

public:
	MemoryBuffer() : BufferStart(nullptr), BufferEnd(nullptr) { };
	MemoryBuffer(const char *St, const char *Ed)
		: BufferStart(St), BufferEnd(Ed) { };

	const char *GetBufferStart() const { return BufferStart; }
	const char *GetBufferEnd() const { return BufferEnd; }
	size_t GetBufferSize() const { return BufferEnd - BufferStart; }

	const StringRef GetBuffer() const {
		return StringRef(BufferStart, GetBufferSize());
	}

	static ErrorOr<std::unique_ptr<MemoryBuffer>>
	GetFile(const char *const Filename);
};

#endif // METAL_BASIC_MEMORYBUFFER_HPP
