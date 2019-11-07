cmake_minimum_required(VERSION 3.5.1)
project(Client)

set(CMAKE_CXX_STANDARD 17)

# alternativa: settings -> build,execution,deployment -> cmake options = -DCMAKE_PREFIX_PATH=C:/Qt/5.12.5/msvc2017/lib/cmake
#set(CMAKE_PREFIX_PATH "C:/Qt/5.12.5/msvc2017/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-D_WIN32_WINNT=0x600 /EHs)

add_subdirectory(../third_party/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)

# After using add_subdirectory, we can now use the grpc targets directly from
# this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)

# needed to build boringssl with VS2017
set(_gRPC_C_CXX_FLAGS "${_gRPC_C_CXX_FLAGS} /wd4987 /wd4774 /wd4819 /wd4996 /wd4619")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${_gRPC_C_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${_gRPC_C_CXX_FLAGS}")

set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)

# Proto file
get_filename_component(hw_proto "../protos/messageP.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/messageP.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/messageP.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/messageP.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/messageP.grpc.pb.h")
add_custom_command(
        OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
        DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Sql)

# mantenere in ordine alfabetico per comodità
add_executable(Client main.cpp
        comunication/CharacterClient.cpp comunication/CharacterClient.h comunication/definitions.h comunication/Message.cpp comunication/Message.h comunication/MyCustomAuthenticator.cpp comunication/MyCustomAuthenticator.h comunication/SharedEditor.cpp comunication/SharedEditor.h comunication/Symbol.h comunication/Symbol.cpp
        condividi.h editor.h importa.h loginpage.h nuovo.h principale.h registrationpage.h splashscreen.h
        condividi.cpp editor.cpp importa.cpp loginpage.cpp nuovo.cpp principale.cpp registrationpage.cpp splashscreen.cpp
        condividi.ui editor.ui importa.ui loginpage.ui nuovo.ui principale.ui registrationpage.ui splashscreen.ui
        ${hw_proto_srcs}
        ${hw_grpc_srcs} )

#target_link_libraries(Client Qt5::Widgets Qt5::Sql Qt5::Core grpc++_unsecure ${_PROTOBUF_LIBPROTOBUF})
target_link_libraries(Client Qt5::Widgets Qt5::Sql Qt5::Core grpc++ ${_PROTOBUF_LIBPROTOBUF})

