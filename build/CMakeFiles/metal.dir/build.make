# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macadmin/desktop/metal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macadmin/desktop/metal/build

# Include any dependencies generated for this target.
include CMakeFiles/metal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/metal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/metal.dir/flags.make

CMakeFiles/metal.dir/MetalMain.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/MetalMain.cpp.o: ../MetalMain.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/metal.dir/MetalMain.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/MetalMain.cpp.o -c /Users/macadmin/desktop/metal/MetalMain.cpp

CMakeFiles/metal.dir/MetalMain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/MetalMain.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/MetalMain.cpp > CMakeFiles/metal.dir/MetalMain.cpp.i

CMakeFiles/metal.dir/MetalMain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/MetalMain.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/MetalMain.cpp -o CMakeFiles/metal.dir/MetalMain.cpp.s

CMakeFiles/metal.dir/MetalMain.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/MetalMain.cpp.o.requires

CMakeFiles/metal.dir/MetalMain.cpp.o.provides: CMakeFiles/metal.dir/MetalMain.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/MetalMain.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/MetalMain.cpp.o.provides

CMakeFiles/metal.dir/MetalMain.cpp.o.provides.build: CMakeFiles/metal.dir/MetalMain.cpp.o


CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o: ../lib/Basic/MemoryBuffer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o -c /Users/macadmin/desktop/metal/lib/Basic/MemoryBuffer.cpp

CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Basic/MemoryBuffer.cpp > CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.i

CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Basic/MemoryBuffer.cpp -o CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.s

CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.requires

CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.provides: CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.provides

CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o


CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o: ../lib/Basic/SourceManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o -c /Users/macadmin/desktop/metal/lib/Basic/SourceManager.cpp

CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Basic/SourceManager.cpp > CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.i

CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Basic/SourceManager.cpp -o CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.s

CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.requires

CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.provides: CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.provides

CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o


CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o: ../lib/Parse/Lexer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o -c /Users/macadmin/desktop/metal/lib/Parse/Lexer.cpp

CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Parse/Lexer.cpp > CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.i

CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Parse/Lexer.cpp -o CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.s

CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.requires

CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.provides: CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.provides

CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o


CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o: ../lib/Parse/Parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o -c /Users/macadmin/desktop/metal/lib/Parse/Parser.cpp

CMakeFiles/metal.dir/lib/Parse/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Parse/Parser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Parse/Parser.cpp > CMakeFiles/metal.dir/lib/Parse/Parser.cpp.i

CMakeFiles/metal.dir/lib/Parse/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Parse/Parser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Parse/Parser.cpp -o CMakeFiles/metal.dir/lib/Parse/Parser.cpp.s

CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.requires

CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.provides: CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.provides

CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o


CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o: ../lib/Support/Diagnostic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o -c /Users/macadmin/desktop/metal/lib/Support/Diagnostic.cpp

CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Support/Diagnostic.cpp > CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.i

CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Support/Diagnostic.cpp -o CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.s

CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.requires

CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.provides: CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.provides

CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o


CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o: CMakeFiles/metal.dir/flags.make
CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o: ../lib/Support/DiagnosticEngine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o -c /Users/macadmin/desktop/metal/lib/Support/DiagnosticEngine.cpp

CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macadmin/desktop/metal/lib/Support/DiagnosticEngine.cpp > CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.i

CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macadmin/desktop/metal/lib/Support/DiagnosticEngine.cpp -o CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.s

CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.requires:

.PHONY : CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.requires

CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.provides: CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.requires
	$(MAKE) -f CMakeFiles/metal.dir/build.make CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.provides.build
.PHONY : CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.provides

CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.provides.build: CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o


# Object files for target metal
metal_OBJECTS = \
"CMakeFiles/metal.dir/MetalMain.cpp.o" \
"CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o" \
"CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o" \
"CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o" \
"CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o" \
"CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o" \
"CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o"

# External object files for target metal
metal_EXTERNAL_OBJECTS =

metal: CMakeFiles/metal.dir/MetalMain.cpp.o
metal: CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o
metal: CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o
metal: CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o
metal: CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o
metal: CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o
metal: CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o
metal: CMakeFiles/metal.dir/build.make
metal: CMakeFiles/metal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/macadmin/desktop/metal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable metal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/metal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/metal.dir/build: metal

.PHONY : CMakeFiles/metal.dir/build

CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/MetalMain.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Basic/MemoryBuffer.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Basic/SourceManager.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Parse/Lexer.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Parse/Parser.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Support/Diagnostic.cpp.o.requires
CMakeFiles/metal.dir/requires: CMakeFiles/metal.dir/lib/Support/DiagnosticEngine.cpp.o.requires

.PHONY : CMakeFiles/metal.dir/requires

CMakeFiles/metal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/metal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/metal.dir/clean

CMakeFiles/metal.dir/depend:
	cd /Users/macadmin/desktop/metal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macadmin/desktop/metal /Users/macadmin/desktop/metal /Users/macadmin/desktop/metal/build /Users/macadmin/desktop/metal/build /Users/macadmin/desktop/metal/build/CMakeFiles/metal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/metal.dir/depend
