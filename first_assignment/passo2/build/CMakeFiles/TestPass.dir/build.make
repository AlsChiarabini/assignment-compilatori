# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build

# Include any dependencies generated for this target.
include CMakeFiles/TestPass.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TestPass.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TestPass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestPass.dir/flags.make

CMakeFiles/TestPass.dir/codegen:
.PHONY : CMakeFiles/TestPass.dir/codegen

CMakeFiles/TestPass.dir/LocalOpts.cpp.o: CMakeFiles/TestPass.dir/flags.make
CMakeFiles/TestPass.dir/LocalOpts.cpp.o: /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/LocalOpts.cpp
CMakeFiles/TestPass.dir/LocalOpts.cpp.o: CMakeFiles/TestPass.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestPass.dir/LocalOpts.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TestPass.dir/LocalOpts.cpp.o -MF CMakeFiles/TestPass.dir/LocalOpts.cpp.o.d -o CMakeFiles/TestPass.dir/LocalOpts.cpp.o -c /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/LocalOpts.cpp

CMakeFiles/TestPass.dir/LocalOpts.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/TestPass.dir/LocalOpts.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/LocalOpts.cpp > CMakeFiles/TestPass.dir/LocalOpts.cpp.i

CMakeFiles/TestPass.dir/LocalOpts.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/TestPass.dir/LocalOpts.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/LocalOpts.cpp -o CMakeFiles/TestPass.dir/LocalOpts.cpp.s

# Object files for target TestPass
TestPass_OBJECTS = \
"CMakeFiles/TestPass.dir/LocalOpts.cpp.o"

# External object files for target TestPass
TestPass_EXTERNAL_OBJECTS =

libTestPass.dylib: CMakeFiles/TestPass.dir/LocalOpts.cpp.o
libTestPass.dylib: CMakeFiles/TestPass.dir/build.make
libTestPass.dylib: CMakeFiles/TestPass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libTestPass.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestPass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestPass.dir/build: libTestPass.dylib
.PHONY : CMakeFiles/TestPass.dir/build

CMakeFiles/TestPass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestPass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestPass.dir/clean

CMakeFiles/TestPass.dir/depend:
	cd /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2 /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2 /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build /Users/nitroroot/Desktop/uni/prove_compilatori/assgnm/passo2/build/CMakeFiles/TestPass.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TestPass.dir/depend

