CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(engine)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../cmake/")

file(GLOB_RECURSE SRC sources/**/*.cpp)
file(GLOB_RECURSE TEST tests/**/*.cpp tests/*.cpp)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow)
endif()

add_library(engine
    STATIC
    ${SRC}
)

add_executable(engine_unit_tests
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

target_include_directories(engine PUBLIC ${raylib_SOURCE_DIR}/src ${INC})
target_include_directories(engine_unit_tests PUBLIC ${raylib_SOURCE_DIR}/src ${INC})

TARGET_LINK_LIBRARIES(engine encapsu ecs xmlGen ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(engine_unit_tests encapsu ecs ${Boost_LIBRARIES} criterion -lgcov)
TARGET_COMPILE_OPTIONS(engine_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)
