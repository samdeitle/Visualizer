# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/samuel/Visualizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/samuel/Visualizer

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/samuel/Visualizer/CMakeFiles /home/samuel/Visualizer/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/samuel/Visualizer/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Visualizer

# Build rule for target.
Visualizer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Visualizer
.PHONY : Visualizer

# fast build rule for target.
Visualizer/fast:
	$(MAKE) -f CMakeFiles/Visualizer.dir/build.make CMakeFiles/Visualizer.dir/build
.PHONY : Visualizer/fast

Visualizer.o: Visualizer.cxx.o
.PHONY : Visualizer.o

# target to build an object file
Visualizer.cxx.o:
	$(MAKE) -f CMakeFiles/Visualizer.dir/build.make CMakeFiles/Visualizer.dir/Visualizer.cxx.o
.PHONY : Visualizer.cxx.o

Visualizer.i: Visualizer.cxx.i
.PHONY : Visualizer.i

# target to preprocess a source file
Visualizer.cxx.i:
	$(MAKE) -f CMakeFiles/Visualizer.dir/build.make CMakeFiles/Visualizer.dir/Visualizer.cxx.i
.PHONY : Visualizer.cxx.i

Visualizer.s: Visualizer.cxx.s
.PHONY : Visualizer.s

# target to generate assembly for a file
Visualizer.cxx.s:
	$(MAKE) -f CMakeFiles/Visualizer.dir/build.make CMakeFiles/Visualizer.dir/Visualizer.cxx.s
.PHONY : Visualizer.cxx.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... Visualizer"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... Visualizer.o"
	@echo "... Visualizer.i"
	@echo "... Visualizer.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

