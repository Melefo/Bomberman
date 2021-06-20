CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(terrainGen)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow -Wshadow -Wno-missing-field-initializers)
endif()

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

HEADER_DIRECTORIES(INC)

file(GLOB_RECURSE SRC sources/*.cpp)

add_library(terrainGen
    STATIC
    ${SRC}
)

TARGET_LINK_LIBRARIES(terrainGen xmlGen encapsu)

target_include_directories(terrainGen PUBLIC ${raylib_SOURCE_DIR}/src ${INC})

if (UnitTests)
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

    TESTS_HEADER_DIRECTORIES(TEST_INC)

    file(GLOB_RECURSE TEST tests/*.cpp)

    add_executable(terrainGen_unit_tests
        ${SRC}
        ${TEST}
    )

    TARGET_LINK_LIBRARIES(terrainGen_unit_tests criterion xmlGen encapsu -lgcov)
    TARGET_COMPILE_OPTIONS(terrainGen_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

    target_include_directories(terrainGen_unit_tests PUBLIC ${raylib_SOURCE_DIR}/src ${INC} ${TEST_INC})
endif()