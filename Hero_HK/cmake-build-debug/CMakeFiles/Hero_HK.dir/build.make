# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /home/tcrnx/include/cmake-3.24.3-linux-aarch64/bin/cmake

# The command to remove a file.
RM = /home/tcrnx/include/cmake-3.24.3-linux-aarch64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tcrnx/Hero_HK

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tcrnx/Hero_HK/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Hero_HK.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Hero_HK.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Hero_HK.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Hero_HK.dir/flags.make

CMakeFiles/Hero_HK.dir/main.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/main.cpp.o: /home/tcrnx/Hero_HK/main.cpp
CMakeFiles/Hero_HK.dir/main.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Hero_HK.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/main.cpp.o -MF CMakeFiles/Hero_HK.dir/main.cpp.o.d -o CMakeFiles/Hero_HK.dir/main.cpp.o -c /home/tcrnx/Hero_HK/main.cpp

CMakeFiles/Hero_HK.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/main.cpp > CMakeFiles/Hero_HK.dir/main.cpp.i

CMakeFiles/Hero_HK.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/main.cpp -o CMakeFiles/Hero_HK.dir/main.cpp.s

CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o: /home/tcrnx/Hero_HK/Thread/MyThread.cpp
CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o -MF CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o.d -o CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o -c /home/tcrnx/Hero_HK/Thread/MyThread.cpp

CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Thread/MyThread.cpp > CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.i

CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Thread/MyThread.cpp -o CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.s

CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o: /home/tcrnx/Hero_HK/Armor/ArmorDetect.cpp
CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o -MF CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o.d -o CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o -c /home/tcrnx/Hero_HK/Armor/ArmorDetect.cpp

CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Armor/ArmorDetect.cpp > CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.i

CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Armor/ArmorDetect.cpp -o CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.s

CMakeFiles/Hero_HK.dir/Drawing.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Drawing.cpp.o: /home/tcrnx/Hero_HK/Drawing.cpp
CMakeFiles/Hero_HK.dir/Drawing.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Hero_HK.dir/Drawing.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Drawing.cpp.o -MF CMakeFiles/Hero_HK.dir/Drawing.cpp.o.d -o CMakeFiles/Hero_HK.dir/Drawing.cpp.o -c /home/tcrnx/Hero_HK/Drawing.cpp

CMakeFiles/Hero_HK.dir/Drawing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Drawing.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Drawing.cpp > CMakeFiles/Hero_HK.dir/Drawing.cpp.i

CMakeFiles/Hero_HK.dir/Drawing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Drawing.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Drawing.cpp -o CMakeFiles/Hero_HK.dir/Drawing.cpp.s

CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o: /home/tcrnx/Hero_HK/Armor/LightBar.cpp
CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o -MF CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o.d -o CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o -c /home/tcrnx/Hero_HK/Armor/LightBar.cpp

CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Armor/LightBar.cpp > CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.i

CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Armor/LightBar.cpp -o CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.s

CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o: /home/tcrnx/Hero_HK/Armor/ArmorBox.cpp
CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o -MF CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o.d -o CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o -c /home/tcrnx/Hero_HK/Armor/ArmorBox.cpp

CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Armor/ArmorBox.cpp > CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.i

CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Armor/ArmorBox.cpp -o CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.s

CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o: CMakeFiles/Hero_HK.dir/flags.make
CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o: /home/tcrnx/Hero_HK/Armor/NumClassifier.cpp
CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o: CMakeFiles/Hero_HK.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o -MF CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o.d -o CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o -c /home/tcrnx/Hero_HK/Armor/NumClassifier.cpp

CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tcrnx/Hero_HK/Armor/NumClassifier.cpp > CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.i

CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tcrnx/Hero_HK/Armor/NumClassifier.cpp -o CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.s

# Object files for target Hero_HK
Hero_HK_OBJECTS = \
"CMakeFiles/Hero_HK.dir/main.cpp.o" \
"CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o" \
"CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o" \
"CMakeFiles/Hero_HK.dir/Drawing.cpp.o" \
"CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o" \
"CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o" \
"CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o"

# External object files for target Hero_HK
Hero_HK_EXTERNAL_OBJECTS =

Hero_HK: CMakeFiles/Hero_HK.dir/main.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Thread/MyThread.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Armor/ArmorDetect.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Drawing.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Armor/LightBar.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Armor/ArmorBox.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/Armor/NumClassifier.cpp.o
Hero_HK: CMakeFiles/Hero_HK.dir/build.make
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_gapi.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_video.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_dnn.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.4.5.4
Hero_HK: /usr/lib/aarch64-linux-gnu/libopencv_core.so.4.5.4
Hero_HK: CMakeFiles/Hero_HK.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Hero_HK"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Hero_HK.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Hero_HK.dir/build: Hero_HK
.PHONY : CMakeFiles/Hero_HK.dir/build

CMakeFiles/Hero_HK.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Hero_HK.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Hero_HK.dir/clean

CMakeFiles/Hero_HK.dir/depend:
	cd /home/tcrnx/Hero_HK/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tcrnx/Hero_HK /home/tcrnx/Hero_HK /home/tcrnx/Hero_HK/cmake-build-debug /home/tcrnx/Hero_HK/cmake-build-debug /home/tcrnx/Hero_HK/cmake-build-debug/CMakeFiles/Hero_HK.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Hero_HK.dir/depend

