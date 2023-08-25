cmake_minimum_required(VERSION 3.15)
project(BuildDLL)

option(BuildSC "BuildSC" ON)
option(BuildHS "BuildHS" OFF)
option(BuildT2SDK "BuildT2SDK" OFF)
option(BuildMain "BuildMain" ON)

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# set(CMAKE_GENERATOR_PLATFORM x86)
# set(CMAKE_C_FLAGS "-m32")
# set(CMAKE_CXX_FLAGS "-m32")


# Lib output path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
# Dll output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# Exe output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of CURRENT_LIST: ${CMAKE_CURRENT_LIST_DIR}")

# dbg-macro
# include(FetchContent)
# FetchContent_Declare(dbg_macro GIT_REPOSITORY https://github.com/sharkdp/dbg-macro)
# FetchContent_MakeAvailable(dbg_macro)
# find_path(DBG_MACRO_INCLUDE_DIRS "dbg.h")

# Include path
include_directories(${CMAKE_SOURCE_DIR}/Include)
message(STATUS "* Path of include: ${CMAKE_SOURCE_DIR}/Include")
# Link library path
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
# link_directories(${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of link: ${CMAKE_SOURCE_DIR}/lib")

# Build SC.dll
if(${BuildSC})
    add_library(SC
    SHARED
        SC.cpp 
        # ./Include/t2sdk_interface.h
        # ./Include/SC.h 
        # ./Include/dbg.h
        # ${DBG_MACRO_INCLUDE_DIRS}
    )
endif(${BuildSC})

# Build HS.dll HS.lib
if(${BuildHS})
    add_library(HS 
    SHARED 
        HS.cpp 
        ./Include/HS.h
        # ./Include/dbg.h
        # ${DBG_MACRO_INCLUDE_DIRS}
    )
    # add_library(HS_Static STATIC HS.cpp ./Include/HS.h)
endif(${BuildHS})

# Build t2sdk.lib
if(${BuildT2SDK})
    add_library(t2sdk
    STATIC
        # ./Include/t2sdk_interface.h
        ./Include/empty.cpp
    )    
endif(${BuildT2SDK})

# Build main.exe
if(${BuildMain})
    add_executable(main main.cpp)
    # target_link_directories(main PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bin/Debug/")
    target_link_libraries(main 
        # t2sdk.lib
        SC.lib
        # ${DBG_MACRO_INCLUDE_DIRS}
    )
endif(${BuildMain})

