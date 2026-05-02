cmake_minimum_required(VERSION 3.22) #JUCE 8 requires CMake 3.22+

# On M1 Macs, uncomment to enable universal binaries
# set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64" CACHE STRING "")

if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif()

project(Surge VERSION 2.0.0)

set(CMAKE_CXX_STANDARD 17) #JUCE 8 requires 17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_COLOR_DIAGNOSTICS ON)

if (NOT DEFINED RNBO_EXPORT_DIR OR RNBO_EXPORT_DIR STREQUAL "")
  if (DEFINED ENV{RNBO_EXPORT_DIR} AND NOT "$ENV{RNBO_EXPORT_DIR}" STREQUAL "")
    file(TO_CMAKE_PATH "$ENV{RNBO_EXPORT_DIR}" RNBO_EXPORT_DIR)
  else()
    set(RNBO_EXPORT_DIR "${CMAKE_CURRENT_LIST_DIR}/export")
  endif()
endif()
set(RNBO_EXPORT_DIR "${RNBO_EXPORT_DIR}" CACHE FILEPATH "Path to the RNBO export directory")

if (NOT DEFINED RNBO_CPP_DIR OR RNBO_CPP_DIR STREQUAL "")
  if (DEFINED ENV{RNBO_CPP_DIR} AND NOT "$ENV{RNBO_CPP_DIR}" STREQUAL "")
    file(TO_CMAKE_PATH "$ENV{RNBO_CPP_DIR}" RNBO_CPP_DIR)
  else()
    set(RNBO_CPP_DIR "${RNBO_EXPORT_DIR}/rnbo")
  endif()
endif()
set(RNBO_CPP_DIR "${RNBO_CPP_DIR}" CACHE FILEPATH "Path to the RNBO C++ source directory")

if (NOT DEFINED RNBO_CLASS_FILE_NAME OR RNBO_CLASS_FILE_NAME STREQUAL "")
  if (DEFINED ENV{RNBO_CLASS_FILE_NAME} AND NOT "$ENV{RNBO_CLASS_FILE_NAME}" STREQUAL "")
    set(RNBO_CLASS_FILE_NAME "$ENV{RNBO_CLASS_FILE_NAME}")
  else()
    set(RNBO_CLASS_FILE_NAME "Surge.rnbopat.cpp")
  endif()
endif()
set(RNBO_CLASS_FILE_NAME "${RNBO_CLASS_FILE_NAME}" CACHE STRING "The name of the RNBO class file")
mark_as_advanced(RNBO_CLASS_FILE_NAME)

set(RNBO_CLASS_NAME "rnbomatic")
set(RNBO_CLASS_FILE "${RNBO_EXPORT_DIR}/${RNBO_CLASS_FILE_NAME}")
set(RNBO_DESCRIPTION_FILE "${RNBO_EXPORT_DIR}/description.json")
set(RNBO_PRESETS_FILE "${RNBO_EXPORT_DIR}/presets.json")
set(RNBO_BINARY_DATA_FILE "${RNBO_EXPORT_DIR}/${RNBO_CLASS_NAME}_binary.cpp")
set(RNBO_BINARY_DATA_STORAGE_NAME "${RNBO_CLASS_NAME}_binary")
set(PLUGIN_PARAM_DEFAULT_NOTIFY ON CACHE BOOL "Should parameter changes from inside your rnbo patch send output by default?")

message(STATUS "RNBO export directory: ${RNBO_EXPORT_DIR}")
message(STATUS "RNBO C++ directory: ${RNBO_CPP_DIR}")
message(STATUS "RNBO class file: ${RNBO_CLASS_FILE_NAME}")

if (NOT EXISTS "${RNBO_EXPORT_DIR}")
  message(FATAL_ERROR
    "RNBO export directory not found: ${RNBO_EXPORT_DIR}\n"
    "Commit the repo-local export/ directory, or set RNBO_EXPORT_DIR to a valid export folder.")
endif()

if (NOT EXISTS "${RNBO_CPP_DIR}/RNBO.h")
  message(FATAL_ERROR
    "RNBO runtime not found: ${RNBO_CPP_DIR}/RNBO.h\n"
    "Set RNBO_CPP_DIR explicitly or make sure RNBO_EXPORT_DIR points to a valid RNBO export.")
endif()

if (NOT EXISTS "${RNBO_CLASS_FILE}")
  message(FATAL_ERROR
    "RNBO class file not found: ${RNBO_CLASS_FILE}\n"
    "Set RNBO_CLASS_FILE_NAME or point RNBO_EXPORT_DIR at the correct export folder.")
endif()

if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/thirdparty/juce/CMakeLists.txt")
  message(FATAL_ERROR
    "JUCE submodule not found at ${CMAKE_CURRENT_LIST_DIR}/thirdparty/juce\n"
    "Clone with --recurse-submodules or run: git submodule update --init --recursive")
endif()

#write description header file if description.json exists, sets RNBO_INCLUDE_DESCRIPTION_FILE if the file exists
include(${RNBO_CPP_DIR}/cmake/RNBODescriptionHeader.cmake)
set(DESCRIPTION_INCLUDE_DIR ${CMAKE_BINARY_DIR}/include)
rnbo_write_description_header_if_exists(${RNBO_DESCRIPTION_FILE} ${DESCRIPTION_INCLUDE_DIR} ${RNBO_PRESETS_FILE})
include_directories(${DESCRIPTION_INCLUDE_DIR})

if (EXISTS ${RNBO_BINARY_DATA_FILE})
	add_definitions(-DRNBO_BINARY_DATA_STORAGE_NAME=${RNBO_BINARY_DATA_STORAGE_NAME})
endif()

# Include the JUCE submodule, needed for JUCE-based CMake definitions
add_subdirectory(
  ${CMAKE_CURRENT_LIST_DIR}/thirdparty/juce
  ${CMAKE_BINARY_DIR}/juce
  EXCLUDE_FROM_ALL #don't build examples etc, also don't install
)

# Or, instead, use Conan to get JUCE, should speed up clean builds
# include(${RNBO_CPP_DIR}/cmake/RNBOJuce.cmake)


# Optionally, enable ccache, should speed up builds
# include(${RNBO_CPP_DIR}/cmake/CCache.cmake)


# Comment out this line if you really want to emulate MIDI CC with Audio Parameters.
# See the discussion here: https://forums.steinberg.net/t/vst3-and-midi-cc-pitfall/201879/11
add_compile_definitions(JUCE_VST3_EMULATE_MIDI_CC_WITH_PARAMETERS=0)

# setup your application, you can remove this include if you don't want to build applications
include(${CMAKE_CURRENT_LIST_DIR}/App.cmake)

# setup your plugin(s), you can remove this include if you don't want to build plugins
include(${CMAKE_CURRENT_LIST_DIR}/Plugin.cmake)
