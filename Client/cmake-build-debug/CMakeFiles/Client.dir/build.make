# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Client.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Client.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Client.dir\flags.make

CMakeFiles\Client.dir\main.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\main.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\main.cpp"
<<

CMakeFiles\Client.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\main.cpp"
<<

CMakeFiles\Client.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\main.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\main.cpp"
<<

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles\Client.dir\main.cpp.obj"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client.exe: CMakeFiles\Client.dir\main.cpp.obj
Client.exe: CMakeFiles\Client.dir\build.make
Client.exe: CMakeFiles\Client.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Client.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Client.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Client.dir\objects1.rsp @<<
 /out:Client.exe /implib:Client.lib /pdb:"C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug\Client.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Client.dir\build: Client.exe

.PHONY : CMakeFiles\Client.dir\build

CMakeFiles\Client.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Client.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Client.dir\clean

CMakeFiles\Client.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-20189\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles\Client.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Client.dir\depend
