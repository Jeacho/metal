#include "Basic/MemoryBuffer.hpp"

#include <system_error>
#include <string>
#include <memory>
#include <iostream>
#include <fstream>

ErrorOr<std::unique_ptr<MemoryBuffer>>
MemoryBuffer::GetFile(const char *const Filename) {
	std::ifstream Input(Filename, std::ios::ate | std::ios::in | std::ios::binary);
	int64_t S = Input.tellg();
	Input.seekg(0, Input.beg);

	if (!Input.is_open()) {
		return make_error_code(std::errc::no_such_file_or_directory);
	}

    char *Mem = static_cast<char *>(operator new(S + 1));
	Mem[S] = '\0';
	Input.read(Mem, S);

	std::unique_ptr<MemoryBuffer>
		MemBuf(new MemoryBuffer(&Mem[0], &Mem[S + 1]));

	if (!MemBuf) {
		return make_error_code(std::errc::not_enough_memory);
	}

	return std::move(MemBuf);
}
