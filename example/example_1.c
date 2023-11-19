/** This is a simple illustration  of how to use libusage 
 *  ---It's not the only way to use it ---
 **/  

#include <stdlib.h>
#include <stdio.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h> 


#include "usage.h"  
//see man page of  getopt 


struct option longopt[] ={
  {"help" , no_argument, 0  , 'h'} , 
  {"version" , no_argument , 0   , 'v'}, 
  {"flag1" , required_argument ,  0 ,  'f'} , 
  {"flag2" , required_argument ,  0 ,  'F'} , 
};

#ifdef WITH_SYNOPSIS  
//! by default the sysnopsis description   should be at the first index of the list  
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

int
main ( int __ac , char **__av ) 
{
   gopt_usage_t * usage  = _Nullable  ; 
   //! you can choose to  init the usage in two ways 
   //->  with the description list  
   //->  without the description list  
   //---|but later if you want to add the description 
   //---|you will need to  use this functions  usage_register_description <see include/usage.h> 
    
#ifdef   USAGE_INIT_WITH_DESC  
   usage = usage_init_(longopt , GETOPT_SIZE(longopt) , descriptions) ; 
   //! or use macro -->  usage = init_with_desc (longopt , GETOPT_SIZE(option) , descriptions)  ; 
#else  
   usage= usage_init(longopt , GETOPT_SIZE(longopt)) ;  
   //! if you  want to register  the description list  later 
   //! you must register the description list  
   usage_register_descriptions(usage , descriptions) ; 
#endif 

  assert(usage != _Nullable ) ;  
  //! if you build with sysnopsis enable choose GETOPT_SYNOPSIS_ON otherwise GETOPT_SYNOPSIS_OFF 
  usage_show(usage , __av  ,GETOPT_SYNOPSIS_ON) ;
  //! here   some  alternatives 
  // usage_with_synopsis :  equivalent to usage_show(  usage , __av, GETOPT_SYNOPSIS_ON)  
  // usage_no_synopsis   :  equivalent to usage_show(  usage, __av , GETOPT_SYNOPSIS_OFF )
  // ----^------------
  // |* /!\\ WARNING *|
  // -----------------
  // * you should know what you really want  to show 
  // if   you choose with sysnopsis  
  // the first index of the description list should be the sysnopsis  and the rest ill be affected to  option list respectively 
  // when you choose no sysnopsis  
  // make sure the option list and description list are length matched  
   
   



  
  return EXIT_SUCCESS; 
}
