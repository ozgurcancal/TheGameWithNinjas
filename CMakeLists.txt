cmake_minimum_required(VERSION 3.26)
project(TheGameWithNinjas)

set(CMAKE_CXX_STANDARD 20)

find_package(SQLite3 REQUIRED)

add_subdirectory(src)

target_link_libraries (TheGameWithNinjas SQLite::SQLite3)
