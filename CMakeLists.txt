CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(bomberman)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

FIND_PACKAGE(raylib REQUIRED)

file(GLOB_RECURSE SRC sources/**/*.cpp)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow)
endif()

add_executable(bomberman
    ${SRC}
    sources/main.cpp
)

TARGET_LINK_LIBRARIES(bomberman raylib)
target_include_directories(bomberman PUBLIC ${raylib_SOURCE_DIR}/src sources/)