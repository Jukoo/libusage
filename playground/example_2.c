/** This is a simple illusatration of how to use libusage 
 *  ---It's not the only way to use it --- 
 *  @author Umar Ba, jUmarB@protonmail.com , OpenWire Studion .HomeLab
 *
 */ 

#include <stdlib.h> 
#include <stdio.h> 
#include <getopt.h> 
#include <unistd.h> 

#include "usage.h"


struct option longopt[] ={
  {"help" , no_argument, 0  , 'h'} ,
  {"version" , no_argument , 0   , 'v'},
  {"flag1" , required_argument ,  0 ,  'f'} ,
  {"flag2" , optional_argument ,  0 ,  'F'} ,
};

#ifdef WITH_SYNOPSIS
//! by default, the sysnopsis description must be in the first index of the list
char  *descriptions[] = {
  "little synopsis that tell what it supposed to do" ,
  "show this help",
  "print version of the programme",
  "description of flag 1" ,
  "descriptions of flag 2" ,
   EODL  //!  that mark the end  of  descriptions
} ;

#else
char  *descriptions[] = {
  "show this help",
  "print version of the programme",
  "description of flag 1" ,
  "descriptions of flag 2" ,
   EODL  //!  that mark the end  of  descriptions
} ;

#endif


/** 
 * interfacing  with the getopt_long function
 * NOTE: this interface will be fully integrated into libusage.
 *
 * this is just a small example ... you can go further
 */ 

int argparse(int ac , char *const* _av   , gopt_usage_t * usage ) 
{
  if (usage == NULL)return  -USAGE_GINFAIL ;

  char *shortopts =  usage_get_shortopt(usage) ;
  
  int  opt =0 ; 
  while ( (opt = getopt_long(ac, _av , shortopts , usage->opt,0)) != ~0 ) { 
    switch (opt){
      case 'h' :
        usage_with_synopsis(usage , _av) ;  
        break ; 
      case  'v' : 
        printf("version  1.0\n") ;
        break ; 
      case 'f': 
        printf("value of f %s \n" , optarg) ;  
        break ; 
      case 'F': 
        char *optional_value = usage_optional_argument_hdl(ac, _av  ,  "defaultValue_here!" /*set NULL if you want no default value*/) ;  
        printf("option value  %s \n" ,  optional_value) ; 

        break; 
      default : 
        usage_with_synopsis(usage , _av) ;  
        break ;  
    }
  } 
  return  0 ; 
}



int main (int __ac , char ** __av) 
{
  //That all you need  ... just 2 lines ... 
  gopt_usage_t * usage =  init_with_desc(longopt , GETOPT_SIZE(longopt) , descriptions)  ; 
  argparse(__ac ,__av , usage) ; 
   

  return EXIT_SUCCESS ; 
}
