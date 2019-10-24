cmake_minimum_required(VERSION 3.5.1)
project(Client)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_WIN32_WINNT=0x600)

add_subdirectory(../third_party/grpc ${CMAKE_CURRENT_BINARY_DIR}/grpc EXCLUDE_FROM_ALL)

# After using add_subdirectory, we can now use the grpc targets directly from
# this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP_UNSECURE grpc++_unsecure)
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

find_package(Qt5Widgets REQUIRED)

add_executable(Client main.cpp comunication/CharacterClient.cpp comunication/CharacterClient.h
        ${hw_proto_srcs}
        ${hw_grpc_srcs})
target_link_libraries(Client Qt5::Widgets ${_GRPC_GRPCPP_UNSECURE} ${_PROTOBUF_LIBPROTOBUF})