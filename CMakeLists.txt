cmake_minimum_required(VERSION 3.15)
project(BuildDLL)

option(BuildSC "BuildSC" OFF)
option(BuildHS "BuildHS" OFF)
option(BuildT2SDK "BuildT2SDK" OFF)
option(BuildMain "BuildMain" ON)

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

# Link library path
include_directories(${CMAKE_SOURCE_DIR}/Include)
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
link_directories(${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of Include: ${CMAKE_SOURCE_DIR}/Include")

# Build SC.dll
if(${BuildSC})
    add_library(SC
    SHARED
        SC.cpp 
        ./Include/t2sdk_interface.h
        # ./Include/SC.h 
        # ./Include/dbg.h
        # ${DBG_MACRO_INCLUDE_DIRS}
    )
    # add_library(SC_Static 
    # STATIC 
    #     SC.cpp 
    #     ./Include/SC.h 
    #     ./Include/t2sdk_interface.h
    #     # ./Include/dbg.h
    #     # ${DBG_MACRO_INCLUDE_DIRS}
    # )
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
        ./Include/t2sdk_interface.h
        ./Include/empty.cpp
    )    
endif(${BuildT2SDK})


# Build main.exe
if(${BuildMain})
    add_executable(main main.cpp)
    # target_link_directories(main PRIVATE "${CMAKE_CURRENT_LIST_DIR}/bin/Debug/")
    target_link_libraries(main 
        SC.dll 
        ./Include/t2sdk_interface.h
        # ${DBG_MACRO_INCLUDE_DIRS}
    )
endif(${BuildMain})

