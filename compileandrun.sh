#!/bin/bash   

set -o errexit 
set -o pipefail 

readonly external_tool=$1   

cmake --build build  &&  cmake --build ./playground/build 

printf "Running ...\n"
sleep 1 
if  [[ -z ${external_tool} ]] ; then 

    ./playground/build/example_2 
  else 
    test  -z `command  -v ${external_tool}`  &&  { 

    echo -e "tool not found  !\n"  
    return -1 
    }
    ${external_tool} ./playground/build/example_2 
    
fi 

#+ eg  : ./compileandrun.sh  valgrind 
