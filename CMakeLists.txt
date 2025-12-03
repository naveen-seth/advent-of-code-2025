cmake_minimum_required(VERSION 4.1.2 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD d0edc3af-4c50-42ea-a356-e2862fe7a444)

project(advent_of_code_cpp LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_MODULE_STD ON)

include(FetchContent)

FetchContent_Declare(
  flux
  GIT_REPOSITORY https://github.com/naveen-seth/flux.git
  GIT_TAG main # Replace with a git commit id to fix a particular revision
)

set(FLUX_BUILD_MODULE
    ON
    CACHE BOOL "Build C++20 module (experimental)" FORCE)

FetchContent_MakeAvailable(flux)

add_library(aoc_utils)
target_sources(aoc_utils PUBLIC FILE_SET CXX_MODULES FILES
                                src/advent_of_code_utils.cppm)

add_executable(day1)
target_sources(day1 PRIVATE src/day1.cpp)
target_link_libraries(day1 PRIVATE aoc_utils flux::module)
