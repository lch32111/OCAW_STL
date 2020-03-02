#-------------------------------------------------------------------------------------------
# Compiler Flag Detection
#-------------------------------------------------------------------------------------------
# You can Include CMake Module to do easy things
# https://cmake.org/cmake/help/v3.0/module/CheckCXXCompilerFlag.html
# This module is for checking cxx compiler flag
include(CheckCXXCompilerFlag)

# http://man7.org/linux/man-pages/man1/g++.1.html
# You can check what the "-fchar8_t" is
# So this is for GCC
check_cxx_compiler_flag("-fchar8_t" OCAW_STL_HAS_FCHAR8T_FLAG)

# https://docs.microsoft.com/en-us/cpp/overview/cpp-conformance-improvements?view=vs-2019#char8_t
# You can check what the "/Zc"
# So this if for MSVC
check_cxx_compiler_flag("/Zc:char8_t" OCAW_STL_HAS_ZCCHAR8T_FLAG)

if(OCAW_STL_HAS_FCHAR8T_FLAG)
    set(OCAW_STL_CHAR8T_FLAG "-fchar8_t")
    set(OCAW_STL_NO_CHAR8T_FLAG "-fno-char8_t")
elseif(OCAW_STL_HAS_ZCCHAR8T_FLAG)
    set(OCAW_STL_CHAR8T_FLAG "/Zc:char8_t")
    set(OCAW_STL_NO_CHAR8T_FLAG "/Zc:char8_t-")
endif()

#-------------------------------------------------------------------------------------------
# Compiler Flags
#-------------------------------------------------------------------------------------------
# WIN32 / APPLE / CYGWIN / UNIX
# https://cmake.org/cmake/help/v3.0/variable/CMAKE_LANG_COMPILER_ID.html
# You can check the list of CMAKE_CXX_COMPILER_ID
if(UNIX AND "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    # https://software.intel.com/en-us/forums/intel-c-compiler/topic/296615
    # The -fasm-blocks option is provided on MAC for Microsoft style inline assembly.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fasm-blocks")
endif()

# NOT LESS == GREATER_OR_EQUAL; CMake doesn't support this out of the box.
# TODO : I should analyze this versioning for platform and compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    if(NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.2"))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.2" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.1")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "6.1" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.3")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    endif()
    # It seems Apple started changing version numbers after 3.1, going straight to 4.0 after 3.1.
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.3" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.1")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.1")
        message(FATAL_ERROR "Building with a Apple clang version less than 3.1 is not supported.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT CMAKE_CXX_SIMULATE_ID MATCHES "MSVC") # clang, but not clang-cl.
    # non-Apple clangs uses different versioning.
    if(NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0"))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.0.0" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.5.0" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.2")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.2" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.0")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "3.0")
        message(FATAL_ERROR "Building with a clang version less than 3.0 is not supported.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    if(NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0.0"))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif()
    if((CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.0.0") AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.2.0")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "5.2.0" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.1")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.8.1" AND (NOT (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.3")))
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "4.7.3")
        message(FATAL_ERROR "Building with a gcc version less than 4.7.3 is not supported.")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4 /permissive-")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
endif()
