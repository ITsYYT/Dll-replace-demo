cmake_minimum_required(VERSION 3.15)
project(BuildDLL)

option(BuildSC "BuildSC" ON)
option(BuildHS "BuildHS" ON)
option(BuildMain "BuildMain" ON)

# Lib out path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
# Dll out path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# Exe out path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of CURRENT_LIST: ${CMAKE_CURRENT_LIST_DIR}")

include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
message(STATUS "* Path of include: ${CMAKE_SOURCE_DIR}/include")

# Build SC.dll SC.lib
if(${BuildSC})
    add_library(SC SHARED SC.cpp ./include/SC.h)
    add_library(SC_Static STATIC SC.cpp ./include/SC.h)
endif(${BuildSC})

# Build HS.dll HS.lib
if(${BuildHS})
    add_library(HS SHARED HS.cpp ./include/HS.h)
    # add_library(HS_Static STATIC HS.cpp ./include/HS.h)
endif(${BuildHS})

# Build main.exe
if(${BuildMain})
    add_executable(main main.cpp )
    # target_link_directories(main PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bin/Debug/")
    target_link_libraries(main SC.dll)
endif(${BuildMain})

