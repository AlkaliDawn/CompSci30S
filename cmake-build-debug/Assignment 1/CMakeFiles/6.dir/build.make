# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\evanb\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.7571.171\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\evanb\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.7571.171\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\evanb\CLionProjects\CompSci30S

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug

# Include any dependencies generated for this target.
include Assignment\ 1/CMakeFiles/6.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Assignment\ 1/CMakeFiles/6.dir/compiler_depend.make

# Include the progress variables for this target.
include Assignment\ 1/CMakeFiles/6.dir/progress.make

# Include the compile flags for this target's objects.
include Assignment\ 1/CMakeFiles/6.dir/flags.make

Assignment\ 1/CMakeFiles/6.dir/6.cpp.obj: Assignment\ 1/CMakeFiles/6.dir/flags.make
Assignment\ 1/CMakeFiles/6.dir/6.cpp.obj: C:/Users/evanb/CLionProjects/CompSci30S/Assignment\ 1/6.cpp
Assignment\ 1/CMakeFiles/6.dir/6.cpp.obj: Assignment\ 1/CMakeFiles/6.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Assignment 1/CMakeFiles/6.dir/6.cpp.obj"
	cd /d C:\Users\evanb\CLIONP~1\CO4D02~1\CMAKE-~1\ASSIGN~1 && C:\Users\evanb\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.7571.171\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT "Assignment\ 1/CMakeFiles/6.dir/6.cpp.obj" -MF CMakeFiles\6.dir\6.cpp.obj.d -o CMakeFiles\6.dir\6.cpp.obj -c "C:\Users\evanb\CLionProjects\CompSci30S\Assignment 1\6.cpp"

Assignment\ 1/CMakeFiles/6.dir/6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/6.dir/6.cpp.i"
	cd /d C:\Users\evanb\CLIONP~1\CO4D02~1\CMAKE-~1\ASSIGN~1 && C:\Users\evanb\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.7571.171\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\evanb\CLionProjects\CompSci30S\Assignment 1\6.cpp" > CMakeFiles\6.dir\6.cpp.i

Assignment\ 1/CMakeFiles/6.dir/6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/6.dir/6.cpp.s"
	cd /d C:\Users\evanb\CLIONP~1\CO4D02~1\CMAKE-~1\ASSIGN~1 && C:\Users\evanb\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.7571.171\bin\mingw\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\evanb\CLionProjects\CompSci30S\Assignment 1\6.cpp" -o CMakeFiles\6.dir\6.cpp.s

# Object files for target 6
6_OBJECTS = \
"CMakeFiles/6.dir/6.cpp.obj"

# External object files for target 6
6_EXTERNAL_OBJECTS =

Assignment\ 1/6.exe: Assignment\ 1/CMakeFiles/6.dir/6.cpp.obj
Assignment\ 1/6.exe: Assignment\ 1/CMakeFiles/6.dir/build.make
Assignment\ 1/6.exe: Assignment\ 1/CMakeFiles/6.dir/linklibs.rsp
Assignment\ 1/6.exe: Assignment\ 1/CMakeFiles/6.dir/objects1.rsp
Assignment\ 1/6.exe: Assignment\ 1/CMakeFiles/6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 6.exe"
	cd /d C:\Users\evanb\CLIONP~1\CO4D02~1\CMAKE-~1\ASSIGN~1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\6.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Assignment\ 1/CMakeFiles/6.dir/build: Assignment\ 1/6.exe
.PHONY : Assignment\ 1/CMakeFiles/6.dir/build

Assignment\ 1/CMakeFiles/6.dir/clean:
	cd /d C:\Users\evanb\CLIONP~1\CO4D02~1\CMAKE-~1\ASSIGN~1 && $(CMAKE_COMMAND) -P CMakeFiles\6.dir\cmake_clean.cmake
.PHONY : Assignment\ 1/CMakeFiles/6.dir/clean

Assignment\ 1/CMakeFiles/6.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\evanb\CLionProjects\CompSci30S "C:\Users\evanb\CLionProjects\CompSci30S\Assignment 1" C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug "C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug\Assignment 1" "C:\Users\evanb\CLionProjects\CompSci30S\cmake-build-debug\Assignment 1\CMakeFiles\6.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : Assignment\ 1/CMakeFiles/6.dir/depend

