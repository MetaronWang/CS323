# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/metaron/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.144/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/metaron/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.144/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/metaron/Nextcloud/CS323/CS323/project3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/metaron/Nextcloud/CS323/CS323/project3/cmake-build-debug

# Utility rule file for makeScanner.

# Include the progress variables for this target.
include CMakeFiles/makeScanner.dir/progress.make

CMakeFiles/makeScanner:
	make splc -C /home/metaron/Nextcloud/CS323/CS323/project3 CLION_EXE_DIR=/home/metaron/Nextcloud/CS323/CS323/project3

makeScanner: CMakeFiles/makeScanner
makeScanner: CMakeFiles/makeScanner.dir/build.make

.PHONY : makeScanner

# Rule to build all files generated by this target.
CMakeFiles/makeScanner.dir/build: makeScanner

.PHONY : CMakeFiles/makeScanner.dir/build

CMakeFiles/makeScanner.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/makeScanner.dir/cmake_clean.cmake
.PHONY : CMakeFiles/makeScanner.dir/clean

CMakeFiles/makeScanner.dir/depend:
	cd /home/metaron/Nextcloud/CS323/CS323/project3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/metaron/Nextcloud/CS323/CS323/project3 /home/metaron/Nextcloud/CS323/CS323/project3 /home/metaron/Nextcloud/CS323/CS323/project3/cmake-build-debug /home/metaron/Nextcloud/CS323/CS323/project3/cmake-build-debug /home/metaron/Nextcloud/CS323/CS323/project3/cmake-build-debug/CMakeFiles/makeScanner.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/makeScanner.dir/depend

