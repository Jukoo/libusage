/**  @file usage.h 
     @Copyright (C) 2023 Umar Ba jUmarB@protonmail.com  AT OpenWire Studio .Lab

     This program is free software: you can redistribute it and/or modify

     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     

     This file is not part of GNU C Library 
*/  

#if !defined  (GETOPT_USAGE_H) 
#define        GETOPT_USAGE_H 1 

#define  USAGE  

#include <bits/getopt_ext.h> 

#ifdef __cplusplus
extern "C"  {   
#endif 

#define   MXBUFF 0xff
#define   RBN_MXBUFF ( MXBUFF >> 4 )

#define  _nullable   ( (void *) (0UL << 1) )   
#define  __void0h  _nullable    
#define  _Nullable _nullable 

#ifdef  SHOWUPWUR  
  #define  __must_check  __attribute__((warn_unused_result)) 
#else 
  #define  __must_check 
#endif

#define  __noreturn   __attribute__((__noreturn__))
#define  __nonull     __attribute__((__nonnull__)) 
#define  __pure       __attribute__((__pure__))
#define  __nonullx(index) __attribute__((__nonnull__(index)))

#ifdef  USAGE_AUTO_DEALOCATE
/** ! when it define no need to call  dealocate procedure 
 *  ! **/
#define  __destroy  __attribute__((destructor))
#else 
#define  __destroy 
#endif 
#define  __ulog(__mesg ,  ... )  \
  fprintf(stdout  , __mesg , ##__VA_ARGS__) ;  

enum {
   GETOPT_SIZE ,  
#define  GETOPT_SIZE(__options_struct) \
  sizeof(__options_struct)/sizeof(__options_struct[0]) 

   GETOPT_DESC_SIZE  
#define  GETOPT_DESC_SIZE(__description_list)  \
   sizeof(__description_list)/1 
  
  //... 
} ;


#define _end_of_description_list_marker  "" 
#define EODL  _end_of_description_list_marker 

#define _end_of_description_list_marker_p  _Nullable 
#define EODL_P _end_of_description_list_marker_p  


/** Dealing with synopsis  just right after  the command usage : 
 *  e.g  
 *   command usage : 
 *      synopsis  <- 
 *    options : 
 **/
enum  {
  /*desable synopsis*/
  GETOPT_SYNOPSIS_OFF , 
#define GETOPT_SYNOPSIS_OFF GETOPT_SYNOPSIS_OFF 
  
  /*enable synopsis*/
  GETOPT_SYNOPSIS_ON, 
#define GETOPT_SYNOPSIS_ON GETOPT_SYNOPSIS_ON
} ;

#define  __condcheck_GETOPT_SYNOPSIS_ON(_x,_y)  _x <= _y 
#define  __condcheck_GETOPT_SYNOPSIS_OFF(_x,_y) _x < _y


#define __get_ccgsyn(__synopsis_attr , x ,y) __condcheck_##__synopsis_attr(x,y)  


/**General errors*/
enum {
  /** basename too long */ 
  BN2LONG = ~22 , 
  
  /** getoptusage init failure*/
  GINFAIL
  
}; 
   
typedef  struct  __getopt_usage_t  gopt_usage_t  ; 
struct __getopt_usage_t { 
  struct option *  opt ; 
  int opt_size  ; 
  char opt_desc[MXBUFF][MXBUFF] ;
  char synopsis[MXBUFF] ;
  char shopt[MXBUFF] ;
  
  //@TODO : make a function  that return cmpcheck_between_optndesc 
  //--- i should change the name 
  int  cmpcheck_between_optndesc ; 

} ;
/** @fn  struct __getopt_usage_t  * init (struct option *   , int size )   
 *  @brief initialize  getoptusage struct 
 *  @param   struct option * 
 *  @param   int size  :!NOTE: you'd better  user GETOPT_SIZE() macro  to get the size of  options
 *  @return  struct  __getopt_usage_t  *
 */ 
USAGE struct __getopt_usage_t* init( struct option * __opt , int size );

/** @fn  struct __getopt_usage_t * init_(struct option * , int size , char * const * dl)
 *  @brief like the init function above +  dump_desclist to feed  opt_desc 
 *  @param   struct option * 
 *  @param   int size  :!NOTE: you'd better  use GETOPT_SIZE() macro  to get the size of  options
 *  @param   char * const *  dl  when (void *) 0 or NULL the init function above is used by default   
 *  @return  struct  __getopt_usage_t  *
 */ 
USAGE struct __getopt_usage_t* init_( struct option * __opt , int size  ,char * const * __description_list ) ; 

/** good naming Macro shortcut*/
#define  init_no_desc    init 
#define  init_with_desc  init_ 

USAGE extern int  __pure usage_get_size_optionslist( int size  )  { 
  return size  ; 
}

void  __destroy usage_free(void) ; 

/**  @fn void dump_desclist ( struct __getopt_usage_t * , char *const *  )  
 *   @brief dump description list  in  getoptusage structure 
 *   @param  __getopt_usage_t * 
 *   @param  char * const *  
 */
void dump_desclist ( struct  __getopt_usage_t  * goptu  ,    char  * const *desclist ) ; 


USAGE char *  __nonull __must_check get_shortopt(struct  __getopt_usage_t * goptu) ;  


static int  usage_check  (struct __getopt_usage_t *  __goptu  ,  char  * const * __description_list)  ; 

/** @fn  show_usage (struct __getopt_usage_t *)  
 *  @brief print  description list dumped on gopt_usage_t 
 */ 
USAGE void __nonull show_usage (struct __getopt_usage_t *  __goptu ,  char * const *  __argv , int __synopsis_stat ) ; 

static char __nonull switch_condition (  int __synopsis_status ,  int * index   , int const refcount) ; 

USAGE void __nonull show_usage_with_synopsis( struct __getopt_usage_t * __goptu  , char *const * __argv) ; 
USAGE void __nonull show_usage_no_synopsis(struct __getopt_usage_t * __goptu, char *const * __argv);

#define show_usage_ws show_usage_with_synopsis  
#define show_usage_ns show_usage_no_synopsis 

//build  shortoption from strct option
//char *retrive_shortopt(struct __getopt_usage_t * __goptu)

/** @brief basename program  manipulation to prettyfy */ 
USAGE static char *  __must_check  root_basename (char  *const *  __argv ,char *__restrict__   __dumper)  ; 
USAGE static char *  __must_check  fds_basename (char *basename) ; 


#ifdef __cplusplus 
} 
#endif 

#endif /** GETOPT_USAGE_H  */
