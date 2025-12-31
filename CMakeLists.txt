cmake_minimum_required(VERSION 3.16)
project(QuadPhysicsSim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(QuadPhysicsSim
    src/main.cpp
    src/Math2D.cpp
    src/PhysicalPoint.cpp
    src/PhysicsWorld.cpp
    src/DistanceConstraint.cpp
    src/JointConstraint.cpp
    src/Genome.cpp
    src/Fitness.cpp
    src/Population.cpp
    src/Creature.cpp
    src/Render.cpp
)

target_include_directories(QuadPhysicsSim PRIVATE include)
target_link_libraries(QuadPhysicsSim sfml-graphics sfml-window sfml-system)
