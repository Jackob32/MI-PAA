# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /cygdrive/c/Users/Jakub/.CLion2018.1/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/Jakub/.CLion2018.1/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/wtf.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wtf.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wtf.dir/flags.make

CMakeFiles/wtf.dir/main.cpp.o: CMakeFiles/wtf.dir/flags.make
CMakeFiles/wtf.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wtf.dir/main.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wtf.dir/main.cpp.o -c /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/main.cpp

CMakeFiles/wtf.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wtf.dir/main.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/main.cpp > CMakeFiles/wtf.dir/main.cpp.i

CMakeFiles/wtf.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wtf.dir/main.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/main.cpp -o CMakeFiles/wtf.dir/main.cpp.s

CMakeFiles/wtf.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/wtf.dir/main.cpp.o.requires

CMakeFiles/wtf.dir/main.cpp.o.provides: CMakeFiles/wtf.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/wtf.dir/build.make CMakeFiles/wtf.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/wtf.dir/main.cpp.o.provides

CMakeFiles/wtf.dir/main.cpp.o.provides.build: CMakeFiles/wtf.dir/main.cpp.o


# Object files for target wtf
wtf_OBJECTS = \
"CMakeFiles/wtf.dir/main.cpp.o"

# External object files for target wtf
wtf_EXTERNAL_OBJECTS =

wtf.exe: CMakeFiles/wtf.dir/main.cpp.o
wtf.exe: CMakeFiles/wtf.dir/build.make
wtf.exe: CMakeFiles/wtf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable wtf.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wtf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wtf.dir/build: wtf.exe

.PHONY : CMakeFiles/wtf.dir/build

CMakeFiles/wtf.dir/requires: CMakeFiles/wtf.dir/main.cpp.o.requires

.PHONY : CMakeFiles/wtf.dir/requires

CMakeFiles/wtf.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wtf.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wtf.dir/clean

CMakeFiles/wtf.dir/depend:
	cd /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug /cygdrive/c/Users/Jakub/GoogleDrive/Programming/C++/MI-PAA/wtf/cmake-build-debug/CMakeFiles/wtf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/wtf.dir/depend

