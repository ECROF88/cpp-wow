# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.29)
# Set the project name
project (hello_cmake)
# set(OpenCV_DIR "C:/Users/D1mo/Downloads/opencv/build/x64/vc16/lib")
# find_package(opencv REQUIRED)
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++23" COMPILER_SUPPORTS_CXX23)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)

# check results and add flag
if(COMPILER_SUPPORTS_CXX23)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++23")
elseif(COMPILER_SUPPORTS_CXX17)#
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()
# Add an executable
add_executable(hello_cmake main6.cpp)

# target_link_libraries(hello_cmake opencv)