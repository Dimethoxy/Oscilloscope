#==============================================================================
# Oscilloscope Source Folder CMakeLists.txt file
#==============================================================================

cmake_minimum_required(VERSION 3.22)
project(OscilloscopePlugin VERSION 0.1.0)

if (APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

juce_add_plugin(${PROJECT_NAME}
    PRODUCT_NAME "Oscilloscope"
    COMPANY_NAME "Dimethoxy"
    FORMATS VST3 Standalone  
    VST3_CATEGORIES "Fx" "Analyzer"                   
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    #COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE DMTX
    PLUGIN_CODE OSCP                 
    )                    

target_sources(${PROJECT_NAME}
    PRIVATE
        app/PluginEditor.cpp
        app/PluginProcessor.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/external/dmt
)

juce_add_binary_data(FontBinaryData
    SOURCES
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Thin.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-ExtraLight.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Light.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Regular.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Medium.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-SemiBold.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Bold.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-ExtraBold.ttf
    ${CMAKE_SOURCE_DIR}/fonts/poppins/Poppins-Black.ttf
    ${CMAKE_SOURCE_DIR}/fonts/sedgwick_ave_display/SedgwickAveDisplay-Regular.ttf
        
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_cryptography
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_opengl
        juce::juce_product_unlocking
    PUBLIC
        FontBinaryData
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_DISPLAY_SPLASH_SCREEN=0
        REPORT_JUCE_APP_USAGE=0)

juce_generate_juce_header(${PROJECT_NAME})
message("JUCE header file generated!")

if(MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
            _SILENCE_CXX23_ALIGEND_STORAGE_DEPRECATION_WARNING
    )
endif()

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        OS_IS_WINDOWS=$<BOOL:${WIN32}>
        OS_IS_DARWIN=$<BOOL:${APPLE}>
        OS_IS_LINUX=$<BOOL:${UNIX} AND NOT APPLE>
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/..)

clap_juce_extensions_plugin(TARGET ${PROJECT_NAME}
    CLAP_ID "com.dimethoxy.oscilloscope"
    CLAP_FEATURES audio-effect utility analyser oscilloscope)