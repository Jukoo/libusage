cmake_minimum_required(VERSION 3.25) 

option(__synopis_status "Build with  synopsis"   ON) 
option(__description_init_status  "init by registering  the description" ON )  

if(BUILD_EXPLENO STREQUAL  2   OR   BUILD_EXPLENO STREQUAL 1)  
  project(example_${BUILD_EXPLENO})
  if (NOT EXISTS ${PROJECT_NAME}.c) 
    message(FATAL_ERROR  "File not Found ! ")
  else() 
    message(STATUS "Building   ${PROJECT_NAME}.c ...") 
  endif()


  if (__synopis_status)  
    message(STATUS "with synopsis")
    add_definitions(-DWITH_SYNOPSIS)
  endif() 

  if(__description_init_status) 
    message(STATUS "append description on init")   
    add_definitions(-DINIT_WITH_DESC) 
  endif()

endif() 


set(CMAKE_BUILD_TYPE Debug)

#link_directories(../build) 
#include_directories( ../include)  


add_executable(${PROJECT_NAME}  ${PROJECT_NAME}.c) 

target_link_libraries(${PROJECT_NAME} usage)
target_include_directories(${PROJECT_NAME} PUBLIC ../include) 
target_link_directories(${PROJECT_NAME} PUBLIC ../lib) 
