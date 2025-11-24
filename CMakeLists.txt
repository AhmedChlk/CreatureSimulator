cmake_minimum_required(VERSION 3.10)
project(CreatureSimulator)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

add_executable(CreatureSimulator
    src/main.cpp
    src/World.cpp
    src/Creature.cpp
    src/BodyPart.cpp
    src/Link.cpp
)

target_link_libraries(CreatureSimulator sfml-graphics sfml-window sfml-system)
