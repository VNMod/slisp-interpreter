# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /vagrant

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /vagrant

# Include any dependencies generated for this target.
include CMakeFiles/slisp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/slisp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/slisp.dir/flags.make

CMakeFiles/slisp.dir/tokenize.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/tokenize.cpp.o: tokenize.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/slisp.dir/tokenize.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/tokenize.cpp.o -c /vagrant/tokenize.cpp

CMakeFiles/slisp.dir/tokenize.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/tokenize.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/tokenize.cpp > CMakeFiles/slisp.dir/tokenize.cpp.i

CMakeFiles/slisp.dir/tokenize.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/tokenize.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/tokenize.cpp -o CMakeFiles/slisp.dir/tokenize.cpp.s

CMakeFiles/slisp.dir/tokenize.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/tokenize.cpp.o.requires

CMakeFiles/slisp.dir/tokenize.cpp.o.provides: CMakeFiles/slisp.dir/tokenize.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/tokenize.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/tokenize.cpp.o.provides

CMakeFiles/slisp.dir/tokenize.cpp.o.provides.build: CMakeFiles/slisp.dir/tokenize.cpp.o


CMakeFiles/slisp.dir/expression.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/expression.cpp.o: expression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/slisp.dir/expression.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/expression.cpp.o -c /vagrant/expression.cpp

CMakeFiles/slisp.dir/expression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/expression.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/expression.cpp > CMakeFiles/slisp.dir/expression.cpp.i

CMakeFiles/slisp.dir/expression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/expression.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/expression.cpp -o CMakeFiles/slisp.dir/expression.cpp.s

CMakeFiles/slisp.dir/expression.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/expression.cpp.o.requires

CMakeFiles/slisp.dir/expression.cpp.o.provides: CMakeFiles/slisp.dir/expression.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/expression.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/expression.cpp.o.provides

CMakeFiles/slisp.dir/expression.cpp.o.provides.build: CMakeFiles/slisp.dir/expression.cpp.o


CMakeFiles/slisp.dir/environment.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/environment.cpp.o: environment.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/slisp.dir/environment.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/environment.cpp.o -c /vagrant/environment.cpp

CMakeFiles/slisp.dir/environment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/environment.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/environment.cpp > CMakeFiles/slisp.dir/environment.cpp.i

CMakeFiles/slisp.dir/environment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/environment.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/environment.cpp -o CMakeFiles/slisp.dir/environment.cpp.s

CMakeFiles/slisp.dir/environment.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/environment.cpp.o.requires

CMakeFiles/slisp.dir/environment.cpp.o.provides: CMakeFiles/slisp.dir/environment.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/environment.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/environment.cpp.o.provides

CMakeFiles/slisp.dir/environment.cpp.o.provides.build: CMakeFiles/slisp.dir/environment.cpp.o


CMakeFiles/slisp.dir/interpreter.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/interpreter.cpp.o: interpreter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/slisp.dir/interpreter.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/interpreter.cpp.o -c /vagrant/interpreter.cpp

CMakeFiles/slisp.dir/interpreter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/interpreter.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/interpreter.cpp > CMakeFiles/slisp.dir/interpreter.cpp.i

CMakeFiles/slisp.dir/interpreter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/interpreter.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/interpreter.cpp -o CMakeFiles/slisp.dir/interpreter.cpp.s

CMakeFiles/slisp.dir/interpreter.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/interpreter.cpp.o.requires

CMakeFiles/slisp.dir/interpreter.cpp.o.provides: CMakeFiles/slisp.dir/interpreter.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/interpreter.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/interpreter.cpp.o.provides

CMakeFiles/slisp.dir/interpreter.cpp.o.provides.build: CMakeFiles/slisp.dir/interpreter.cpp.o


CMakeFiles/slisp.dir/slisp.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/slisp.cpp.o: slisp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/slisp.dir/slisp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/slisp.cpp.o -c /vagrant/slisp.cpp

CMakeFiles/slisp.dir/slisp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/slisp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/slisp.cpp > CMakeFiles/slisp.dir/slisp.cpp.i

CMakeFiles/slisp.dir/slisp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/slisp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/slisp.cpp -o CMakeFiles/slisp.dir/slisp.cpp.s

CMakeFiles/slisp.dir/slisp.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/slisp.cpp.o.requires

CMakeFiles/slisp.dir/slisp.cpp.o.provides: CMakeFiles/slisp.dir/slisp.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/slisp.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/slisp.cpp.o.provides

CMakeFiles/slisp.dir/slisp.cpp.o.provides.build: CMakeFiles/slisp.dir/slisp.cpp.o


CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o: CMakeFiles/slisp.dir/flags.make
CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o: slisp_autogen/mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o -c /vagrant/slisp_autogen/mocs_compilation.cpp

CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /vagrant/slisp_autogen/mocs_compilation.cpp > CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.i

CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /vagrant/slisp_autogen/mocs_compilation.cpp -o CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.s

CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.requires:

.PHONY : CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.requires

CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.provides: CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.requires
	$(MAKE) -f CMakeFiles/slisp.dir/build.make CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.provides.build
.PHONY : CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.provides

CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.provides.build: CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o


# Object files for target slisp
slisp_OBJECTS = \
"CMakeFiles/slisp.dir/tokenize.cpp.o" \
"CMakeFiles/slisp.dir/expression.cpp.o" \
"CMakeFiles/slisp.dir/environment.cpp.o" \
"CMakeFiles/slisp.dir/interpreter.cpp.o" \
"CMakeFiles/slisp.dir/slisp.cpp.o" \
"CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o"

# External object files for target slisp
slisp_EXTERNAL_OBJECTS =

slisp: CMakeFiles/slisp.dir/tokenize.cpp.o
slisp: CMakeFiles/slisp.dir/expression.cpp.o
slisp: CMakeFiles/slisp.dir/environment.cpp.o
slisp: CMakeFiles/slisp.dir/interpreter.cpp.o
slisp: CMakeFiles/slisp.dir/slisp.cpp.o
slisp: CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o
slisp: CMakeFiles/slisp.dir/build.make
slisp: CMakeFiles/slisp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/vagrant/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable slisp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/slisp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/slisp.dir/build: slisp

.PHONY : CMakeFiles/slisp.dir/build

CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/tokenize.cpp.o.requires
CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/expression.cpp.o.requires
CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/environment.cpp.o.requires
CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/interpreter.cpp.o.requires
CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/slisp.cpp.o.requires
CMakeFiles/slisp.dir/requires: CMakeFiles/slisp.dir/slisp_autogen/mocs_compilation.cpp.o.requires

.PHONY : CMakeFiles/slisp.dir/requires

CMakeFiles/slisp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/slisp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/slisp.dir/clean

CMakeFiles/slisp.dir/depend:
	cd /vagrant && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /vagrant /vagrant /vagrant /vagrant /vagrant/CMakeFiles/slisp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/slisp.dir/depend

