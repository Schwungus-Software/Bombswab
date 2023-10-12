cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

add_subdirectory(external/raylib)

project(BasharQuest)

add_executable(BasharQuest "src/main.cpp")

set_target_properties(BasharQuest PROPERTIES CXX_STANDARD 23
                                             CXX_STANDARD_REQUIRED ON)

target_include_directories(BasharQuest PRIVATE include "external/raylib/src")

target_link_libraries(BasharQuest raylib)
