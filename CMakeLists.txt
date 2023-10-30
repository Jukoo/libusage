cmake_minimum_required(VERSION  3.25)
project(usage  VERSION 1.0  DESCRIPTION "Simple library to build helper command dynamicly") 

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB_RECURSE  src  src/*) 
file(GLOB_RECURSE  hdr  include/*) 

add_library(${PROJECT_NAME}  SHARED  ${src}) 
target_include_directories(${PROJECT_NAME}  PRIVATE  include) 

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION  ${PROJECT_VERSION}) 
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MINOR}) 
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/usage.h) 
