cmake_minimum_required(VERSION 3.20)
project(ChengboStudioLib LANGUAGES CXX)

file(GLOB_RECURSE ENGINE_SRC
    src/*.cpp
    src/*.h
)

add_library(ChengboStudio SHARED ${ENGINE_SRC})

# 宏定义
target_compile_definitions(ChengboStudio
    PRIVATE
        DEBUG_ASSERTS
        STUDIO_WINDOWS_PLATFORM
        _CONSOLE
        _DEBUG
)

# 包含目录
target_include_directories(ChengboStudio
    PUBLIC
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src/ChengboStudio
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/GLFW/include
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/spdlog/include
)

# 链接库
target_link_libraries(ChengboStudio
    PUBLIC
        dwmapi.lib
        glfw3_mt.lib
        opengl32.lib
)

# 预编译头（可选）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
    target_precompile_headers(ChengboStudio PRIVATE src/pch.h)
endif()

# MSVC 编译选项
if(MSVC)
    target_compile_options(ChengboStudio PRIVATE /W4 /EHsc /utf-8)
endif()
