# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/yanko/work/first_thousand_words/google_translate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yanko/work/first_thousand_words/google_translate

# Include any dependencies generated for this target.
include CMakeFiles/translator.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/translator.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/translator.dir/flags.make

CMakeFiles/translator.dir/main.cpp.o: CMakeFiles/translator.dir/flags.make
CMakeFiles/translator.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yanko/work/first_thousand_words/google_translate/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/translator.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/translator.dir/main.cpp.o -c /home/yanko/work/first_thousand_words/google_translate/main.cpp

CMakeFiles/translator.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/translator.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yanko/work/first_thousand_words/google_translate/main.cpp > CMakeFiles/translator.dir/main.cpp.i

CMakeFiles/translator.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/translator.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yanko/work/first_thousand_words/google_translate/main.cpp -o CMakeFiles/translator.dir/main.cpp.s

CMakeFiles/translator.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/translator.dir/main.cpp.o.requires

CMakeFiles/translator.dir/main.cpp.o.provides: CMakeFiles/translator.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/translator.dir/build.make CMakeFiles/translator.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/translator.dir/main.cpp.o.provides

CMakeFiles/translator.dir/main.cpp.o.provides.build: CMakeFiles/translator.dir/main.cpp.o

# Object files for target translator
translator_OBJECTS = \
"CMakeFiles/translator.dir/main.cpp.o"

# External object files for target translator
translator_EXTERNAL_OBJECTS =

translator: CMakeFiles/translator.dir/main.cpp.o
translator: CMakeFiles/translator.dir/build.make
translator: CMakeFiles/translator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable translator"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/translator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/translator.dir/build: translator
.PHONY : CMakeFiles/translator.dir/build

CMakeFiles/translator.dir/requires: CMakeFiles/translator.dir/main.cpp.o.requires
.PHONY : CMakeFiles/translator.dir/requires

CMakeFiles/translator.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/translator.dir/cmake_clean.cmake
.PHONY : CMakeFiles/translator.dir/clean

CMakeFiles/translator.dir/depend:
	cd /home/yanko/work/first_thousand_words/google_translate && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanko/work/first_thousand_words/google_translate /home/yanko/work/first_thousand_words/google_translate /home/yanko/work/first_thousand_words/google_translate /home/yanko/work/first_thousand_words/google_translate /home/yanko/work/first_thousand_words/google_translate/CMakeFiles/translator.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/translator.dir/depend

