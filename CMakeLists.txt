## rEmbed CMakeLists.txt ##

# Version #
cmake_minimum_required (VERSION 3.0)

# Project #
project (rEmbed)

set (rEmbed_version_major 1)
set (rEmbed_version_minor 0)
set (CMAKE_C_STANDARD 11)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable (rEmbed ${CMAKE_SOURCE_DIR}/src/rEmbed.c)
target_include_directories (rEmbed PRIVATE ${CMAKE_SOURCE_DIR}/include)