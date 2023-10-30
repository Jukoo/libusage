cmake_minimum_required(VERSION 3.25) 
project(argparse)


link_directories(../build) 
include_directories( ../include)  


add_executable(${PROJECT_NAME}  illustration_main.c)
target_link_libraries(${PROJECT_NAME} usage)
