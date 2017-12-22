cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)
include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/hackallcode/hunter/archive/v0.19.170.1.tar.gz"
    SHA1 "64b918e50cf0dbc2d9d77a321a002c88ac186b54"
)
project(demo)
hunter_add_package(print)
hunter_add_package(Boost COMPONENTS program_options)
find_package(print)
find_package(Boost CONFIG REQUIRED program_options)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/sources/demo.cpp)
target_link_libraries(demo print)
target_link_libraries(demo Boost::program_options)
install(TARGETS demo RUNTIME DESTINATION bin)
