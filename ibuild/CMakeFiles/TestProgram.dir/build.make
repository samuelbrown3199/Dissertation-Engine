# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\SDKs\cmake-3.18.3-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = C:\SDKs\cmake-3.18.3-win64-x64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild

# Include any dependencies generated for this target.
include CMakeFiles\TestProgram.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\TestProgram.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\TestProgram.dir\flags.make

CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj: CMakeFiles\TestProgram.dir\flags.make
CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj: CMakeFiles\TestProgram.dir\includes_CXX.rsp
CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj: ..\src\TestProgram\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestProgram.dir/src/TestProgram/main.cpp.obj"
	C:\PROGRA~2\Intel\oneAPI\compiler\latest\windows\bin\CLANG_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj -c C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\src\TestProgram\main.cpp

CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestProgram.dir/src/TestProgram/main.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestProgram.dir/src/TestProgram/main.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj: CMakeFiles\TestProgram.dir\flags.make
CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj: CMakeFiles\TestProgram.dir\includes_CXX.rsp
CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj: ..\src\TestProgram\FlyingCamSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TestProgram.dir/src/TestProgram/FlyingCamSystem.cpp.obj"
	C:\PROGRA~2\Intel\oneAPI\compiler\latest\windows\bin\CLANG_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj -c C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\src\TestProgram\FlyingCamSystem.cpp

CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestProgram.dir/src/TestProgram/FlyingCamSystem.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestProgram.dir/src/TestProgram/FlyingCamSystem.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj: CMakeFiles\TestProgram.dir\flags.make
CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj: CMakeFiles\TestProgram.dir\includes_CXX.rsp
CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj: ..\src\TestProgram\RotatorSystem.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TestProgram.dir/src/TestProgram/RotatorSystem.cpp.obj"
	C:\PROGRA~2\Intel\oneAPI\compiler\latest\windows\bin\CLANG_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj -c C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\src\TestProgram\RotatorSystem.cpp

CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestProgram.dir/src/TestProgram/RotatorSystem.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestProgram.dir/src/TestProgram/RotatorSystem.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj: CMakeFiles\TestProgram.dir\flags.make
CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj: CMakeFiles\TestProgram.dir\includes_CXX.rsp
CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj: ..\src\TestProgram\TestUI.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TestProgram.dir/src/TestProgram/TestUI.cpp.obj"
	C:\PROGRA~2\Intel\oneAPI\compiler\latest\windows\bin\CLANG_~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj -c C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\src\TestProgram\TestUI.cpp

CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestProgram.dir/src/TestProgram/TestUI.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestProgram.dir/src/TestProgram/TestUI.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

# Object files for target TestProgram
TestProgram_OBJECTS = \
"CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj" \
"CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj" \
"CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj" \
"CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj"

# External object files for target TestProgram
TestProgram_EXTERNAL_OBJECTS =

TestProgram.exe: CMakeFiles\TestProgram.dir\src\TestProgram\main.cpp.obj
TestProgram.exe: CMakeFiles\TestProgram.dir\src\TestProgram\FlyingCamSystem.cpp.obj
TestProgram.exe: CMakeFiles\TestProgram.dir\src\TestProgram\RotatorSystem.cpp.obj
TestProgram.exe: CMakeFiles\TestProgram.dir\src\TestProgram\TestUI.cpp.obj
TestProgram.exe: CMakeFiles\TestProgram.dir\build.make
TestProgram.exe: NobleEngine.lib
TestProgram.exe: CMakeFiles\TestProgram.dir\linklibs.rsp
TestProgram.exe: CMakeFiles\TestProgram.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable TestProgram.exe"
	C:\PROGRA~2\Intel\oneAPI\compiler\latest\windows\bin\CLANG_~1.EXE -fuse-ld=lld-link -nostartfiles -nostdlib @CMakeFiles\TestProgram.dir\objects1.rsp -o TestProgram.exe -Xlinker /implib:TestProgram.lib -Xlinker /pdb:C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\TestProgram.pdb -Xlinker /version:0.0  @CMakeFiles\TestProgram.dir\linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles\TestProgram.dir\build: TestProgram.exe

.PHONY : CMakeFiles\TestProgram.dir\build

CMakeFiles\TestProgram.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TestProgram.dir\cmake_clean.cmake
.PHONY : CMakeFiles\TestProgram.dir\clean

CMakeFiles\TestProgram.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild C:\Users\samue\Desktop\GamesDevelopment\Projects\Noble\ibuild\CMakeFiles\TestProgram.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\TestProgram.dir\depend
