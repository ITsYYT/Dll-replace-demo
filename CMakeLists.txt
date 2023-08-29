cmake_minimum_required(VERSION 3.15)
project(BuildDLL)

option(BuildSC "BuildSC" ON)
option(BuildHS "BuildHS" OFF)
option(BuildT2SDK "BuildT2SDK" OFF)
option(BuildMain "BuildMain" ON)

# Useless
# set(CMAKE_CXX_FLAGS "-D__FILENAME__='\"$(subst $(SOURCE_PREFIX)/,,$(abspath $<))\"'")

# Implemented only for MS-compatible tools on Windows.
# Enable this boolean property to automatically create \
# a module definition (.def) file with all global symbols \
# found in the input .obj files for a SHARED library \
# (or executable with ENABLE_EXPORTS) on Windows.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Useless
# set(CMAKE_GENERATOR_PLATFORM x86)
# set(CMAKE_C_FLAGS "-m32")
# set(CMAKE_CXX_FLAGS "-m32")

# Useless in Windows (Linux unknow)
# Change the __FILE__ macro variable from absolute path to relative path
# include (utils.cmake)
# add_definitions(-Wno-builtin-macro-redefined)


# Lib output path
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib)
# Dll output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
# Exe output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of CURRENT_LIST: ${CMAKE_CURRENT_LIST_DIR}")

# Include path
include_directories(${CMAKE_SOURCE_DIR}/Include)
message(STATUS "* Path of include: ${CMAKE_SOURCE_DIR}/Include")
# Link library path
link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)
link_directories(${CMAKE_CURRENT_LIST_DIR}/bin)
message(STATUS "* Path of link: ${CMAKE_SOURCE_DIR}/lib")

# Build SC.dll
if(${BuildSC})
    add_library(SC
    SHARED
        SC.cpp 
    )
endif(${BuildSC})

# Build HS.dll HS_Static.lib
if(${BuildHS})
    add_library(HS 
    SHARED 
        HS.cpp 
    )
endif(${BuildHS})

# Build t2sdk.lib
if(${BuildT2SDK})
    add_library(t2sdk
    STATIC
        ./Include/empty.cpp
    )    
endif(${BuildT2SDK})

# Build main.exe
if(${BuildMain})
    add_executable(main main.cpp)
    target_link_libraries(main 
        # t2sdk.dll
        SC.lib
    )
endif(${BuildMain})

