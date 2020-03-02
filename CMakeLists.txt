cmake_minimum_required(VERSION 3.1)
project(OCAW_STL CXX)

message("My Message")

# https://cmake.org/cmake/help/latest/variable/CMAKE_MODULE_PATH.html
# directories specifying a search path for CMake modules 
# to be loaded by the include() or find_package() commands 
# before checking the default modules that come with CMake. 
# By default it is empty, it is intended to be set by the project.
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/scripts/CMake")
include(CommonCppFlags)

file(GLOB OCAW_SOURCES "source/*.cpp")
add_library(OCAW_STL ${OCAW_SOURCES})

# TODO : Add Benchmark project
# if(EASTL_BUILD_BENCHMARK)
#    add_subdirectory(benchmark)
# endif()

# TODO : Add Test Project
#if(EASTL_BUILD_TESTS)
#    add_subdirectory(test)
#endif()

#-------------------------------------------------------------------------------------------
# Defines
#-------------------------------------------------------------------------------------------
# TODO : Should know what it is for
add_definitions(-D_CHAR16T)

# https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-3-c4996?view=vs-2019
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

# https://docs.microsoft.com/en-us/cpp/standard-library/scl-secure-no-warnings?view=vs-2019
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

# TODO : Should know what it is for
add_definitions(-DOCAW_STL_OPENSOURCE=1)

#-------------------------------------------------------------------------------------------
# Include dirs
#-------------------------------------------------------------------------------------------
# https://cmake.org/cmake/help/v3.0/command/target_include_directories.html
target_include_directories(OCAW_STL PUBLIC include)

#-------------------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------------------
# TODO : Should Know How to do this
# target_link_libraries(OCAW_STL OCAW_STL_BASE)