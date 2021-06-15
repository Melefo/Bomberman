CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(terrainGen)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

file(GLOB_RECURSE SRC sources/*.cpp)
file(GLOB_RECURSE TEST tests/*.cpp)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow -Wshadow -Wno-missing-field-initializers)
endif()

add_library(terrainGen
    STATIC
    ${SRC}
)

add_executable(terrainGen_unit_tests
    ${SRC}
    ${TEST}
)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list sources/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

MACRO(TESTS_HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list tests/*.hpp)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(INC)
TESTS_HEADER_DIRECTORIES(TEST_INC)

TARGET_LINK_LIBRARIES(terrainGen xmlGen)
TARGET_LINK_LIBRARIES(terrainGen_unit_tests criterion xmlGen -lgcov)
TARGET_COMPILE_OPTIONS(terrainGen_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

target_include_directories(terrainGen PUBLIC ${raylib_SOURCE_DIR}/src ${INC})
target_include_directories(terrainGen_unit_tests PUBLIC ${raylib_SOURCE_DIR}/src ${INC} ${TEST_INC})