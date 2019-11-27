cmake_minimum_required(VERSION 3.5.1)
project(Server)

set(CMAKE_CXX_STANDARD 17)

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

# My Proto file
get_filename_component(hw_my_proto "../protos/messageP.proto" ABSOLUTE)
get_filename_component(hw_my_proto_path "${hw_my_proto}" PATH)

# Google Proto file
#get_filename_component(hw_google_proto "../third_party/grpc/third_party/protobuf/src" ABSOLUTE)
#get_filename_component(hw_google_proto_path "${hw_google_proto}" PATH)

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
        -I "${hw_my_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_my_proto}"
        DEPENDS "${hw_my_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")


add_executable(Server
        ${hw_proto_srcs}
        ${hw_grpc_srcs}
        main.cpp
        CallData.h
        CharacterServiceImpl.cpp CharacterServiceImpl.h
        GetFilesCallData.cpp GetFilesCallData.h
        GetSymbolsCallData.cpp GetSymbolsCallData.h
        InsertFileCallData.cpp InsertFileCallData.h
        InsertSymbolsCallData.cpp InsertSymbolsCallData.h
        LoginCallData.cpp LoginCallData.h
        LogoutCallData.cpp LogoutCallData.h
        MyServiceAuthProcessor.cpp MyServiceAuthProcessor.h
        RegisterCallData.cpp RegisterCallData.h
        shaeredImport.h)

#target_link_libraries(Server grpc++_unsecure ssl ${_PROTOBUF_LIBPROTOBUF})

target_link_libraries(Server grpc++ ${_PROTOBUF_LIBPROTOBUF})

