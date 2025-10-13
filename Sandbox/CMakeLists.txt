cmake_minimum_required(VERSION 3.20)
project(Sandbox LANGUAGES CXX)

file(GLOB_RECURSE SANDBOX_SRC
    src/*.cpp
    src/*.h
)

add_executable(Sandbox ${SANDBOX_SRC})

# macro definitions
target_compile_definitions(Sandbox
    PRIVATE
        STUDIO_APP
        _CONSOLE
)

# include directories
target_include_directories(Sandbox
    PRIVATE
        ${CMAKE_SOURCE_DIR}/ChengboStudio/src
        ${CMAKE_SOURCE_DIR}/ChengboStudio/vendor/spdlog/include
)

# link engine core
target_link_libraries(Sandbox PRIVATE ChengboStudio)

# automate packaging process
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:ChengboStudio>
        $<TARGET_FILE_DIR:Sandbox>
)

# MSVC compile options
if(MSVC)
    target_compile_options(Sandbox PRIVATE /W4 /EHsc /utf-8)
endif()

#[[ precompiled header
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
    target_precompile_headers(Sandbox PRIVATE pch.h)
endif()]]
