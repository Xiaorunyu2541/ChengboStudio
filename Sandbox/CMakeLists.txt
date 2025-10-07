cmake_minimum_required(VERSION 3.20)
project(Sandbox LANGUAGES CXX)

file(GLOB_RECURSE SANDBOX_SRC
    src/*.cpp
    src/*.h
)

add_executable(Sandbox ${SANDBOX_SRC})

# 宏定义
target_compile_definitions(Sandbox
    PRIVATE
        DEBUG_ASSERTS
        STUDIO_APP
        STUDIO_WINDOWS_PLATFORM
        _CONSOLE
        _DEBUG
)

# 包含目录
target_include_directories(Sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/spdlog/include
)

# 链接 ChengboStudio 动态库
target_link_libraries(Sandbox PRIVATE ChengboStudio)

# 自动复制 DLL 到 Sandbox 运行目录（Windows）
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ChengboStudio>
        $<TARGET_FILE_DIR:Sandbox>
)

# MSVC 编译选项
if(MSVC)
    target_compile_options(Sandbox PRIVATE /W4 /EHsc /utf-8)
endif()

# 预编译头（可选）
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
    target_precompile_headers(Sandbox PRIVATE pch.h)
endif()
