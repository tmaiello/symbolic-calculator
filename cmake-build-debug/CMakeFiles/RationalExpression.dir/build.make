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
CMAKE_COMMAND = /cygdrive/c/Users/Boris/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Boris/.CLion2017.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/RationalExpression.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/RationalExpression.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RationalExpression.dir/flags.make

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o: CMakeFiles/RationalExpression.dir/flags.make
CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o: ../RationalExpression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o -c /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/RationalExpression.cpp

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RationalExpression.dir/RationalExpression.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/RationalExpression.cpp > CMakeFiles/RationalExpression.dir/RationalExpression.cpp.i

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RationalExpression.dir/RationalExpression.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/RationalExpression.cpp -o CMakeFiles/RationalExpression.dir/RationalExpression.cpp.s

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.requires:

.PHONY : CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.requires

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.provides: CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.requires
	$(MAKE) -f CMakeFiles/RationalExpression.dir/build.make CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.provides.build
.PHONY : CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.provides

CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.provides.build: CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o


# Object files for target RationalExpression
RationalExpression_OBJECTS = \
"CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o"

# External object files for target RationalExpression
RationalExpression_EXTERNAL_OBJECTS =

RationalExpression.exe: CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o
RationalExpression.exe: CMakeFiles/RationalExpression.dir/build.make
RationalExpression.exe: CMakeFiles/RationalExpression.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable RationalExpression.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RationalExpression.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RationalExpression.dir/build: RationalExpression.exe

.PHONY : CMakeFiles/RationalExpression.dir/build

CMakeFiles/RationalExpression.dir/requires: CMakeFiles/RationalExpression.dir/RationalExpression.cpp.o.requires

.PHONY : CMakeFiles/RationalExpression.dir/requires

CMakeFiles/RationalExpression.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/RationalExpression.dir/cmake_clean.cmake
.PHONY : CMakeFiles/RationalExpression.dir/clean

CMakeFiles/RationalExpression.dir/depend:
	cd /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug /cygdrive/c/Users/Boris/CLionProjects/symbolic-calculator/cmake-build-debug/CMakeFiles/RationalExpression.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RationalExpression.dir/depend

