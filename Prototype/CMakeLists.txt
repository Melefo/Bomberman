CMAKE_MINIMUM_REQUIRED(VERSION 3.17)
PROJECT(prototype)
SET(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

file(GLOB_RECURSE BEHAVIOUR_SRC sources/Behaviour/**/*.cpp)

if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wshadow)
endif()

add_executable(loopPrototype
    sources/Loop/main.cpp
)
add_executable(inputPrototype
    sources/Input/main.cpp
)
add_executable(dragPrototype
  sources/Drag/main.cpp
)
add_executable(coordinatorPrototype
  sources/Coordinator/main.cpp
  sources/Coordinator/MoveSystem.cpp
  sources/Coordinator/MoveSystem.hpp
  sources/Coordinator/ObjectComponent.cpp
  sources/Coordinator/ObjectComponent.hpp
)

add_executable(shaderPrototype
  sources/Shaders/main.cpp
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

add_executable(behaviourPrototype
  ${BEHAVIOUR_SRC}
  sources/Behaviour/main.cpp
)

target_include_directories(behaviourPrototype PUBLIC ${raylib_SOURCE_DIR}/src ${INC})

TARGET_LINK_LIBRARIES(shaderPrototype encapsu ecs engine)
TARGET_LINK_LIBRARIES(loopPrototype encapsu)
TARGET_LINK_LIBRARIES(inputPrototype encapsu)
TARGET_LINK_LIBRARIES(dragPrototype encapsu)
TARGET_LINK_LIBRARIES(coordinatorPrototype encapsu ecs)
TARGET_LINK_LIBRARIES(behaviourPrototype encapsu ecs engine terrainGen)