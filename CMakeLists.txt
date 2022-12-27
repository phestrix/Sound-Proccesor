cmake_minimum_required(VERSION 3.8)

set(This LAB)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(Sources 
wav/errors.cpp 
wav/reader.cpp 
wav/writer.cpp 
processor/processor.cpp 
errors/io_errors.cpp 
convertors/convertor_create.cpp 
convertors/convertor_errors.cpp 
convertors/mix.cpp
convertors/double.cpp 
convertors/mute.cpp 
cl/cl_parser.cpp 
cfg_parser/cfg_parser.cpp 
main.cpp 
)

set(Headers 
wav/errors.hpp 
wav/reader.hpp 
wav/writer.hpp
wav/types.hpp
processor/processor.hpp 
errors/io_errors.hpp 
convertors/convertor_create.hpp 
convertors/convertor_errors.hpp 
convertors/convertors_interface.hpp
convertors/mix.hpp
convertors/double.hpp
convertors/mute.hpp 
cl/cl_parser.hpp 
cfg_parser/cfg_parser.hpp 
)

add_executable(${PROJECT_NAME} ${Sources})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES})
