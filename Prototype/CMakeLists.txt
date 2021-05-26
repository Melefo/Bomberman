CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(prototype)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB_RECURSE SRC sources/**/*.cpp)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow)
endif()

add_executable(prototype
    ${SRC}
    sources/main.cpp
)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list sources/**/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(INC)

TARGET_LINK_LIBRARIES(prototype encapsu ecs)

target_include_directories(prototype PRIVATE ${INC})