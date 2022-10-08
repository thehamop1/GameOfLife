cmake_minimum_required(VERSION 3.18)
project(RIOT_GAMES LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 23)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -m64 -g3 -O0 -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -m64 -O3 -fopenmp -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Wall -m64 -g3 -O3 -fopenmp -DNDEBUG -lprofiler")

include_directories(include)
add_subdirectory(src)

# add_subdirectory(googletest)
# option(BP_BUILD_TESTS "Build tests" ON)
# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BP_BUILD_TESTS)
#     include(GoogleTest)
#     enable_testing()
#     add_subdirectory(test)
# endif()