cmake_minimum_required(VERSION  3.25)
project(usage  VERSION 0.2.1  DESCRIPTION "Simple library to build helper command dynamicly") 

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

option(GENERATE_DOC "Generate documentation API"  OFF) 
if(${CMAKE_BUILD_TYPE} MATCHES  "[Rr]elease")  
  message(STATUS "${libname} build for release ${PROJECT_VERSION} !") 
  set(GENERATE_DOC ON  ) #CACHE BOOL "Generate documentation api for ${libname} version ${PROJECT_VERSION}")
endif() 

if(GENERATE_DOC)

  message(CHECK_START "Looking Doxygen build engine  ..")
  list(APPEND CMAKE_MESSAGE_INDENT "[DOXYGEN] ")
  find_package(Doxygen) 
  if(DOXYGEN_FOUND) 
    message(CHECK_PASS  "FOUND") 
    message(CHECK_START "Looking Doxyfile config ...") 
    set(Doxyconf ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    if(NOT EXISTS  ${Doxyconf})  
      message(CHECK_FAIL "NOT FOUND")  
      message(FATAL_ERROR  "no Doxyfile found  hint try  <doxywizard> or <doxygen> -g Doxyfile") 
    endif()
    message(CHECK_PASS  "FOUND")
    
    list(POP_BACK CMAKE_MESSAGE_INDENT)  
     
    add_custom_target(doxyrun  ALL 
      COMMAND   ${DOXYGEN_EXECUTABLE}  ${Doxyconf}
      WORKING_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}
      COMMENT "Build doxygen api documentation..."
      VERBATIM
    ) 

  else () 
    message(WARNING "not able to Generate  api documentation") 
  endif()
endif()  


file(GLOB_RECURSE  src  src/*) 
file(GLOB_RECURSE  hdr  include/*) 

add_library(${PROJECT_NAME}  SHARED  ${src}) 
target_include_directories(${PROJECT_NAME}  PRIVATE  include) 

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION  ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/usage.h) 
