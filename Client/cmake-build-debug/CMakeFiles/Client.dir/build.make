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
CMAKE_SOURCE_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Client.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Client.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Client.dir\flags.make

messageP.pb.cc: "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\protos\messageP.proto"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating messageP.pb.cc, messageP.pb.h, messageP.grpc.pb.cc, messageP.grpc.pb.h"
	grpc\third_party\protobuf\protoc.exe --grpc_out "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Client/cmake-build-debug" --cpp_out "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Client/cmake-build-debug" -I "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/protos" --plugin=protoc-gen-grpc="C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Client/cmake-build-debug/grpc/grpc_cpp_plugin.exe" "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/protos/messageP.proto"

messageP.pb.h: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.pb.h

messageP.grpc.pb.cc: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.grpc.pb.cc

messageP.grpc.pb.h: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.grpc.pb.h

CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj: Client_autogen\mocs_compilation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\Client_autogen\mocs_compilation.cpp"
<<

CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\Client_autogen\mocs_compilation.cpp"
<<

CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/Client_autogen/mocs_compilation.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\Client_autogen\mocs_compilation.cpp"
<<

CMakeFiles\Client.dir\main.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Client.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\main.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\main.cpp"
<<

CMakeFiles\Client.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\main.cpp"
<<

CMakeFiles\Client.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\main.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\main.cpp"
<<

CMakeFiles\Client.dir\comunication\CharacterClient.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\comunication\CharacterClient.cpp.obj: ..\comunication\CharacterClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Client.dir/comunication/CharacterClient.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\comunication\CharacterClient.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\comunication\CharacterClient.cpp"
<<

CMakeFiles\Client.dir\comunication\CharacterClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/comunication/CharacterClient.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\comunication\CharacterClient.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\comunication\CharacterClient.cpp"
<<

CMakeFiles\Client.dir\comunication\CharacterClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/comunication/CharacterClient.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\comunication\CharacterClient.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\comunication\CharacterClient.cpp"
<<

CMakeFiles\Client.dir\qt\condividi.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\condividi.cpp.obj: ..\qt\condividi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Client.dir/qt/condividi.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\condividi.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\condividi.cpp"
<<

CMakeFiles\Client.dir\qt\condividi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/condividi.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\condividi.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\condividi.cpp"
<<

CMakeFiles\Client.dir\qt\condividi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/condividi.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\condividi.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\condividi.cpp"
<<

CMakeFiles\Client.dir\qt\editor.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\editor.cpp.obj: ..\qt\editor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Client.dir/qt/editor.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\editor.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\editor.cpp"
<<

CMakeFiles\Client.dir\qt\editor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/editor.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\editor.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\editor.cpp"
<<

CMakeFiles\Client.dir\qt\editor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/editor.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\editor.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\editor.cpp"
<<

CMakeFiles\Client.dir\qt\importa.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\importa.cpp.obj: ..\qt\importa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Client.dir/qt/importa.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\importa.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\importa.cpp"
<<

CMakeFiles\Client.dir\qt\importa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/importa.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\importa.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\importa.cpp"
<<

CMakeFiles\Client.dir\qt\importa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/importa.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\importa.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\importa.cpp"
<<

CMakeFiles\Client.dir\qt\loginpage.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\loginpage.cpp.obj: ..\qt\loginpage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Client.dir/qt/loginpage.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\loginpage.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\loginpage.cpp"
<<

CMakeFiles\Client.dir\qt\loginpage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/loginpage.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\loginpage.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\loginpage.cpp"
<<

CMakeFiles\Client.dir\qt\loginpage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/loginpage.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\loginpage.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\loginpage.cpp"
<<

CMakeFiles\Client.dir\qt\nuovo.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\nuovo.cpp.obj: ..\qt\nuovo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Client.dir/qt/nuovo.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\nuovo.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\nuovo.cpp"
<<

CMakeFiles\Client.dir\qt\nuovo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/nuovo.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\nuovo.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\nuovo.cpp"
<<

CMakeFiles\Client.dir\qt\nuovo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/nuovo.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\nuovo.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\nuovo.cpp"
<<

CMakeFiles\Client.dir\qt\principale.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\principale.cpp.obj: ..\qt\principale.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Client.dir/qt/principale.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\principale.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\principale.cpp"
<<

CMakeFiles\Client.dir\qt\principale.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/principale.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\principale.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\principale.cpp"
<<

CMakeFiles\Client.dir\qt\principale.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/principale.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\principale.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\principale.cpp"
<<

CMakeFiles\Client.dir\qt\registrationpage.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\registrationpage.cpp.obj: ..\qt\registrationpage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Client.dir/qt/registrationpage.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\registrationpage.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\registrationpage.cpp"
<<

CMakeFiles\Client.dir\qt\registrationpage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/registrationpage.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\registrationpage.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\registrationpage.cpp"
<<

CMakeFiles\Client.dir\qt\registrationpage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/registrationpage.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\registrationpage.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\registrationpage.cpp"
<<

CMakeFiles\Client.dir\qt\splashscreen.cpp.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\qt\splashscreen.cpp.obj: ..\qt\splashscreen.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Client.dir/qt/splashscreen.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\qt\splashscreen.cpp.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\splashscreen.cpp"
<<

CMakeFiles\Client.dir\qt\splashscreen.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/qt/splashscreen.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\qt\splashscreen.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\splashscreen.cpp"
<<

CMakeFiles\Client.dir\qt\splashscreen.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/qt/splashscreen.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\qt\splashscreen.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\qt\splashscreen.cpp"
<<

CMakeFiles\Client.dir\messageP.pb.cc.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\messageP.pb.cc.obj: messageP.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Client.dir/messageP.pb.cc.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\messageP.pb.cc.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Client.dir\messageP.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/messageP.pb.cc.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\messageP.pb.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Client.dir\messageP.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/messageP.pb.cc.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\messageP.pb.cc.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Client.dir\messageP.grpc.pb.cc.obj: CMakeFiles\Client.dir\flags.make
CMakeFiles\Client.dir\messageP.grpc.pb.cc.obj: messageP.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Client.dir/messageP.grpc.pb.cc.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Client.dir\messageP.grpc.pb.cc.obj /FdCMakeFiles\Client.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.grpc.pb.cc"
<<

CMakeFiles\Client.dir\messageP.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/messageP.grpc.pb.cc.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Client.dir\messageP.grpc.pb.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.grpc.pb.cc"
<<

CMakeFiles\Client.dir\messageP.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/messageP.grpc.pb.cc.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Client.dir\messageP.grpc.pb.cc.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\messageP.grpc.pb.cc"
<<

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj" \
"CMakeFiles\Client.dir\main.cpp.obj" \
"CMakeFiles\Client.dir\comunication\CharacterClient.cpp.obj" \
"CMakeFiles\Client.dir\qt\condividi.cpp.obj" \
"CMakeFiles\Client.dir\qt\editor.cpp.obj" \
"CMakeFiles\Client.dir\qt\importa.cpp.obj" \
"CMakeFiles\Client.dir\qt\loginpage.cpp.obj" \
"CMakeFiles\Client.dir\qt\nuovo.cpp.obj" \
"CMakeFiles\Client.dir\qt\principale.cpp.obj" \
"CMakeFiles\Client.dir\qt\registrationpage.cpp.obj" \
"CMakeFiles\Client.dir\qt\splashscreen.cpp.obj" \
"CMakeFiles\Client.dir\messageP.pb.cc.obj" \
"CMakeFiles\Client.dir\messageP.grpc.pb.cc.obj"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client.exe: CMakeFiles\Client.dir\Client_autogen\mocs_compilation.cpp.obj
Client.exe: CMakeFiles\Client.dir\main.cpp.obj
Client.exe: CMakeFiles\Client.dir\comunication\CharacterClient.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\condividi.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\editor.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\importa.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\loginpage.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\nuovo.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\principale.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\registrationpage.cpp.obj
Client.exe: CMakeFiles\Client.dir\qt\splashscreen.cpp.obj
Client.exe: CMakeFiles\Client.dir\messageP.pb.cc.obj
Client.exe: CMakeFiles\Client.dir\messageP.grpc.pb.cc.obj
Client.exe: CMakeFiles\Client.dir\build.make
Client.exe: C:\Qt\5.12.5\msvc2017\lib\Qt5Widgetsd.lib
Client.exe: C:\Qt\5.12.5\msvc2017\lib\Qt5Sqld.lib
Client.exe: grpc\grpc++_unsecure.lib
Client.exe: grpc\third_party\protobuf\libprotobufd.lib
Client.exe: C:\Qt\5.12.5\msvc2017\lib\Qt5Guid.lib
Client.exe: C:\Qt\5.12.5\msvc2017\lib\Qt5Cored.lib
Client.exe: grpc\grpc_unsecure.lib
Client.exe: grpc\gpr.lib
Client.exe: grpc\third_party\zlib\zlibstaticd.lib
Client.exe: grpc\third_party\cares\cares\lib\cares.lib
Client.exe: grpc\address_sorting.lib
Client.exe: CMakeFiles\Client.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Linking CXX executable Client.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Client.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Client.dir\objects1.rsp @<<
 /out:Client.exe /implib:Client.lib /pdb:"C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\Client.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console C:\Qt\5.12.5\msvc2017\lib\Qt5Widgetsd.lib C:\Qt\5.12.5\msvc2017\lib\Qt5Sqld.lib grpc\grpc++_unsecure.lib grpc\third_party\protobuf\libprotobufd.lib C:\Qt\5.12.5\msvc2017\lib\Qt5Guid.lib C:\Qt\5.12.5\msvc2017\lib\Qt5Cored.lib grpc\grpc_unsecure.lib grpc\gpr.lib grpc\third_party\zlib\zlibstaticd.lib grpc\third_party\cares\cares\lib\cares.lib grpc\address_sorting.lib wsock32.lib ws2_32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Client.dir\build: Client.exe

.PHONY : CMakeFiles\Client.dir\build

CMakeFiles\Client.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Client.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Client.dir\clean

CMakeFiles\Client.dir\depend: messageP.pb.cc
CMakeFiles\Client.dir\depend: messageP.pb.h
CMakeFiles\Client.dir\depend: messageP.grpc.pb.cc
CMakeFiles\Client.dir\depend: messageP.grpc.pb.h
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Client\cmake-build-debug\CMakeFiles\Client.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Client.dir\depend

