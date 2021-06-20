CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(luaBind)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../cmake/")

FIND_PACKAGE(Lua REQUIRED)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow)
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

add_library(luaBind
    STATIC
    ${SRC}
)

TARGET_LINK_LIBRARIES(luaBind ${LUA_LIBRARIES} encapsu)

target_include_directories(luaBind PUBLIC ${INC} ${LUA_INCLUDE_DIR})

if (UnitTests)
    file(GLOB_RECURSE TEST tests/**/*.cpp tests/*.cpp)

    add_executable(lua_unit_tests
        ${SRC}
        ${TEST}
    )

    TARGET_LINK_LIBRARIES(lua_unit_tests ${LUA_LIBRARIES} criterion -lgcov encapsu)
    TARGET_COMPILE_OPTIONS(lua_unit_tests PUBLIC -fprofile-arcs -ftest-coverage)

    target_include_directories(lua_unit_tests PUBLIC ${INC} ${LUA_INCLUDE_DIR})
endif()
