# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kucak7/semestralka

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kucak7/semestralka/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/server/server.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/server.c.o: /home/kucak7/semestralka/server/server.c
CMakeFiles/server.dir/server/server.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/server.dir/server/server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/server/server.c.o -MF CMakeFiles/server.dir/server/server.c.o.d -o CMakeFiles/server.dir/server/server.c.o -c /home/kucak7/semestralka/server/server.c

CMakeFiles/server.dir/server/server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server/server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/server/server.c > CMakeFiles/server.dir/server/server.c.i

CMakeFiles/server.dir/server/server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server/server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/server/server.c -o CMakeFiles/server.dir/server/server.c.s

CMakeFiles/server.dir/shm/buffer.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/shm/buffer.c.o: /home/kucak7/semestralka/shm/buffer.c
CMakeFiles/server.dir/shm/buffer.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/server.dir/shm/buffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/shm/buffer.c.o -MF CMakeFiles/server.dir/shm/buffer.c.o.d -o CMakeFiles/server.dir/shm/buffer.c.o -c /home/kucak7/semestralka/shm/buffer.c

CMakeFiles/server.dir/shm/buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/shm/buffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/shm/buffer.c > CMakeFiles/server.dir/shm/buffer.c.i

CMakeFiles/server.dir/shm/buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/shm/buffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/shm/buffer.c -o CMakeFiles/server.dir/shm/buffer.c.s

CMakeFiles/server.dir/shm/shm.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/shm/shm.c.o: /home/kucak7/semestralka/shm/shm.c
CMakeFiles/server.dir/shm/shm.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/server.dir/shm/shm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/shm/shm.c.o -MF CMakeFiles/server.dir/shm/shm.c.o.d -o CMakeFiles/server.dir/shm/shm.c.o -c /home/kucak7/semestralka/shm/shm.c

CMakeFiles/server.dir/shm/shm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/shm/shm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/shm/shm.c > CMakeFiles/server.dir/shm/shm.c.i

CMakeFiles/server.dir/shm/shm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/shm/shm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/shm/shm.c -o CMakeFiles/server.dir/shm/shm.c.s

CMakeFiles/server.dir/shm/synBuffer.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/shm/synBuffer.c.o: /home/kucak7/semestralka/shm/synBuffer.c
CMakeFiles/server.dir/shm/synBuffer.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/server.dir/shm/synBuffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/shm/synBuffer.c.o -MF CMakeFiles/server.dir/shm/synBuffer.c.o.d -o CMakeFiles/server.dir/shm/synBuffer.c.o -c /home/kucak7/semestralka/shm/synBuffer.c

CMakeFiles/server.dir/shm/synBuffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/shm/synBuffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/shm/synBuffer.c > CMakeFiles/server.dir/shm/synBuffer.c.i

CMakeFiles/server.dir/shm/synBuffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/shm/synBuffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/shm/synBuffer.c -o CMakeFiles/server.dir/shm/synBuffer.c.s

CMakeFiles/server.dir/shm/names.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/shm/names.c.o: /home/kucak7/semestralka/shm/names.c
CMakeFiles/server.dir/shm/names.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/server.dir/shm/names.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/shm/names.c.o -MF CMakeFiles/server.dir/shm/names.c.o.d -o CMakeFiles/server.dir/shm/names.c.o -c /home/kucak7/semestralka/shm/names.c

CMakeFiles/server.dir/shm/names.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/shm/names.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/shm/names.c > CMakeFiles/server.dir/shm/names.c.i

CMakeFiles/server.dir/shm/names.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/shm/names.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/shm/names.c -o CMakeFiles/server.dir/shm/names.c.s

CMakeFiles/server.dir/server/simulation.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/simulation.c.o: /home/kucak7/semestralka/server/simulation.c
CMakeFiles/server.dir/server/simulation.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/server.dir/server/simulation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/server/simulation.c.o -MF CMakeFiles/server.dir/server/simulation.c.o.d -o CMakeFiles/server.dir/server/simulation.c.o -c /home/kucak7/semestralka/server/simulation.c

CMakeFiles/server.dir/server/simulation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server/simulation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/server/simulation.c > CMakeFiles/server.dir/server/simulation.c.i

CMakeFiles/server.dir/server/simulation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server/simulation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/server/simulation.c -o CMakeFiles/server.dir/server/simulation.c.s

CMakeFiles/server.dir/client/drawThread.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/client/drawThread.c.o: /home/kucak7/semestralka/client/drawThread.c
CMakeFiles/server.dir/client/drawThread.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/server.dir/client/drawThread.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/client/drawThread.c.o -MF CMakeFiles/server.dir/client/drawThread.c.o.d -o CMakeFiles/server.dir/client/drawThread.c.o -c /home/kucak7/semestralka/client/drawThread.c

CMakeFiles/server.dir/client/drawThread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/client/drawThread.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/client/drawThread.c > CMakeFiles/server.dir/client/drawThread.c.i

CMakeFiles/server.dir/client/drawThread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/client/drawThread.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/client/drawThread.c -o CMakeFiles/server.dir/client/drawThread.c.s

CMakeFiles/server.dir/server/simThread.c.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/server/simThread.c.o: /home/kucak7/semestralka/server/simThread.c
CMakeFiles/server.dir/server/simThread.c.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/server.dir/server/simThread.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/server.dir/server/simThread.c.o -MF CMakeFiles/server.dir/server/simThread.c.o.d -o CMakeFiles/server.dir/server/simThread.c.o -c /home/kucak7/semestralka/server/simThread.c

CMakeFiles/server.dir/server/simThread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/server.dir/server/simThread.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/kucak7/semestralka/server/simThread.c > CMakeFiles/server.dir/server/simThread.c.i

CMakeFiles/server.dir/server/simThread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/server.dir/server/simThread.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/kucak7/semestralka/server/simThread.c -o CMakeFiles/server.dir/server/simThread.c.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/server/server.c.o" \
"CMakeFiles/server.dir/shm/buffer.c.o" \
"CMakeFiles/server.dir/shm/shm.c.o" \
"CMakeFiles/server.dir/shm/synBuffer.c.o" \
"CMakeFiles/server.dir/shm/names.c.o" \
"CMakeFiles/server.dir/server/simulation.c.o" \
"CMakeFiles/server.dir/client/drawThread.c.o" \
"CMakeFiles/server.dir/server/simThread.c.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/server/server.c.o
server: CMakeFiles/server.dir/shm/buffer.c.o
server: CMakeFiles/server.dir/shm/shm.c.o
server: CMakeFiles/server.dir/shm/synBuffer.c.o
server: CMakeFiles/server.dir/shm/names.c.o
server: CMakeFiles/server.dir/server/simulation.c.o
server: CMakeFiles/server.dir/client/drawThread.c.o
server: CMakeFiles/server.dir/server/simThread.c.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kucak7/semestralka/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/kucak7/semestralka/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kucak7/semestralka /home/kucak7/semestralka /home/kucak7/semestralka/cmake-build-debug /home/kucak7/semestralka/cmake-build-debug /home/kucak7/semestralka/cmake-build-debug/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

