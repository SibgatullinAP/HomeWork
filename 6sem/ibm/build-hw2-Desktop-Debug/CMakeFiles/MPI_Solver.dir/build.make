# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pam/HomeWork/6sem/ibm/hw2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug

# Include any dependencies generated for this target.
include CMakeFiles/MPI_Solver.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MPI_Solver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MPI_Solver.dir/flags.make

CMakeFiles/MPI_Solver.dir/main.cpp.o: CMakeFiles/MPI_Solver.dir/flags.make
CMakeFiles/MPI_Solver.dir/main.cpp.o: /home/pam/HomeWork/6sem/ibm/hw2/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MPI_Solver.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_Solver.dir/main.cpp.o -c /home/pam/HomeWork/6sem/ibm/hw2/main.cpp

CMakeFiles/MPI_Solver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_Solver.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pam/HomeWork/6sem/ibm/hw2/main.cpp > CMakeFiles/MPI_Solver.dir/main.cpp.i

CMakeFiles/MPI_Solver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_Solver.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pam/HomeWork/6sem/ibm/hw2/main.cpp -o CMakeFiles/MPI_Solver.dir/main.cpp.s

CMakeFiles/MPI_Solver.dir/matrix.cpp.o: CMakeFiles/MPI_Solver.dir/flags.make
CMakeFiles/MPI_Solver.dir/matrix.cpp.o: /home/pam/HomeWork/6sem/ibm/hw2/matrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MPI_Solver.dir/matrix.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_Solver.dir/matrix.cpp.o -c /home/pam/HomeWork/6sem/ibm/hw2/matrix.cpp

CMakeFiles/MPI_Solver.dir/matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_Solver.dir/matrix.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pam/HomeWork/6sem/ibm/hw2/matrix.cpp > CMakeFiles/MPI_Solver.dir/matrix.cpp.i

CMakeFiles/MPI_Solver.dir/matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_Solver.dir/matrix.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pam/HomeWork/6sem/ibm/hw2/matrix.cpp -o CMakeFiles/MPI_Solver.dir/matrix.cpp.s

CMakeFiles/MPI_Solver.dir/arguments.cpp.o: CMakeFiles/MPI_Solver.dir/flags.make
CMakeFiles/MPI_Solver.dir/arguments.cpp.o: /home/pam/HomeWork/6sem/ibm/hw2/arguments.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MPI_Solver.dir/arguments.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_Solver.dir/arguments.cpp.o -c /home/pam/HomeWork/6sem/ibm/hw2/arguments.cpp

CMakeFiles/MPI_Solver.dir/arguments.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_Solver.dir/arguments.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pam/HomeWork/6sem/ibm/hw2/arguments.cpp > CMakeFiles/MPI_Solver.dir/arguments.cpp.i

CMakeFiles/MPI_Solver.dir/arguments.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_Solver.dir/arguments.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pam/HomeWork/6sem/ibm/hw2/arguments.cpp -o CMakeFiles/MPI_Solver.dir/arguments.cpp.s

CMakeFiles/MPI_Solver.dir/solver.cpp.o: CMakeFiles/MPI_Solver.dir/flags.make
CMakeFiles/MPI_Solver.dir/solver.cpp.o: /home/pam/HomeWork/6sem/ibm/hw2/solver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/MPI_Solver.dir/solver.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/MPI_Solver.dir/solver.cpp.o -c /home/pam/HomeWork/6sem/ibm/hw2/solver.cpp

CMakeFiles/MPI_Solver.dir/solver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MPI_Solver.dir/solver.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pam/HomeWork/6sem/ibm/hw2/solver.cpp > CMakeFiles/MPI_Solver.dir/solver.cpp.i

CMakeFiles/MPI_Solver.dir/solver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MPI_Solver.dir/solver.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pam/HomeWork/6sem/ibm/hw2/solver.cpp -o CMakeFiles/MPI_Solver.dir/solver.cpp.s

# Object files for target MPI_Solver
MPI_Solver_OBJECTS = \
"CMakeFiles/MPI_Solver.dir/main.cpp.o" \
"CMakeFiles/MPI_Solver.dir/matrix.cpp.o" \
"CMakeFiles/MPI_Solver.dir/arguments.cpp.o" \
"CMakeFiles/MPI_Solver.dir/solver.cpp.o"

# External object files for target MPI_Solver
MPI_Solver_EXTERNAL_OBJECTS =

MPI_Solver: CMakeFiles/MPI_Solver.dir/main.cpp.o
MPI_Solver: CMakeFiles/MPI_Solver.dir/matrix.cpp.o
MPI_Solver: CMakeFiles/MPI_Solver.dir/arguments.cpp.o
MPI_Solver: CMakeFiles/MPI_Solver.dir/solver.cpp.o
MPI_Solver: CMakeFiles/MPI_Solver.dir/build.make
MPI_Solver: CMakeFiles/MPI_Solver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable MPI_Solver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MPI_Solver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MPI_Solver.dir/build: MPI_Solver

.PHONY : CMakeFiles/MPI_Solver.dir/build

CMakeFiles/MPI_Solver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MPI_Solver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MPI_Solver.dir/clean

CMakeFiles/MPI_Solver.dir/depend:
	cd /home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pam/HomeWork/6sem/ibm/hw2 /home/pam/HomeWork/6sem/ibm/hw2 /home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug /home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug /home/pam/HomeWork/6sem/ibm/build-hw2-Desktop-Debug/CMakeFiles/MPI_Solver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MPI_Solver.dir/depend
