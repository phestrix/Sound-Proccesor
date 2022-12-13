cmake_minimum_required(VERSION 3.8)

set(This LAB)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set (Headers
    command_line_parser.hpp
    config_parser.hpp
    converter.hpp
    helper.hpp
    interface.hpp
    parser.hpp
    template_factory.hpp
)

set (Sources
    command_line_parser.cpp
    config_parser.cpp
    converter.cpp
    helper.cpp
    interface.cpp
    parser.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${Sources})
