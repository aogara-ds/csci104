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
CMAKE_SOURCE_DIR = /work/hw-aogara/hw4/hw4_tests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/hw-aogara/hw4/hw4_tests

# Utility rule file for debug-BST.ConstructionDestruction.

# Include the progress variables for this target.
include bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/progress.make

bst_tests/CMakeFiles/debug-BST.ConstructionDestruction:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/hw-aogara/hw4/hw4_tests/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging BST.ConstructionDestruction with GDB..."
	cd /work/hw-aogara/hw4 && gdb --args /work/hw-aogara/hw4/hw4_tests/bst_tests/bst_tests --gtest_filter=BST.ConstructionDestruction

debug-BST.ConstructionDestruction: bst_tests/CMakeFiles/debug-BST.ConstructionDestruction
debug-BST.ConstructionDestruction: bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/build.make

.PHONY : debug-BST.ConstructionDestruction

# Rule to build all files generated by this target.
bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/build: debug-BST.ConstructionDestruction

.PHONY : bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/build

bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/clean:
	cd /work/hw-aogara/hw4/hw4_tests/bst_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-BST.ConstructionDestruction.dir/cmake_clean.cmake
.PHONY : bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/clean

bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/depend:
	cd /work/hw-aogara/hw4/hw4_tests && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-aogara/hw4/hw4_tests /work/hw-aogara/hw4/hw4_tests/bst_tests /work/hw-aogara/hw4/hw4_tests /work/hw-aogara/hw4/hw4_tests/bst_tests /work/hw-aogara/hw4/hw4_tests/bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bst_tests/CMakeFiles/debug-BST.ConstructionDestruction.dir/depend

