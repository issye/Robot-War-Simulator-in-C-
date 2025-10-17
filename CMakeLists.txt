cmake_minimum_required(VERSION 3.10)
project(RobotWarSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(robot_simulator
        main.cpp
        RoboCop.cpp
        Terminator.cpp
        TerminatorRoboCop.cpp
        BlueThunder.cpp
        MadBot.cpp
        RoboTank.cpp
)