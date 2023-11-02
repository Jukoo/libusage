/**  @file getoptusage.h 
     @brief  build helper usage from getopt using options structure 

     @Copyright (C) 2023 Umar Ba jUmarB@protonmail.com  , OpenWire Studio .Lab

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
*/


#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 
#include <err.h> 
#include <libgen.h>  
#include <getopt.h>

#include "usage.h" 

struct  __getopt_usage_t *  init ( struct  option *  opt   , int size  )  
{

  if ( opt ==  _nullable)  return  _nullable ;  
  
  struct __getopt_usage_t *  goptu = (struct __getopt_usage_t*) malloc(sizeof(*goptu)) ;  
  
  goptu->opt = opt ; 
  goptu->opt_size  =   size  ;
  explicit_bzero(goptu->synopsis,MXBUFF);  
  return goptu;  
}


struct __getopt_usage_t * init_(struct option *  opt , int size ,  char * const *  desclist)  
{

   if (desclist == _nullable)  
   { 
     return init(opt  , size) ; 
   } 

   struct __getopt_usage_t *  goptu = (struct __getopt_usage_t *) malloc(sizeof(*goptu)) ; 
   goptu->opt = opt ; 
   goptu->opt_size  =   size  ; 

   explicit_bzero(goptu->synopsis,MXBUFF);  

 dump_desclist(goptu ,  desclist) ; 

   return goptu; 

    
}

void dump_desclist ( struct  __getopt_usage_t  * goptu  ,    char  * const *desclist ) 
{
  int  desclist_index = 0 ;
  if ( desclist ==  _nullable ) return ; 

  // FIXME :TODO 
  // check if goptu->opt_size and desclist size  are same lenght 
  // if it's the case   use  < otherwise  <= 
  //
  int  syncmp  =  usage_check(goptu , desclist) ; 
  printf("sync comparator -> %i\n" , syncmp) ; 
  syncmp =  syncmp  ==0  ?  GETOPT_SYNOPSIS_OFF :  GETOPT_SYNOPSIS_ON ; 

  while (switch_condition(syncmp,&desclist_index ,  goptu->opt_size) )  
  {
    memcpy (
        (goptu->opt_desc+desclist_index) , 
        desclist[desclist_index] ,
        strlen(desclist[desclist_index]))  ; 

    desclist_index++ ;
  }
  
  
}

static int usage_check (struct __getopt_usage_t  * gopt  , char * const *desclist) 
{
  int description_list_size  =  0 ; 
  while (1)  
  { 
    if (strlen(desclist[description_list_size]) ==  0  ||  desclist == _nullable)break ; 
    description_list_size++ ; 
  }

  description_list_size-=1 ; 

  return abs(gopt->opt_size -  description_list_size)  ; 

}

char * get_shortopt ( struct __getopt_usage_t * goptu )  
{
   if (goptu == _nullable) return  _nullable ; 
  
   explicit_bzero(goptu->shopt, MXBUFF);  
   
   int index  =0 ; 
   int j_index=0 ; 
   while ( index <=  goptu->opt_size ) 
   {
     switch (goptu->opt[index].has_arg) 
     {
       case  no_argument :  
         memset((goptu->shopt+j_index) ,  goptu->opt[index].val , 1) ; 
         break ; 
        case required_argument :
         memset((goptu->shopt+j_index) ,  goptu->opt[index].val , 1) ;
         j_index++; 
         memset((goptu->shopt+j_index) ,  0x3a, 1) ;
         break ; 
       case optional_argument : 
         //! no supported yet 
         break ; 
     
     }
     index++ ;
     j_index++; 
     
   } 

   return  goptu->shopt ; 
}

void
show_usage( struct __getopt_usage_t * goptu , char * const *  argv , int synopsis)  
{
   if (goptu == _nullable)   
   {
     errx(GINFAIL ,"nil <nothing to show>") ; 
   }
 
   char rbasename[RBN_MXBUFF] = {0}  ;
   if ( argv !=  _nullable)  
   {
     (void*) root_basename(argv ,  rbasename); 
#ifdef  basename 
     memcpy(rbasename , __xpg_basename(rbasename)  , strlen(rbasename)) ; 
#endif 

     fprintf(stdout , "%s Usage:\n" , rbasename ) ; 
   }
   
   int index  = 0 ;
   int index_options = 0 ; 
   
   if (synopsis == GETOPT_SYNOPSIS_ON ) 
   {
     memcpy(goptu->synopsis ,  goptu->opt_desc[index] , MXBUFF) ; 
     index++ ; 
     fprintf(stdout ,  "\t%s\n" ,  goptu->synopsis); 
     index_options =1  ;  
   }
   
   __ulog("%s\n", "Options :") ;
   while(switch_condition(synopsis,  &index , goptu->opt_size ))  
   {
     fprintf(stdout  , "::\t-%-1c, --%-2s\t" ,  goptu->opt[index - index_options].val ,  goptu->opt[index-index_options].name); 
      fprintf(stdout, ": %-10s\n", goptu->opt_desc[index]);
      index++ ;  
   }
}


static  char switch_condition(int synopsis_status , int *index, const int refcount) 
{
   if (synopsis_status ==  GETOPT_SYNOPSIS_OFF) 
     return  __get_ccgsyn(GETOPT_SYNOPSIS_OFF ,  *index , refcount) ; 

  
   return __get_ccgsyn(GETOPT_SYNOPSIS_ON , *index , refcount) ; 
}


void show_usage_no_synopsis(struct __getopt_usage_t *  goptu  , char *const * argv)  
{
  show_usage(goptu , argv ,  GETOPT_SYNOPSIS_OFF) ; 
}

void show_usage_with_synopsis(struct __getopt_usage_t * goptu , char *const * argv ) 
{
  show_usage(goptu , argv , GETOPT_SYNOPSIS_ON) ; 
}

static char * __must_check  root_basename (char * const * argv ,  char  * restrict rb_dump ) 
{
  char *localbasname =(char *) (*argv+0) ; 
   
  if (strlen(localbasname) >  RBN_MXBUFF)    
  {
     errx(BN2LONG,  "root basename too long !"); 
  }

  fds_basename(localbasname) ;  
  memcpy(rb_dump , (localbasname) ,  RBN_MXBUFF) ; 
  return rb_dump ; 
  
}


static char * __must_check fds_basename  (  char *basename ) 
{
  char dot_start = 0x2e ;
   /** looking  for  './'*/
  if ( (*basename+0) ==dot_start  &&  (*basename+1) ==  dot_start++) 
  {
    return memcpy(basename ,   (basename+2) , strlen(basename)) ; 
  } 
  
  return  basename ; 
}
 
