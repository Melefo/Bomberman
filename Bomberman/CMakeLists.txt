CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(bomberman)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow -Wshadow -Wno-missing-field-initializers)
endif()

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

file(GLOB_RECURSE SRC sources/**/*.cpp)

add_executable(bomberman
    ${SRC}
    sources/main.cpp
)

TARGET_LINK_LIBRARIES(bomberman encapsu ecs engine terrainGen)

target_include_directories(bomberman PUBLIC ${INC})

if (UnitTests)
    file(GLOB_RECURSE TEST tests/*.cpp)

    add_executable(bomberman_unit_tests
        ${SRC}
        ${TEST}
    )

    TARGET_LINK_LIBRARIES(bomberman_unit_tests criterion encapsu engine terrainGen -lgcov encapsu ecs)
    TARGET_COMPILE_OPTIONS(bomberman_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

    target_include_directories(bomberman_unit_tests PUBLIC ${INC})
endif()