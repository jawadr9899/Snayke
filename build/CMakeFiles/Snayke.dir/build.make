# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = "C:/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Program Files/CMake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:/Users/Jawad/Desktop/C++-Snake/Snake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:/Users/Jawad/Desktop/C++-Snake/Snake/build

# Include any dependencies generated for this target.
include CMakeFiles/Snayke.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Snayke.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Snayke.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Snayke.dir/flags.make

CMakeFiles/Snayke.dir/src/main.cpp.obj: CMakeFiles/Snayke.dir/flags.make
CMakeFiles/Snayke.dir/src/main.cpp.obj: CMakeFiles/Snayke.dir/includes_CXX.rsp
CMakeFiles/Snayke.dir/src/main.cpp.obj: C:/Users/Jawad/Desktop/C++-Snake/Snake/src/main.cpp
CMakeFiles/Snayke.dir/src/main.cpp.obj: CMakeFiles/Snayke.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:/Users/Jawad/Desktop/C++-Snake/Snake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Snayke.dir/src/main.cpp.obj"
	C:/msys64/mingw64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Snayke.dir/src/main.cpp.obj -MF CMakeFiles/Snayke.dir/src/main.cpp.obj.d -o CMakeFiles/Snayke.dir/src/main.cpp.obj -c C:/Users/Jawad/Desktop/C++-Snake/Snake/src/main.cpp

CMakeFiles/Snayke.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Snayke.dir/src/main.cpp.i"
	C:/msys64/mingw64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:/Users/Jawad/Desktop/C++-Snake/Snake/src/main.cpp > CMakeFiles/Snayke.dir/src/main.cpp.i

CMakeFiles/Snayke.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Snayke.dir/src/main.cpp.s"
	C:/msys64/mingw64/bin/clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:/Users/Jawad/Desktop/C++-Snake/Snake/src/main.cpp -o CMakeFiles/Snayke.dir/src/main.cpp.s

# Object files for target Snayke
Snayke_OBJECTS = \
"CMakeFiles/Snayke.dir/src/main.cpp.obj"

# External object files for target Snayke
Snayke_EXTERNAL_OBJECTS =

Snayke.exe: CMakeFiles/Snayke.dir/src/main.cpp.obj
Snayke.exe: CMakeFiles/Snayke.dir/build.make
Snayke.exe: libSnayke_lib.a
Snayke.exe: C:/msys64/mingw64/lib/libsfml-graphics.dll.a
Snayke.exe: C:/msys64/mingw64/lib/libsfml-audio.dll.a
Snayke.exe: C:/msys64/mingw64/lib/libsfml-network.dll.a
Snayke.exe: C:/msys64/mingw64/lib/libsfml-window.dll.a
Snayke.exe: C:/msys64/mingw64/lib/libsfml-system.dll.a
Snayke.exe: CMakeFiles/Snayke.dir/linkLibs.rsp
Snayke.exe: CMakeFiles/Snayke.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:/Users/Jawad/Desktop/C++-Snake/Snake/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Snayke.exe"
	"C:/Program Files/CMake/bin/cmake.exe" -E rm -f CMakeFiles/Snayke.dir/objects.a
	C:/msys64/mingw64/bin/llvm-ar.exe qc CMakeFiles/Snayke.dir/objects.a @CMakeFiles/Snayke.dir/objects1.rsp
	C:/msys64/mingw64/bin/clang++.exe -g  -mwindows -Wl,--whole-archive CMakeFiles/Snayke.dir/objects.a -Wl,--no-whole-archive -o Snayke.exe -Wl,--out-implib,libSnayke.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/Snayke.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/Snayke.dir/build: Snayke.exe
.PHONY : CMakeFiles/Snayke.dir/build

CMakeFiles/Snayke.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Snayke.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Snayke.dir/clean

CMakeFiles/Snayke.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" C:/Users/Jawad/Desktop/C++-Snake/Snake C:/Users/Jawad/Desktop/C++-Snake/Snake C:/Users/Jawad/Desktop/C++-Snake/Snake/build C:/Users/Jawad/Desktop/C++-Snake/Snake/build C:/Users/Jawad/Desktop/C++-Snake/Snake/build/CMakeFiles/Snayke.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Snayke.dir/depend
