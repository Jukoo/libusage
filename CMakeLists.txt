cmake_minimum_required(VERSION  3.25)
project(usage  VERSION 1.0  DESCRIPTION "Simple library to build helper command dynamicly") 

set(libname  lib${PROJECT_NAME})  
string(ASCII 27  ${libname}) 

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

option(USAGE_AUTOFREE "Auto free  allocated memory"  ON)
option(USAGE_BN_CTLR   "Restrict the basename programme  in certain lenght" ON)  

if(USAGE_AUTOFREE)
  message(STATUS  "[${libname}] auto free enable")
  add_definitions(-DUSAGE_AUTO_DEALOCATE) 
endif() 

if(USAGE_BN_CTLR)  
  message(STATUS "[${libname}] Basename lenght Restriction enabled") 
  add_definitions(-DUSAGE_RESTRICT_BASENAME) 
endif() 


file(GLOB_RECURSE  src  src/*) 
file(GLOB_RECURSE  hdr  include/*) 

add_library(${PROJECT_NAME}  SHARED  ${src}) 
target_include_directories(${PROJECT_NAME}  PRIVATE  include) 

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION  ${PROJECT_VERSION}) 
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MINOR}) 
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/usage.h) 
