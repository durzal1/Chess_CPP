# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Chess.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Chess.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Chess.dir/flags.make

CMakeFiles/Chess.dir/main.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/main.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Chess.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\main.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\main.cpp

CMakeFiles/Chess.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\main.cpp > CMakeFiles\Chess.dir\main.cpp.i

CMakeFiles/Chess.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\main.cpp -o CMakeFiles\Chess.dir\main.cpp.s

CMakeFiles/Chess.dir/board.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/board.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/board.cpp.obj: ../board.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Chess.dir/board.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\board.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\board.cpp

CMakeFiles/Chess.dir/board.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/board.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\board.cpp > CMakeFiles\Chess.dir\board.cpp.i

CMakeFiles/Chess.dir/board.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/board.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\board.cpp -o CMakeFiles\Chess.dir\board.cpp.s

CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj: ../getPossibleMoves.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\getPossibleMoves.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\getPossibleMoves.cpp

CMakeFiles/Chess.dir/getPossibleMoves.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/getPossibleMoves.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\getPossibleMoves.cpp > CMakeFiles\Chess.dir\getPossibleMoves.cpp.i

CMakeFiles/Chess.dir/getPossibleMoves.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/getPossibleMoves.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\getPossibleMoves.cpp -o CMakeFiles\Chess.dir\getPossibleMoves.cpp.s

CMakeFiles/Chess.dir/ai.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/ai.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/ai.cpp.obj: ../ai.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Chess.dir/ai.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\ai.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\ai.cpp

CMakeFiles/Chess.dir/ai.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/ai.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\ai.cpp > CMakeFiles\Chess.dir\ai.cpp.i

CMakeFiles/Chess.dir/ai.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/ai.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\ai.cpp -o CMakeFiles\Chess.dir\ai.cpp.s

CMakeFiles/Chess.dir/piece.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/piece.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/piece.cpp.obj: ../piece.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Chess.dir/piece.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\piece.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\piece.cpp

CMakeFiles/Chess.dir/piece.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/piece.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\piece.cpp > CMakeFiles\Chess.dir\piece.cpp.i

CMakeFiles/Chess.dir/piece.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/piece.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\piece.cpp -o CMakeFiles\Chess.dir\piece.cpp.s

CMakeFiles/Chess.dir/evaluate.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/evaluate.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/evaluate.cpp.obj: ../evaluate.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Chess.dir/evaluate.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\evaluate.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\evaluate.cpp

CMakeFiles/Chess.dir/evaluate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/evaluate.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\evaluate.cpp > CMakeFiles\Chess.dir\evaluate.cpp.i

CMakeFiles/Chess.dir/evaluate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/evaluate.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\evaluate.cpp -o CMakeFiles\Chess.dir\evaluate.cpp.s

CMakeFiles/Chess.dir/uci.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/uci.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/uci.cpp.obj: ../uci.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Chess.dir/uci.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\uci.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\uci.cpp

CMakeFiles/Chess.dir/uci.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/uci.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\uci.cpp > CMakeFiles\Chess.dir\uci.cpp.i

CMakeFiles/Chess.dir/uci.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/uci.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\uci.cpp -o CMakeFiles\Chess.dir\uci.cpp.s

CMakeFiles/Chess.dir/TranspositionTable.cpp.obj: CMakeFiles/Chess.dir/flags.make
CMakeFiles/Chess.dir/TranspositionTable.cpp.obj: CMakeFiles/Chess.dir/includes_CXX.rsp
CMakeFiles/Chess.dir/TranspositionTable.cpp.obj: ../TranspositionTable.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Chess.dir/TranspositionTable.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Chess.dir\TranspositionTable.cpp.obj -c C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\TranspositionTable.cpp

CMakeFiles/Chess.dir/TranspositionTable.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chess.dir/TranspositionTable.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\TranspositionTable.cpp > CMakeFiles\Chess.dir\TranspositionTable.cpp.i

CMakeFiles/Chess.dir/TranspositionTable.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chess.dir/TranspositionTable.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\TranspositionTable.cpp -o CMakeFiles\Chess.dir\TranspositionTable.cpp.s

# Object files for target Chess
Chess_OBJECTS = \
"CMakeFiles/Chess.dir/main.cpp.obj" \
"CMakeFiles/Chess.dir/board.cpp.obj" \
"CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj" \
"CMakeFiles/Chess.dir/ai.cpp.obj" \
"CMakeFiles/Chess.dir/piece.cpp.obj" \
"CMakeFiles/Chess.dir/evaluate.cpp.obj" \
"CMakeFiles/Chess.dir/uci.cpp.obj" \
"CMakeFiles/Chess.dir/TranspositionTable.cpp.obj"

# External object files for target Chess
Chess_EXTERNAL_OBJECTS =

Chess.exe: CMakeFiles/Chess.dir/main.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/board.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/getPossibleMoves.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/ai.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/piece.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/evaluate.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/uci.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/TranspositionTable.cpp.obj
Chess.exe: CMakeFiles/Chess.dir/build.make
Chess.exe: CMakeFiles/Chess.dir/linklibs.rsp
Chess.exe: CMakeFiles/Chess.dir/objects1.rsp
Chess.exe: CMakeFiles/Chess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable Chess.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Chess.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Chess.dir/build: Chess.exe
.PHONY : CMakeFiles/Chess.dir/build

CMakeFiles/Chess.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Chess.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Chess.dir/clean

CMakeFiles/Chess.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug C:\Users\zacky\Desktop\Coding\c++\games\chess\Chess_CPP\cmake-build-debug\CMakeFiles\Chess.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Chess.dir/depend

