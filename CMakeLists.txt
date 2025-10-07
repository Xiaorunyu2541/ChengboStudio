cmake_minimum_required(VERSION 3.20)
project(ChengboStudio LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录（统一）
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/obj)

# 启用预编译头支持
include(CheckIncludeFileCXX)

# 添加子项目
add_subdirectory(ChengboStudio)
add_subdirectory(Sandbox)

if(MSVC)
    add_compile_options(/utf-8)
endif()
