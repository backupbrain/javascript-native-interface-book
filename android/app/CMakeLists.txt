cmake_minimum_required(VERSION 3.28.0)
project(exampleJsiLibrary
        VERSION 1.0.0
        DESCRIPTION "Example JSI Library"
)

set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_CXX_STANDARD 14)
#set( CMAKE_CXX_COMPILER "/usr/bin/g++" )
#set( CMAKE_C_COMPILER "/usr/bin/gcc" )

message (${CMAKE_C_COMPILER})
message (${CMAKE_CXX_COMPILER})
message (${CMAKE_CXX_COMPILER_AR})
message (${CMAKE_CXX_COMPILER_RANLIB})

include_directories(
        ../../cpp
        ../../node_modules/react-native/React
        ../../node_modules/react-native/React/Base
        ../../node_modules/react-native/ReactCommon/jsi
)

add_library(exampleJsiLibrary
        SHARED
        ../../node_modules/react-native/ReactCommon/jsi/jsi/jsi.cpp
        ../../cpp/exampleJsiLibrary.cpp
        ../../cpp/exampleJsiLibrary.h
        ./cpp-adapter.cpp
)

#set_target_properties(
#        cpp PROPERTIES
#        CXX_STANDARD 17
#        CXX_EXTENSIONS OFF
#        POSITION_INDEPENDENT_CODE ON
#)

target_link_libraries(exampleJsiLibrary android)
