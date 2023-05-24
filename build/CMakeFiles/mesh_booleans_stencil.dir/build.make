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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build

# Include any dependencies generated for this target.
include CMakeFiles/mesh_booleans_stencil.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mesh_booleans_stencil.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mesh_booleans_stencil.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mesh_booleans_stencil.dir/flags.make

CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o: CMakeFiles/mesh_booleans_stencil.dir/flags.make
CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o: /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/main-stencil.cpp
CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o: CMakeFiles/mesh_booleans_stencil.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o -MF CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o.d -o CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o -c /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/main-stencil.cpp

CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/main-stencil.cpp > CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.i

CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/main-stencil.cpp -o CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.s

# Object files for target mesh_booleans_stencil
mesh_booleans_stencil_OBJECTS = \
"CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o"

# External object files for target mesh_booleans_stencil
mesh_booleans_stencil_EXTERNAL_OBJECTS =

mesh_booleans_stencil: CMakeFiles/mesh_booleans_stencil.dir/main-stencil.cpp.o
mesh_booleans_stencil: CMakeFiles/mesh_booleans_stencil.dir/build.make
mesh_booleans_stencil: appleclang_14.0_cxx17_64_release/libtbb.12.7.dylib
mesh_booleans_stencil: /Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
mesh_booleans_stencil: imgui/libimgui.a
mesh_booleans_stencil: imgui/glfw/src/libglfw3.a
mesh_booleans_stencil: shewchuk_predicates/libshewchuk_predicates.a
mesh_booleans_stencil: _deps/indirect_predicates-build/libindirectPredicates.a
mesh_booleans_stencil: CMakeFiles/mesh_booleans_stencil.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mesh_booleans_stencil"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesh_booleans_stencil.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mesh_booleans_stencil.dir/build: mesh_booleans_stencil
.PHONY : CMakeFiles/mesh_booleans_stencil.dir/build

CMakeFiles/mesh_booleans_stencil.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mesh_booleans_stencil.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mesh_booleans_stencil.dir/clean

CMakeFiles/mesh_booleans_stencil.dir/depend:
	cd /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build /Users/elisa/Desktop/Tirocinio/booleans_d/InteractiveAndRobustMeshBooleans/build/CMakeFiles/mesh_booleans_stencil.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mesh_booleans_stencil.dir/depend

