cmake_minimum_required(VERSION 3.20)
project(CBCore LANGUAGES CXX)

file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
    src/*.h
)

add_library(ChengboStudio STATIC ${ENGINE_SRC})

set(CORE_INCLUDE_DIR ${CMAKE_SOURCE_DIR})
set(CORE_INCLUDE_DIR "${CORE_INCLUDE_DIR}" CACHE INTERNAL "STUDIO include path")

# Macro Definitions
target_compile_definitions(ChengboStudio
    PRIVATE
        _CONSOLE
	_CRT_SECURE_NO_WARNINGS
	)

set(ROOT_FILTER "ViewSource")  # root filter

foreach(FILE ${ENGINE_SRC})
    # obtain relative path
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${FILE}")
    get_filename_component(PATH "${REL_PATH}" PATH)
    string(REPLACE "/" "\\" GROUP "${PATH}")

    # prepend root filter name
    if (GROUP)
        set(FULL_GROUP "${ROOT_FILTER}\\${GROUP}")
    else()
        set(FULL_GROUP "${ROOT_FILTER}")
    endif()

    source_group("${FULL_GROUP}" FILES "${FILE}")
endforeach()

# include directories
target_include_directories(ChengboStudio
    PUBLIC
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src
	${CMAKE_SOURCE_DIR}/ChengboStudio/src/Core
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src/ChengboStudio
	    ${CMAKE_SOURCE_DIR}/ChengboStudio/src/ChengboStudio/
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor
	${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/glm
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/spdlog/include
	    ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/GLAD/include
	${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/imgui
)

# add libraries

add_subdirectory(vendor/imgui)

# link libraries
target_link_libraries(ChengboStudio
    PUBLIC
        dwmapi.lib
        glfw
        spdlog::spdlog
        OpenGL::GL
	imgui
)

#[[ precompiled headers
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
    target_precompile_headers(ChengboStudio PRIVATE src/pch.h)
endif()]]

# MSVC specific optimize
if(MSVC)
    target_compile_options(ChengboStudio PRIVATE /W4 /EHsc /utf-8)
endif()
