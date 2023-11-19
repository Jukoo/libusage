/** This is a simple illustration  of how to use libusage 
 *  ---It's not the only way to use it ---
 *  @author  : Umar Ba,jUmarB@protonmail.com  
 *  
 **/  

#include <stdlib.h>
#include <stdio.h> 
#include <getopt.h> 
#include <unistd.h> 
#include <string.h> 
#include <assert.h> 


#include "usage.h"  
//see man page of  getopt 

//! list of   options 
struct option longopt[] ={
  {"help" , no_argument, 0  , 'h'} , 
  {"version" , no_argument , 0   , 'v'}, 
  {"flag1" , required_argument ,  0 ,  'f'} , 
  {"flag2" , required_argument ,  0 ,  'F'} , 
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

int
main ( int __ac , char **__av ) 
{
   gopt_usage_t * usage  = _Nullable  ; 

   // ! you can choose to initialize use in one of two ways
   //-> with the list of descriptions
   //-> without description list
   //---|but later if you want to add the description
   //---|you'll need to use this function usage_register_description <see include/usage.h>.

#ifdef   USAGE_INIT_WITH_DESC  
   usage = usage_init_(longopt , GETOPT_SIZE(longopt) , descriptions) ; 
   //! or use macro -->  usage = init_with_desc (longopt , GETOPT_SIZE(option) , descriptions)  ; 
#else  
   //you can also separate the logic like this
   
   usage= usage_init(longopt , GETOPT_SIZE(longopt)) ;  /*equivalent to :  usage_init_(longopt , GETOPT_SIZE(longopt) , NULL)*/
   usage_register_descriptions(usage , descriptions) ; 
#endif 

  assert(usage != _Nullable ) ;  
  
  //! if you build with sysnopsis enable choose GETOPT_SYNOPSIS_ON otherwise GETOPT_SYNOPSIS_OFF 
  usage_show(usage , __av  ,GETOPT_SYNOPSIS_ON) ;
  
  //! here  are  a few  alternatives 
  // usage_with_synopsis :  equivalent to usage_show(  usage , __av, GETOPT_SYNOPSIS_ON)  
  // usage_no_synopsis   :  equivalent to usage_show(  usage, __av , GETOPT_SYNOPSIS_OFF )
  // ----^------------
  // |* /!\\ WARNING *|
  // -----------------
  // * you need to know what you really want to show
  // if you choose sysnopsis
  // the first index in the description list must be sysnopsis and the rest will be assigned to the options list respectively
  // if you choose no sysnopsis
  // Make sure that the option list and the description list are of the same length.

   
  
  return EXIT_SUCCESS; 
}
