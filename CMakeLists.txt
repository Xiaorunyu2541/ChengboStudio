cmake_minimum_required(VERSION 3.20)
project(ChengboStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/obj)

# add cpm
include(CPM.cmake)

# add package dependencies
CPMAddPackage("gh:gabime/spdlog@1.15.3")
CPMAddPackage(
    NAME glfw
    GITHUB_REPOSITORY glfw/glfw
    GIT_TAG 7b6aead9fb88b3623e3b3725ebb42670cbe4c579
)
CPMAddPackage(
    NAME glm
    GITHUB_REPOSITORY g-truc/glm
    GIT_TAG 0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)
find_package(OpenGL REQUIRED)

# debug macro definiton
set(DEBUG_CONFIGS Debug RelWithDebInfo)

foreach(config ${DEBUG_CONFIGS})
    string(TOUPPER ${config} config_upper)
    add_compile_definitions($<$<CONFIG:${config}>:DEBUG_ASSERTS>)
endforeach()

# enable pch
include(CheckIncludeFileCXX)

# add projects
add_subdirectory(ChengboStudio)
add_subdirectory(Sandbox)

# configure visual studio generation
if(MSVC)
    add_compile_options(/utf-8)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()

# define platform specific macros 
if(WIN32)
    set(PLATFORM_MACRO "STUDIO_WINDOWS_PLATFORM")
elseif(APPLE)
    set(PLATFORM_MACRO "STUDIO_MAC_PLATFORM")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_MACRO "STUDIO_LINUX_PLATFORM")
else()
    message(WARNING "Unknown platform! only supports win mac and linux!")
endif()

target_compile_definitions(ChengboStudio PRIVATE ${PLATFORM_MACRO})
target_compile_definitions(Sandbox PRIVATE ${PLATFORM_MACRO})
