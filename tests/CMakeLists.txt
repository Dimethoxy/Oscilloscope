#==============================================================================
# Oscilloscope Test Folder CMakeLists.txt file
#==============================================================================

cmake_minimum_required(VERSION 3.22)
project(Oscilloscope)
enable_testing()

add_executable(${PROJECT_NAME}
    RingBufferTest.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../src
        ${EXT_DIR}/juce/modules
        ${EXT_DIR}/googletest/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../build/src/OscilloscopePlugin_artefacts/JuceLibraryCode/
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        OscilloscopePlugin
        GTest::gtest_main
)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            _SILENCE_CXX23_ALIGEND_STORAGE_DEPRECATION_WARNING
    )
endif()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})