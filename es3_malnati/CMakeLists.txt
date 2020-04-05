cmake_minimum_required(VERSION 3.5.1)
project(es3_malnati)

set(CMAKE_CXX_STANDARD 17)


add_executable(es3 main.cpp NetworkServer.cpp NetworkServer.h SharedEditor.cpp SharedEditor.h Message.cpp Message.h Symbol.cpp Symbol.h definitions.h)
