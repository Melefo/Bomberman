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

include_directories("sources/Behaviour/Components/PhysicsBody")
include_directories("sources/Behaviour/Components/Transform")
include_directories("sources/Behaviour/Components/Renderer")
include_directories("sources/Behaviour/Systems/PhysicsSystem")
include_directories("sources/Behaviour/Systems/RenderSystem")

add_executable(behaviourPrototype
  ${BEHAVIOUR_SRC}
  sources/Behaviour/main.cpp
)

TARGET_LINK_LIBRARIES(loopPrototype encapsu)
TARGET_LINK_LIBRARIES(inputPrototype encapsu)
TARGET_LINK_LIBRARIES(dragPrototype encapsu)
TARGET_LINK_LIBRARIES(coordinatorPrototype encapsu ecs)
TARGET_LINK_LIBRARIES(behaviourPrototype encapsu ecs)