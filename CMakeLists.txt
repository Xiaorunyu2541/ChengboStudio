cmake_minimum_required(VERSION 3.20)
project(ChengboStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/obj)

if(MSVC)
    add_compile_options(/utf-8)
endif()

# add cpm PS: idk why but i can't put it into that vendor folder it pops an error 
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

# debug/release macros
set(DEBUG_CONFIGS Debug RelWithDebInfo)
set(ALL_CONFIGURATIONS Debug Release MinSizeRel RelWithDebInfo)

foreach(config ${DEBUG_CONFIGS})
    add_compile_definitions($<$<CONFIG:${config}>:DEBUG_ASSERTS>)
    add_compile_definitions($<$<CONFIG:${config}>:_DEBUG>)
endforeach()

# add projects
add_subdirectory(ChengboStudio)
add_subdirectory(Sandbox)

# platform macro
if(WIN32)
    set(PLATFORM_MACRO "STUDIO_WINDOWS_PLATFORM")
elseif(APPLE)
    set(PLATFORM_MACRO "STUDIO_MAC_PLATFORM")
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_MACRO "STUDIO_LINUX_PLATFORM")
else()
    message(WARNING "Unknown platform! only supports win/mac/linux!")
endif()

# assign platform macro and CRT per target
    if(MSVC)
    foreach(target ChengboStudio Sandbox spdlog glfw)
	target_compile_definitions(${target} PRIVATE ${PLATFORM_MACRO})
        target_compile_options(${target} PRIVATE
            $<$<CONFIG:Debug>:/MDd>
            $<$<CONFIG:Release>:/MD>
            $<$<CONFIG:RelWithDebInfo>:/MDd>
            $<$<CONFIG:MinSizeRel>:/MD>
        )
    endforeach()
endif()

# set VS startup project
if(MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)
endif()

#Configure pch
target_precompile_headers(ChengboStudio PRIVATE <pch.h>)
#[[target_precompile_headers(Sandbox PRIVATE <pch.h>)]]
