cmake_minimum_required(VERSION 3.14)
project(assigment2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES main.cpp
        Vec2.h
        Vec2.cpp
        Components.h
        Entity.h
        EntityManager.cpp
        EntityManager.h
        Entity.cpp
        Game.cpp
        Game.h)
add_executable(assigment2 ${SOURCE_FILES}
        Vec2.h
        Vec2.cpp
        Components.h
        Entity.h
        EntityManager.cpp
        EntityManager.h
        Game.cpp
        Game.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(assigment2 sfml-system sfml-window sfml-graphics sfml-audio sfml-network)