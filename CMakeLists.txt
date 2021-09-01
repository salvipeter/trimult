cmake_minimum_required(VERSION 3.2)
project(TriMult)

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "-Wall -pedantic -std=c++17 -fPIC -Wno-reorder")
  set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -DDEBUG")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

  set(CMAKE_C_FLAGS "-Wall -pedantic -std=c99 -fPIC")
  set(CMAKE_C_FLAGS_DEBUG "-O0 -g -DDEBUG")
  set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(Boost REQUIRED)

add_subdirectory(tetgen)
add_subdirectory(trimult)

include_directories(tetgen trimult)
add_definitions(-DTETLIBRARY)
add_executable(trimult-standalone main.cpp)
target_link_libraries(trimult-standalone trimult tetgen)
