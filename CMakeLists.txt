cmake_minimum_required(VERSION 3.16)
project(metronome C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Fetch and build raylib from source so no manual install is needed.
include(FetchContent)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE)
FetchContent_MakeAvailable(raylib)

add_executable(metronome main.c)
target_link_libraries(metronome PRIVATE raylib)

# Always land the binary in build/, including MSVC multi-config generators.
set_target_properties(metronome PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

# Assets ship next to the executable.
add_custom_command(TARGET metronome POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:metronome>/assets)
