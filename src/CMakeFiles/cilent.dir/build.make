# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fuhao/project/socket/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fuhao/project/socket/src

# Include any dependencies generated for this target.
include CMakeFiles/cilent.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cilent.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cilent.dir/flags.make

CMakeFiles/cilent.dir/cilent.c.o: CMakeFiles/cilent.dir/flags.make
CMakeFiles/cilent.dir/cilent.c.o: cilent.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fuhao/project/socket/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cilent.dir/cilent.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cilent.dir/cilent.c.o   -c /home/fuhao/project/socket/src/cilent.c

CMakeFiles/cilent.dir/cilent.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cilent.dir/cilent.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/fuhao/project/socket/src/cilent.c > CMakeFiles/cilent.dir/cilent.c.i

CMakeFiles/cilent.dir/cilent.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cilent.dir/cilent.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/fuhao/project/socket/src/cilent.c -o CMakeFiles/cilent.dir/cilent.c.s

# Object files for target cilent
cilent_OBJECTS = \
"CMakeFiles/cilent.dir/cilent.c.o"

# External object files for target cilent
cilent_EXTERNAL_OBJECTS =

cilent: CMakeFiles/cilent.dir/cilent.c.o
cilent: CMakeFiles/cilent.dir/build.make
cilent: CMakeFiles/cilent.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fuhao/project/socket/src/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cilent"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cilent.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cilent.dir/build: cilent

.PHONY : CMakeFiles/cilent.dir/build

CMakeFiles/cilent.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cilent.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cilent.dir/clean

CMakeFiles/cilent.dir/depend:
	cd /home/fuhao/project/socket/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fuhao/project/socket/src /home/fuhao/project/socket/src /home/fuhao/project/socket/src /home/fuhao/project/socket/src /home/fuhao/project/socket/src/CMakeFiles/cilent.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cilent.dir/depend

