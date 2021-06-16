CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(xmlGen)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

file(GLOB_RECURSE SRC sources/**/*.cpp)
file(GLOB_RECURSE TEST tests/**/*.cpp tests/*.cpp)

find_package(Boost REQUIRED)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow -Wshadow -Wno-missing-field-initializers)
endif()

add_library(xmlGen
    STATIC
    ${SRC}
)

add_executable(xmlGen_unit_tests
    ${SRC}
    ${TEST}
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

target_include_directories(xmlGen PUBLIC ${raylib_SOURCE_DIR}/src ${INC} ${Boost_INCLUDE_DIRS})
target_include_directories(xmlGen_unit_tests PUBLIC ${raylib_SOURCE_DIR}/src ${INC} ${Boost_INCLUDE_DIRS})

TARGET_LINK_LIBRARIES(xmlGen ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(xmlGen_unit_tests criterion -lgcov ${Boost_LIBRARIES})
TARGET_COMPILE_OPTIONS(xmlGen_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

