cmake_minimum_required(VERSION 3.26.4)
project(find-eventual-safe-states VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.82.0 REQUIRED system filesystem)

add_executable(find-eventual-safe-states main.cpp)

target_link_libraries(find-eventual-safe-states PRIVATE Boost::headers Boost::system Boost::filesystem)

