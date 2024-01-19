#==============================================================================
# Main CMakeLists.txt file for the Oscilloscope project
#==============================================================================

# Set the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.22)

# Set version number
set(PROJECT_VERSION "0.0.0")

# Print the version for verification
message("Project version: ${PROJECT_VERSION}")

#==============================================================================

# Set the project name
project(Oscilloscope LANGUAGES CXX VERSION ${PROJECT_VERSION})

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set the directory for external libraries
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Load the CPM.cmake module for downloading external libraries
include(cmake/get_cpm.cmake)

#==============================================================================

# Add the JUCE library
CPMAddPackage(
    NAME JUCE
    GITHUB_REPOSITORY juce-framework/JUCE
    GIT_TAG 7.0.9
    VERSION 7.0.9
    SOURCE_DIR ${EXT_DIR}/juce
)

# Add the GoogleTest library
CPMAddPackage(
    NAME GOOGLETEST
    GITHUB_REPOSITORY google/googletest
    GIT_TAG v1.14.0
    VERSION 1.14.0
    SOURCE_DIR ${EXT_DIR}/googletest
    OPTIONS
        "INSTALL_GTEST OFF"
        "gtest_force_shared_crt ON"
)

#==============================================================================

# Add the subdirectories
add_subdirectory(src)
add_subdirectory(Tests)

#==============================================================================

# Setup compiler settings
if(MSVC)
    # Set the warning level to 4 and treat warnings as errors
    add_compile_options(/Qspectre )#/Wall /WX)
else()
    # Set the warning level to 4 and treat warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#==============================================================================

# Enable testing
enable_testing()