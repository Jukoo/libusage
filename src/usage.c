/**  @file getoptusage.h 
     @brief  build helper usage from getopt using options structure 

     @Copyright (C) 2023 Umar Ba jUmarB@protonmail.com   AT OpenWire Studio .HomeLab

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

struct __getopt_usage_t *goptu_pref = _nullable ;

struct  __getopt_usage_t *  usage_init ( struct  option *  opt   , int size  )  
{

  if ( opt ==  _nullable)  return  _nullable ;  
  
  struct __getopt_usage_t *  goptu = (struct __getopt_usage_t*) malloc(sizeof(*goptu)) ;  
  
  goptu->opt = opt ; 
  goptu->opt_size  =   size  ;
  explicit_bzero(goptu->synopsis,MXBUFF);  
  goptu_pref   = goptu ; 

  return goptu;  
}


struct __getopt_usage_t * usage_init_(struct option *  opt , int size ,  char * const *  desclist)  
{

   if (desclist == _nullable)  
     return usage_init(opt  , size) ; 


   struct __getopt_usage_t *  goptu = (struct __getopt_usage_t *) malloc(sizeof(*goptu)) ; 
   goptu->opt = opt ; 
   goptu->opt_size  =   size  ; 

   explicit_bzero(goptu->synopsis,MXBUFF);  

   usage_register_descriptions(goptu ,  desclist) ; 

   goptu_pref   = goptu ; 
   return goptu; 

    
}

void __destroy usage_autofree(void) 
{
   if(goptu_pref == _nullable )return  ; 
   
   free(goptu_pref) ;
}


static int usage_sync_matched ( struct __getopt_usage_t *  restrict  goptu , int  synopsis_stat  ) 
{  
  if (goptu->usage_sync != synopsis_stat ) {

     uwarn(USAGE_NO_SYNC) ;  
     return  USAGE_NO_SYNC;  
  }

  return  USAGE_SYNC ; 
}

void   usage_register_descriptions( struct  __getopt_usage_t  * goptu  ,    char  * const *desclist ) 
{
  int  desclist_index = 0 ;
  if ( desclist ==  _nullable ) return ; 

  goptu->usage_sync = usage_check(goptu,  desclist) ;

  while (switch_condition(goptu->usage_sync,&desclist_index ,  goptu->opt_size) ){ 

    memcpy (
        (goptu->opt_desc+desclist_index) , 
        desclist[desclist_index] ,
        strlen(desclist[desclist_index]))  ; 

    desclist_index++ ;
  }
  
  
}

static int usage_check (struct __getopt_usage_t  * gopt  , char * const *desclist) 
{
  int description_list_size  =   usage_get_sizeof_descriptions(desclist) ; 
 
  if(description_list_size == ~0)
    return description_list_size ; 
  
  return abs(gopt->opt_size -  description_list_size)  ; 

}


static int usage_get_sizeof_descriptions(char * const *  description_list)  
{ 
  static int index = 0 ; 
  
  if (description_list[index] == _nullable) {
    return  index  +(~0)  ;
  }

  index++ ;
  usage_get_sizeof_descriptions(description_list) ;  
}


char * usage_get_shortopt ( struct __getopt_usage_t * goptu )  
{
   if (goptu == _nullable) return  _nullable ; 
  
   explicit_bzero(goptu->shopt, MXBUFF);  
   
   int index  =0 ; 
   int j_index=0 ; 
  
   while ( index <=  goptu->opt_size ) {

     switch (goptu->opt[index].has_arg){

       case  no_argument :  
         memset((goptu->shopt+j_index) ,  goptu->opt[index].val , 1) ; 
         break ; 
        case required_argument :
         memset((goptu->shopt+j_index) ,  goptu->opt[index].val , 1) ;
         j_index++; 
         memset((goptu->shopt+j_index) ,  0x3a, 1) ;
         break ; 
       case optional_argument : 
         memset((goptu->shopt+j_index) , goptu->opt[index].val, 1) ;  
         goptu->shopt[++j_index] = 0x3a; 
         goptu->shopt[++j_index] = 0x3a; 
         break ; 
     }

     index++ ;
     j_index++; 
     
   } 

   return  goptu->shopt ; 
}


void
usage_show( struct __getopt_usage_t * goptu , char * const *  argv , int synopsis)  
{
   if (goptu == _nullable){

     uerr_c(USAGE_GINFAIL ,"nil <nothing to show>") ; 
   }
 
   char rbasename[RBN_MXBUFF] = {0} ;
   if ( argv !=  _nullable) {

     (void*) root_basename(argv ,  rbasename); 
#ifdef  basename 
     memcpy(rbasename , __xpg_basename(rbasename)  , strlen(rbasename)) ; 
#endif 

     fprintf(stdout , "%s Usage:\n" , rbasename ) ; 
   }
   
   int index  = 0 ;
   int index_options = 0 ; 
   
   if (synopsis == GETOPT_SYNOPSIS_ON ){

     memcpy(goptu->synopsis ,  goptu->opt_desc[index] , MXBUFF) ; 
     index++ ; 
     fprintf(stdout ,  "\t%s\n" ,  goptu->synopsis); 
     index_options =1  ;  
   }
   
   __ulog("%s\n", "Options :") ;
   while(switch_condition(synopsis,  &index , goptu->opt_size )){
     fprintf(stdout  , "::\t-%-1c, --%-2s\t" ,  goptu->opt[index - index_options].val ,  goptu->opt[index-index_options].name); 
      fprintf(stdout, ": %-10s\n", goptu->opt_desc[index]);
      index++ ;  
   }
    
   usage_sync_matched(goptu, synopsis) ;  
}

static  char switch_condition(int synopsis_status , int *index, const int refcount) 
{
   if (synopsis_status ==  GETOPT_SYNOPSIS_OFF) 
     return  __get_ccgsyn(GETOPT_SYNOPSIS_OFF ,  *index , refcount) ; 

   return __get_ccgsyn(GETOPT_SYNOPSIS_ON , *index , refcount) ; 
}


void usage_no_synopsis(struct __getopt_usage_t *  goptu  , char *const * argv)  
{
  usage_show(goptu , argv ,  GETOPT_SYNOPSIS_OFF) ; 
}

void usage_with_synopsis(struct __getopt_usage_t * goptu , char *const * argv ) 
{
  usage_show(goptu , argv , GETOPT_SYNOPSIS_ON) ; 
}

static char * __must_check  root_basename (char * const * argv ,  char  * restrict rb_dump ) 
{
  char *localbasname =(char *) (*argv+0) ; 
  
  fds_basename(localbasname) ;  
#ifdef USAGE_RESTRICT_BASENAME 
  if (strlen(localbasname) >  RBN_MXBUFF){
     uerr(USAGE_BN2LONG) ;  
  }

  memcpy(rb_dump , (localbasname) ,  RBN_MXBUFF) ; 
#else 
  memcpy(rb_dump , (localbasname) ,  strlen(localbasname)) ;  
#endif 
 
  return rb_dump ; 
  
}


static char * __must_check fds_basename  (  char *basename ) 
{
  char dot_start = 0x2e ;

   /** looking  for  './'*/
  if ( (*basename+0) ==dot_start  &&  (*basename+1) ==  dot_start++){

    return memcpy(basename ,   (basename+2) , strlen(basename)) ; 
  } 
  
  return  basename ; 
}
 
USAGE char * usage_optional_argument_hdl(int ac , char * const * av , void * _deflaut_value)  
{

  if (optarg  == _nullable   &&  ac >  optind  &&  av[optind][0] != '-') {
     optarg = av[optind++] ; 
  }else {  
    return (char*) _deflaut_value ;  
  } 

  return optarg ;  
}
