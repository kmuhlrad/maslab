# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/katy/MASLAB/vision

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/katy/MASLAB/vision

# Include any dependencies generated for this target.
include CMakeFiles/shapes6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/shapes6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/shapes6.dir/flags.make

CMakeFiles/shapes6.dir/shapes6.cpp.o: CMakeFiles/shapes6.dir/flags.make
CMakeFiles/shapes6.dir/shapes6.cpp.o: shapes6.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/katy/MASLAB/vision/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/shapes6.dir/shapes6.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/shapes6.dir/shapes6.cpp.o -c /Users/katy/MASLAB/vision/shapes6.cpp

CMakeFiles/shapes6.dir/shapes6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/shapes6.dir/shapes6.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/katy/MASLAB/vision/shapes6.cpp > CMakeFiles/shapes6.dir/shapes6.cpp.i

CMakeFiles/shapes6.dir/shapes6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/shapes6.dir/shapes6.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/katy/MASLAB/vision/shapes6.cpp -o CMakeFiles/shapes6.dir/shapes6.cpp.s

CMakeFiles/shapes6.dir/shapes6.cpp.o.requires:
.PHONY : CMakeFiles/shapes6.dir/shapes6.cpp.o.requires

CMakeFiles/shapes6.dir/shapes6.cpp.o.provides: CMakeFiles/shapes6.dir/shapes6.cpp.o.requires
	$(MAKE) -f CMakeFiles/shapes6.dir/build.make CMakeFiles/shapes6.dir/shapes6.cpp.o.provides.build
.PHONY : CMakeFiles/shapes6.dir/shapes6.cpp.o.provides

CMakeFiles/shapes6.dir/shapes6.cpp.o.provides.build: CMakeFiles/shapes6.dir/shapes6.cpp.o

# Object files for target shapes6
shapes6_OBJECTS = \
"CMakeFiles/shapes6.dir/shapes6.cpp.o"

# External object files for target shapes6
shapes6_EXTERNAL_OBJECTS =

shapes6: CMakeFiles/shapes6.dir/shapes6.cpp.o
shapes6: CMakeFiles/shapes6.dir/build.make
shapes6: /usr/local/lib/libopencv_videostab.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_video.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_ts.a
shapes6: /usr/local/lib/libopencv_superres.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_stitching.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_photo.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_ocl.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_objdetect.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_nonfree.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_ml.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_legacy.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_imgproc.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_highgui.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_gpu.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_flann.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_features2d.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_core.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_contrib.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_calib3d.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_nonfree.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_ocl.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_gpu.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_photo.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_objdetect.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_legacy.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_video.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_ml.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_calib3d.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_features2d.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_highgui.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_imgproc.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_flann.2.4.10.dylib
shapes6: /usr/local/lib/libopencv_core.2.4.10.dylib
shapes6: CMakeFiles/shapes6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable shapes6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/shapes6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/shapes6.dir/build: shapes6
.PHONY : CMakeFiles/shapes6.dir/build

CMakeFiles/shapes6.dir/requires: CMakeFiles/shapes6.dir/shapes6.cpp.o.requires
.PHONY : CMakeFiles/shapes6.dir/requires

CMakeFiles/shapes6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/shapes6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/shapes6.dir/clean

CMakeFiles/shapes6.dir/depend:
	cd /Users/katy/MASLAB/vision && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/katy/MASLAB/vision /Users/katy/MASLAB/vision /Users/katy/MASLAB/vision /Users/katy/MASLAB/vision /Users/katy/MASLAB/vision/CMakeFiles/shapes6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/shapes6.dir/depend

