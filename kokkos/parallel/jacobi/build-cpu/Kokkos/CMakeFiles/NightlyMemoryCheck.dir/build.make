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
CMAKE_COMMAND = /apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/cmake-3.18.4-kw3wpvkxke7lo3atixjcvt4roclfopip/bin/cmake

# The command to remove a file.
RM = /apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/cmake-3.18.4-kw3wpvkxke7lo3atixjcvt4roclfopip/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu

# Utility rule file for NightlyMemoryCheck.

# Include the progress variables for this target.
include Kokkos/CMakeFiles/NightlyMemoryCheck.dir/progress.make

Kokkos/CMakeFiles/NightlyMemoryCheck:
	cd /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu/Kokkos && /apps/spack/0.16.0/opt/spack/linux-rhel7-skylake_avx512/gcc-10.2.0/cmake-3.18.4-kw3wpvkxke7lo3atixjcvt4roclfopip/bin/ctest -D NightlyMemoryCheck

NightlyMemoryCheck: Kokkos/CMakeFiles/NightlyMemoryCheck
NightlyMemoryCheck: Kokkos/CMakeFiles/NightlyMemoryCheck.dir/build.make

.PHONY : NightlyMemoryCheck

# Rule to build all files generated by this target.
Kokkos/CMakeFiles/NightlyMemoryCheck.dir/build: NightlyMemoryCheck

.PHONY : Kokkos/CMakeFiles/NightlyMemoryCheck.dir/build

Kokkos/CMakeFiles/NightlyMemoryCheck.dir/clean:
	cd /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu/Kokkos && $(CMAKE_COMMAND) -P CMakeFiles/NightlyMemoryCheck.dir/cmake_clean.cmake
.PHONY : Kokkos/CMakeFiles/NightlyMemoryCheck.dir/clean

Kokkos/CMakeFiles/NightlyMemoryCheck.dir/depend:
	cd /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi /home/groubahiefissa/chps/chps0801_projet/kokkos/dep/Kokkos /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu/Kokkos /home/groubahiefissa/chps/chps0801_projet/kokkos/parallel/jacobi/build-cpu/Kokkos/CMakeFiles/NightlyMemoryCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Kokkos/CMakeFiles/NightlyMemoryCheck.dir/depend

