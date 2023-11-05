/** This is a simple illustration  of how to use libusage 
 *  ---It's not the only way to use it ---
 **/  

#include <stdlib.h>
#include <stdio.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <string.h> 

#include "usage.h"  
//see man page of  getopt 
struct option longopt [] ={
  {"help" , no_argument, 0  , 'h'} , 
  {"version" , no_argument , 0   , 'v'}, 
   {"age" , required_argument ,  0 ,  'a'} , 
   {"life" , required_argument ,  0 ,  'l'} , 
   {"ispresent" , no_argument ,  0 ,  'I'} , 
};

char  *descriptions[] = {
  "this is just an illustration" , 
  "show this help", 
  "print version of the programme",
  "age" , 
  "life" ,
  "ispresent",
   EODL 
} ; 

int
main ( int __ac , char **__av ) 
{
 
  struct  __getopt_usage_t *  usage   = NULL ; 

  usage = init_with_desc(longopt ,GETOPT_SIZE(longopt) , descriptions ) ; 
  //usage = init_with_desc(longopt ,GETOPT_SIZE(longopt) , descriptions  ) ; 
  if( usage == NULL ) 
  {
     perror("usage init error") ; 
  }

  char *sopt = get_shortopt(usage) ; 
  
  printf("shortoption -> %s \n" , sopt) ; 
  show_usage_no_synopsis(usage , __av) ; 



  endof_getoptusage(usage) ; 
  
  return EXIT_SUCCESS; 
}
