# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /home/hubert/Downloads/cmake-3.26.4-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /home/hubert/Downloads/cmake-3.26.4-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hubert/projects/oskar-fork

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hubert/projects/oskar-fork/build

# Include any dependencies generated for this target.
include CMakeFiles/MyProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyProject.dir/flags.make

CMakeFiles/MyProject.dir/bin/Actors.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/bin/Actors.cpp.o: /home/hubert/projects/oskar-fork/bin/Actors.cpp
CMakeFiles/MyProject.dir/bin/Actors.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hubert/projects/oskar-fork/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyProject.dir/bin/Actors.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/bin/Actors.cpp.o -MF CMakeFiles/MyProject.dir/bin/Actors.cpp.o.d -o CMakeFiles/MyProject.dir/bin/Actors.cpp.o -c /home/hubert/projects/oskar-fork/bin/Actors.cpp

CMakeFiles/MyProject.dir/bin/Actors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/bin/Actors.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hubert/projects/oskar-fork/bin/Actors.cpp > CMakeFiles/MyProject.dir/bin/Actors.cpp.i

CMakeFiles/MyProject.dir/bin/Actors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/bin/Actors.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hubert/projects/oskar-fork/bin/Actors.cpp -o CMakeFiles/MyProject.dir/bin/Actors.cpp.s

CMakeFiles/MyProject.dir/bin/Eng.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/bin/Eng.cpp.o: /home/hubert/projects/oskar-fork/bin/Eng.cpp
CMakeFiles/MyProject.dir/bin/Eng.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hubert/projects/oskar-fork/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/MyProject.dir/bin/Eng.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/bin/Eng.cpp.o -MF CMakeFiles/MyProject.dir/bin/Eng.cpp.o.d -o CMakeFiles/MyProject.dir/bin/Eng.cpp.o -c /home/hubert/projects/oskar-fork/bin/Eng.cpp

CMakeFiles/MyProject.dir/bin/Eng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/bin/Eng.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hubert/projects/oskar-fork/bin/Eng.cpp > CMakeFiles/MyProject.dir/bin/Eng.cpp.i

CMakeFiles/MyProject.dir/bin/Eng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/bin/Eng.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hubert/projects/oskar-fork/bin/Eng.cpp -o CMakeFiles/MyProject.dir/bin/Eng.cpp.s

CMakeFiles/MyProject.dir/bin/main.cpp.o: CMakeFiles/MyProject.dir/flags.make
CMakeFiles/MyProject.dir/bin/main.cpp.o: /home/hubert/projects/oskar-fork/bin/main.cpp
CMakeFiles/MyProject.dir/bin/main.cpp.o: CMakeFiles/MyProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hubert/projects/oskar-fork/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/MyProject.dir/bin/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyProject.dir/bin/main.cpp.o -MF CMakeFiles/MyProject.dir/bin/main.cpp.o.d -o CMakeFiles/MyProject.dir/bin/main.cpp.o -c /home/hubert/projects/oskar-fork/bin/main.cpp

CMakeFiles/MyProject.dir/bin/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyProject.dir/bin/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hubert/projects/oskar-fork/bin/main.cpp > CMakeFiles/MyProject.dir/bin/main.cpp.i

CMakeFiles/MyProject.dir/bin/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyProject.dir/bin/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hubert/projects/oskar-fork/bin/main.cpp -o CMakeFiles/MyProject.dir/bin/main.cpp.s

# Object files for target MyProject
MyProject_OBJECTS = \
"CMakeFiles/MyProject.dir/bin/Actors.cpp.o" \
"CMakeFiles/MyProject.dir/bin/Eng.cpp.o" \
"CMakeFiles/MyProject.dir/bin/main.cpp.o"

# External object files for target MyProject
MyProject_EXTERNAL_OBJECTS =

MyProject: CMakeFiles/MyProject.dir/bin/Actors.cpp.o
MyProject: CMakeFiles/MyProject.dir/bin/Eng.cpp.o
MyProject: CMakeFiles/MyProject.dir/bin/main.cpp.o
MyProject: CMakeFiles/MyProject.dir/build.make
MyProject: /usr/lib/x86_64-linux-gnu/libSM.so
MyProject: /usr/lib/x86_64-linux-gnu/libICE.so
MyProject: /usr/lib/x86_64-linux-gnu/libX11.so
MyProject: /usr/lib/x86_64-linux-gnu/libXext.so
MyProject: /usr/lib/x86_64-linux-gnu/libXext.so
MyProject: CMakeFiles/MyProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hubert/projects/oskar-fork/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable MyProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyProject.dir/build: MyProject
.PHONY : CMakeFiles/MyProject.dir/build

CMakeFiles/MyProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyProject.dir/clean

CMakeFiles/MyProject.dir/depend:
	cd /home/hubert/projects/oskar-fork/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hubert/projects/oskar-fork /home/hubert/projects/oskar-fork /home/hubert/projects/oskar-fork/build /home/hubert/projects/oskar-fork/build /home/hubert/projects/oskar-fork/build/CMakeFiles/MyProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyProject.dir/depend

