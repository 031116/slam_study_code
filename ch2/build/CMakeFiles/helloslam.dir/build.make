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
CMAKE_SOURCE_DIR = /home/psj/Desktop/slam_study/ch2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/psj/Desktop/slam_study/ch2/build

# Include any dependencies generated for this target.
include CMakeFiles/helloslam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helloslam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helloslam.dir/flags.make

CMakeFiles/helloslam.dir/src/helloslam.cpp.o: CMakeFiles/helloslam.dir/flags.make
CMakeFiles/helloslam.dir/src/helloslam.cpp.o: ../src/helloslam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/psj/Desktop/slam_study/ch2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/helloslam.dir/src/helloslam.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/helloslam.dir/src/helloslam.cpp.o -c /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp

CMakeFiles/helloslam.dir/src/helloslam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloslam.dir/src/helloslam.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp > CMakeFiles/helloslam.dir/src/helloslam.cpp.i

CMakeFiles/helloslam.dir/src/helloslam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloslam.dir/src/helloslam.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/psj/Desktop/slam_study/ch2/src/helloslam.cpp -o CMakeFiles/helloslam.dir/src/helloslam.cpp.s

# Object files for target helloslam
helloslam_OBJECTS = \
"CMakeFiles/helloslam.dir/src/helloslam.cpp.o"

# External object files for target helloslam
helloslam_EXTERNAL_OBJECTS =

libhelloslam.so: CMakeFiles/helloslam.dir/src/helloslam.cpp.o
libhelloslam.so: CMakeFiles/helloslam.dir/build.make
libhelloslam.so: CMakeFiles/helloslam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/psj/Desktop/slam_study/ch2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libhelloslam.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloslam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helloslam.dir/build: libhelloslam.so

.PHONY : CMakeFiles/helloslam.dir/build

CMakeFiles/helloslam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/helloslam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/helloslam.dir/clean

CMakeFiles/helloslam.dir/depend:
	cd /home/psj/Desktop/slam_study/ch2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/psj/Desktop/slam_study/ch2 /home/psj/Desktop/slam_study/ch2 /home/psj/Desktop/slam_study/ch2/build /home/psj/Desktop/slam_study/ch2/build /home/psj/Desktop/slam_study/ch2/build/CMakeFiles/helloslam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helloslam.dir/depend

