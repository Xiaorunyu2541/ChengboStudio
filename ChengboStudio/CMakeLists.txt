cmake_minimum_required(VERSION 3.20)
project(CBCore LANGUAGES CXX)

file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
    src/*.h
)

add_library(ChengboStudio SHARED ${ENGINE_SRC})

# Macro Definitions
target_compile_definitions(ChengboStudio
    PRIVATE
        _CONSOLE
        _DEBUG
)

# include directories
target_include_directories(ChengboStudio
    PUBLIC
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src/ChengboStudio
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/spdlog/include
)

# link libraries
target_link_libraries(ChengboStudio
    PUBLIC
        dwmapi.lib
        glfw
        spdlog::spdlog
        OpenGL::GL
)

# precompiled headers
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
    target_precompile_headers(ChengboStudio PRIVATE src/pch.h)
endif()

# MSVC specific optimize
if(MSVC)
    target_compile_options(ChengboStudio PRIVATE /W4 /EHsc /utf-8)
endif()
