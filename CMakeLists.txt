# @file      CMakeLists.txt
# @brief     c-list library CMakeLists file
#
# MIT License
#
# Copyright joelguittet and c-list contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# CMake minimum version
cmake_minimum_required(VERSION 3.14)

# Project name
project(c-list)

# Project version
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/VERSION PROJECT_VER LIMIT_COUNT 1)
string(REPLACE "." ";" PROJECT_VER_LIST ${PROJECT_VER})
list(GET PROJECT_VER_LIST 0 PROJECT_VER_MAJOR)
list(GET PROJECT_VER_LIST 1 PROJECT_VER_MINOR)
list(GET PROJECT_VER_LIST 2 PROJECT_VER_PATCH)

# Use GNU installation directories
include(GNUInstallDirs)

# Import CHECK_C_COMPILER_FLAG
include(CheckCCompilerFlag)

# Additional flags
set(c_flags "${c_flags} -Os -ffunction-sections -Wall -fPIC")
set(linker_flags "${linker_flags} -Wl,-gc-sections")
CHECK_C_COMPILER_FLAG("fvisibility" "FLAG_SUPPORTED_FVISIBILITY")
if (FLAG_SUPPORTED_FVISIBILITY)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
endif()

# Definitions
add_definitions(-DLIST_EXPORT_SYMBOLS -DLIST_API_VISIBILITY)

# List of sources
file(GLOB_RECURSE src ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Creation of the library
add_library(list SHARED ${src})

# Link the library with the wanted libraries
find_package(Threads REQUIRED)
if (Threads_FOUND)
    if (CMAKE_USE_PTHREADS_INIT)
        target_link_libraries(list pthread)
    endif()
endif()

# Properties of the library
set_target_properties(list
    PROPERTIES
    SOVERSION "${PROJECT_VER_MAJOR}"
    VERSION "${PROJECT_VER_MAJOR}.${PROJECT_VER_MINOR}.${PROJECT_VER_PATCH}"
)

# Creation of the examples binaries
option(ENABLE_LIST_EXAMPLES "Enable building list examples" OFF)
if(ENABLE_LIST_EXAMPLES)
    add_executable(list_sort ${CMAKE_CURRENT_SOURCE_DIR}/examples/list_sort.c)
    target_link_libraries(list_sort list)
endif()

# Installation
set(CMAKE_INSTALL_FULL_LIBDIR lib)
set(CMAKE_INSTALL_FULL_BINDIR bin)
set(CMAKE_INSTALL_FULL_INCLUDEDIR include)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/list.h DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
install(TARGETS list
    ARCHIVE DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_BINDIR}"
    INCLUDES DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
)
if(ENABLE_LIST_EXAMPLES)
    install(TARGETS list_sort
        ARCHIVE DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_FULL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
    )
endif()
