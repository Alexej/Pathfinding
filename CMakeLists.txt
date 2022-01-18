cmake_policy(SET CMP0048 NEW)

project(Pathfinding VERSION 1.0)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
include_directories(include/Events)
include_directories(include/Core)
include_directories(include/Datastructures)
include_directories(include/Algorithms)
include_directories(include/Core)

add_subdirectory(dependencies)
add_subdirectory(src)

option(ENABLE_TESTING "Enable Test Builds" ON)

if(ENABLE_TESTING)
  message("Building Tests.")
  add_subdirectory(test)
endif()


# Lisa Lippincott