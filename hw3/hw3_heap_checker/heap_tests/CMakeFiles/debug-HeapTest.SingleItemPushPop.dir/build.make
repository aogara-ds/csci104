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
CMAKE_SOURCE_DIR = /work/hw-aogara/hw3/hw3_heap_checker

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/hw-aogara/hw3/hw3_heap_checker

# Utility rule file for debug-HeapTest.SingleItemPushPop.

# Include the progress variables for this target.
include heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/progress.make

heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/hw-aogara/hw3/hw3_heap_checker/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Debugging HeapTest.SingleItemPushPop with GDB..."
	cd /work/hw-aogara/hw3 && gdb --args /work/hw-aogara/hw3/hw3_heap_checker/heap_tests/heap_tests --gtest_filter=HeapTest.SingleItemPushPop

debug-HeapTest.SingleItemPushPop: heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop
debug-HeapTest.SingleItemPushPop: heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/build.make

.PHONY : debug-HeapTest.SingleItemPushPop

# Rule to build all files generated by this target.
heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/build: debug-HeapTest.SingleItemPushPop

.PHONY : heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/build

heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/clean:
	cd /work/hw-aogara/hw3/hw3_heap_checker/heap_tests && $(CMAKE_COMMAND) -P CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/cmake_clean.cmake
.PHONY : heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/clean

heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/depend:
	cd /work/hw-aogara/hw3/hw3_heap_checker && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/hw-aogara/hw3/hw3_heap_checker /work/hw-aogara/hw3/hw3_heap_checker/heap_tests /work/hw-aogara/hw3/hw3_heap_checker /work/hw-aogara/hw3/hw3_heap_checker/heap_tests /work/hw-aogara/hw3/hw3_heap_checker/heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : heap_tests/CMakeFiles/debug-HeapTest.SingleItemPushPop.dir/depend

