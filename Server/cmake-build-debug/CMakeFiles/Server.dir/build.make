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
CMAKE_SOURCE_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Server.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Server.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Server.dir\flags.make

messageP.pb.cc: "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\protos\messageP.proto"
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating messageP.pb.cc, messageP.pb.h, messageP.grpc.pb.cc, messageP.grpc.pb.h"
	grpc\third_party\protobuf\protoc.exe --grpc_out "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Server/cmake-build-debug" --cpp_out "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Server/cmake-build-debug" -I "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/protos" --plugin=protoc-gen-grpc="C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/Server/cmake-build-debug/grpc/grpc_cpp_plugin.exe" "C:/Users/flori/Documents/Universita/Programmazione di sistema/Malnati/Progetto-Malnati/protos/messageP.proto"

messageP.pb.h: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.pb.h

messageP.grpc.pb.cc: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.grpc.pb.cc

messageP.grpc.pb.h: messageP.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate messageP.grpc.pb.h

CMakeFiles\Server.dir\messageP.pb.cc.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\messageP.pb.cc.obj: messageP.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Server.dir/messageP.pb.cc.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\messageP.pb.cc.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Server.dir\messageP.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/messageP.pb.cc.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\messageP.pb.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Server.dir\messageP.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/messageP.pb.cc.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\messageP.pb.cc.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.pb.cc"
<<

CMakeFiles\Server.dir\messageP.grpc.pb.cc.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\messageP.grpc.pb.cc.obj: messageP.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Server.dir/messageP.grpc.pb.cc.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\messageP.grpc.pb.cc.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.grpc.pb.cc"
<<

CMakeFiles\Server.dir\messageP.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/messageP.grpc.pb.cc.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\messageP.grpc.pb.cc.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.grpc.pb.cc"
<<

CMakeFiles\Server.dir\messageP.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/messageP.grpc.pb.cc.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\messageP.grpc.pb.cc.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\messageP.grpc.pb.cc"
<<

CMakeFiles\Server.dir\main.cpp.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Server.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\main.cpp.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\main.cpp"
<<

CMakeFiles\Server.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\main.cpp"
<<

CMakeFiles\Server.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\main.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\main.cpp"
<<

CMakeFiles\Server.dir\CharacterServiceImpl.cpp.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\CharacterServiceImpl.cpp.obj: ..\CharacterServiceImpl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Server.dir/CharacterServiceImpl.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\CharacterServiceImpl.cpp.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\CharacterServiceImpl.cpp"
<<

CMakeFiles\Server.dir\CharacterServiceImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/CharacterServiceImpl.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\CharacterServiceImpl.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\CharacterServiceImpl.cpp"
<<

CMakeFiles\Server.dir\CharacterServiceImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/CharacterServiceImpl.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\CharacterServiceImpl.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\CharacterServiceImpl.cpp"
<<

CMakeFiles\Server.dir\ConnectCallData.cpp.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\ConnectCallData.cpp.obj: ..\ConnectCallData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Server.dir/ConnectCallData.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\ConnectCallData.cpp.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\ConnectCallData.cpp"
<<

CMakeFiles\Server.dir\ConnectCallData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/ConnectCallData.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\ConnectCallData.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\ConnectCallData.cpp"
<<

CMakeFiles\Server.dir\ConnectCallData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/ConnectCallData.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\ConnectCallData.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\ConnectCallData.cpp"
<<

CMakeFiles\Server.dir\GetSymbolsCallData.cpp.obj: CMakeFiles\Server.dir\flags.make
CMakeFiles\Server.dir\GetSymbolsCallData.cpp.obj: ..\GetSymbolsCallData.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Server.dir/GetSymbolsCallData.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Server.dir\GetSymbolsCallData.cpp.obj /FdCMakeFiles\Server.dir\ /FS -c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\GetSymbolsCallData.cpp"
<<

CMakeFiles\Server.dir\GetSymbolsCallData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/GetSymbolsCallData.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Server.dir\GetSymbolsCallData.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\GetSymbolsCallData.cpp"
<<

CMakeFiles\Server.dir\GetSymbolsCallData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/GetSymbolsCallData.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Server.dir\GetSymbolsCallData.cpp.s /c "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\GetSymbolsCallData.cpp"
<<

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles\Server.dir\messageP.pb.cc.obj" \
"CMakeFiles\Server.dir\messageP.grpc.pb.cc.obj" \
"CMakeFiles\Server.dir\main.cpp.obj" \
"CMakeFiles\Server.dir\CharacterServiceImpl.cpp.obj" \
"CMakeFiles\Server.dir\ConnectCallData.cpp.obj" \
"CMakeFiles\Server.dir\GetSymbolsCallData.cpp.obj"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server.exe: CMakeFiles\Server.dir\messageP.pb.cc.obj
Server.exe: CMakeFiles\Server.dir\messageP.grpc.pb.cc.obj
Server.exe: CMakeFiles\Server.dir\main.cpp.obj
Server.exe: CMakeFiles\Server.dir\CharacterServiceImpl.cpp.obj
Server.exe: CMakeFiles\Server.dir\ConnectCallData.cpp.obj
Server.exe: CMakeFiles\Server.dir\GetSymbolsCallData.cpp.obj
Server.exe: CMakeFiles\Server.dir\build.make
Server.exe: grpc\grpc++.lib
Server.exe: grpc\third_party\protobuf\libprotobufd.lib
Server.exe: grpc\grpc.lib
Server.exe: grpc\third_party\boringssl\ssl\ssl.lib
Server.exe: grpc\third_party\boringssl\crypto\crypto.lib
Server.exe: grpc\third_party\zlib\zlibstaticd.lib
Server.exe: grpc\third_party\cares\cares\lib\cares.lib
Server.exe: grpc\address_sorting.lib
Server.exe: grpc\gpr.lib
Server.exe: CMakeFiles\Server.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Server.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Server.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Server.dir\objects1.rsp @<<
 /out:Server.exe /implib:Server.lib /pdb:"C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\Server.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console grpc\grpc++.lib grpc\third_party\protobuf\libprotobufd.lib grpc\grpc.lib grpc\third_party\boringssl\ssl\ssl.lib grpc\third_party\boringssl\crypto\crypto.lib grpc\third_party\zlib\zlibstaticd.lib grpc\third_party\cares\cares\lib\cares.lib grpc\address_sorting.lib wsock32.lib ws2_32.lib grpc\gpr.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Server.dir\build: Server.exe

.PHONY : CMakeFiles\Server.dir\build

CMakeFiles\Server.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Server.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Server.dir\clean

CMakeFiles\Server.dir\depend: messageP.pb.cc
CMakeFiles\Server.dir\depend: messageP.pb.h
CMakeFiles\Server.dir\depend: messageP.grpc.pb.cc
CMakeFiles\Server.dir\depend: messageP.grpc.pb.h
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug" "C:\Users\flori\Documents\Universita\Programmazione di sistema\Malnati\Progetto-Malnati\Server\cmake-build-debug\CMakeFiles\Server.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Server.dir\depend

