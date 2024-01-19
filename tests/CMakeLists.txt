#==============================================================================
# Oscilloscope Test Folder CMakeLists.txt file
#==============================================================================

# Set the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.22)

# Set the project name and version
project(Oscilloscope VERSION ${PROJECT_VERSION})

add_executable(${PROJECT_NAME}_test
    RingBufferTest.cpp
)

target_include_directories(${PROJECT_NAME}_test
    PRIVATE
        ${GOOGLETEST_SOURCE_DIR}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${JUCE_SOURCE_DIR}/modules
)

target_link_libraries(${PROJECT_NAME}_test
    PRIVATE
        ${PROJECT_NAME}
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)