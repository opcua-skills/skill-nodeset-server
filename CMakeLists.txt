cmake_minimum_required(VERSION 3.2)
project(skill-nodeset-server)

# -------------
# Project setup
# -------------

# Debug
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER_CASE)
if(BUILD_TYPE_LOWER_CASE STREQUAL "debug")
    if("x${CMAKE_C_COMPILER_ID}" STREQUAL "xClang")
        # Add default sanitizer settings when using clang and Debug build.
        # This allows e.g. CLion to find memory locations for SegFaults
        message(STATUS "Clang Sanitizer enabled")
        set(SANITIZER_FLAGS "-g -fno-omit-frame-pointer -gline-tables-only -fsanitize=address -fsanitize-address-use-after-scope -fsanitize-coverage=trace-pc-guard,trace-cmp -fsanitize=leak -fsanitize=undefined")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
    endif()
endif()

find_package(open62541 1.1 REQUIRED COMPONENTS FullNamespace Events)

#enable_testing()

# -------------
# Your own config
# -------------

add_subdirectory(src)

