#==============================================================================
# Main CMakeLists.txt file for the Oscilloscope project
#==============================================================================

cmake_minimum_required(VERSION 3.22)
project(Oscilloscope VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)
include(cmake/get_cpm.cmake)

CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG juce8
    SOURCE_DIR ${EXT_DIR}/juce
)

CPMAddPackage(
    NAME DMT
    GITHUB_REPOSITORY Dimethoxy/DMT
    GIT_TAG main
    SOURCE_DIR ${EXT_DIR}/dmt
)

if(MSVC)
    add_compile_options(/Qspectre )#/Wall /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif() 

add_definitions(-D_SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING)

add_subdirectory(src)
