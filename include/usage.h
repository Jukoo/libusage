/**  @file usage.h 
     @Copyright (C) 2023 Umar Ba jUmarB@protonmail.com  AT OpenWire Studio .HomeLab

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

#include <bits/getopt_ext.h>
#include <bits/types.h>

#define  USAGE  

__BEGIN_DECLS  

/** 
 * !All  char array have size  of MXBUFF
 **/
#ifndef   USAGE_MXBUFF 
  #define   MXBUFF 0xff
#else  
  #define   MXBUFF USAGE_MXBUFF 
#endif 

/**
 * !Programme basename length control   
 **/
#ifdef USAGE_RESTRICT_BASENAME
  #define  RBN_MXBUFF 0x14
#else  
  #define  RBN_MXBUFF MXBUFF 
#endif 

/** 
 * ! null aliases 
 **/
#define  _nullable   ( (void *) (0UL << 1) )   
#define  __void0h  _nullable    
#define  _Nullable _nullable 

#ifdef  SHOWUPWUR  
  #if __has_attribute(warn_unused_result)  
    #define  __must_check  __attribute__((warn_unused_result)) 
  #else 
    #define  __must_check  
  #endif 

#else 
  #define  __must_check 
#endif


/**! GNU attributes */ 
#if __has_attribute(__noreturn__)
  #define  __noreturn   __attribute__((__noreturn__))
#else 
  #define  __noreturn 
#endif  

#if __has_attribute(__nonnull__) 
  #define  __nonull     __attribute__((__nonnull__)) 
  #define  __nonullx(index) __attribute__((__nonnull__(index)))
#else  
  #define  __nonull
  #define  __nonullx(index)  
#endif 


#if __has_attribute(__pure__) 
  #define  __pure       __attribute__((__pure__))
#else 
  #define __pure 
#endif 

/**  
 * Free  memory automaticly avoiding  leaks by calling 
 * the function marked as   __destructor__ ( see  usage_free  procedure) 
 * *This macro  is enabled by default.* 
 * when  it's  desabled please  call  the function marked as __destroy  
 */ 
#ifdef  USAGE_AUTO_DEALOCATE
 
  #if __has_attribute(__destructor__) 
    #define  __destroy  __attribute__((destructor))
  #else  
    #define __destroy 
  #endif

#else  
  #define __destroy 

#endif  /*! USAGE_AUTO_DEALOCATE */


#define  __ulog(__mesg ,  ... )  \
  fprintf(stdout  , __mesg , ##__VA_ARGS__) ;  

enum usage_options_size_t {
   GETOPT_SIZE ,  
#define  GETOPT_SIZE(__options_struct) \
  sizeof(__options_struct)/sizeof(__options_struct[0]) 
  
} ;

/**
 * @brief these are a marker that used for  to delimit 
 * description list  
 */ 
enum USAGE_EODL { 
   EODL , 
#define  EODL  "" 
   EODL_P
#define  EODL_P  _nullable 
};  

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
  USAGE_BN2LONG = ~9 ,
#define mesg_USAGE_BN2LONG    "Usage basename too long :"
  USAGE_GINFAIL , 
#define  mesg_USAGE_GINFAIL   "Usage init error :" 
USAGE_NO_SYNC,
  #define  mesg_USAGE_NO_SYNC "Usage options and descriptions list are not synced :"
USAGE_SYNC= 0

};

#define  uerr(error) \
  errx(error , "%s\n" , mesg_##error); 

#define  uerr_c(error , static_mesg )  ({\
    char  _i[MXBUFF] = mesg_##error  ;\
    char *_s = static_mesg ; \
    strcat(_i , _s) ; \
    errx(error , "%s\n", _i);\
    }) 


#define  uwarn(error)\
  warn(mesg_##error); 

#define  uwarn_c(error , static_mesg )  ({\
    char  _i[MXBUFF] = mesg_##error  ;\
    char *_s = static_mesg ; \
    strcat(_i , _s) ; \
    warn("%s\n", _i);\
    }) 


   
typedef  struct  __getopt_usage_t  gopt_usage_t  ;

struct __getopt_usage_t { 
  struct option *  opt ; 
  int opt_size  ; 
  char opt_desc[MXBUFF][MXBUFF] ;
  char synopsis[MXBUFF] ;
  char shopt[MXBUFF] ;
  
  __u_char usage_sync; 

  struct __usage_option_hdl_t *optargs_node ; 
} ; 

//! TODO: each option  should have his own  data 
//        Like 
//          -> name 
//          -> generic function for his own logic
//          -> 
typedef struct __usage_option_hdl_t   usage_option_hdl_t ; 
struct __usage_option_hdl_t  { 
  char *option_name ; 
  //int position_index ; 
  //void *(*handler)()
  struct __usage_option_hdl_t * next ; 

};  

typedef enum __USAGE_OPTION_HDL_PROPERTY PROPERTY ;  
enum   __USAGE_OPTION_HDL_PROPERTY { 
  USAGE_OPTARG_SHOW_MODE, 
  USAGE_OPTARG_RELEASE_MODE 
} ; 


extern struct  __getopt_usage_t * goptu_pref ;  

/**
 */ 
USAGE  struct  __usage_option_hdl_t * usage_optarg_push( struct  __usage_option_hdl_t * opthdl_unit  , char const   *option_name)  ; 

USAGE  static  void  usage_optarg_operation_mode (struct __usage_option_hdl_t *  opthdl_unit_first_node , PROPERTY __mode ) __nonullx(1) ; 

USAGE  void  usage_optarg_show(struct __usage_option_hdl_t * opthdl) __nonull; 
USAGE  struct __usage_option_hdl_t * usage_optarg_delete(struct __usage_option_hdl_t *  opthdl) __nonull  ; 
 

/** @fn  struct __getopt_usage_t  * init (struct option *   , int size )   
 *  @brief initialize  getoptusage struct 
 *  @param   struct option * 
 *  @param   int size  :!NOTE  macro  to get the size of  options
 *  @return  struct  __getopt_usage_t  *
 */ 
USAGE struct __getopt_usage_t* usage_init( struct option * __opt , int size );

/** @fn  struct __getopt_usage_t * init_(struct option * , int size , char * const * dl)
 *  @brief like the init function above +  dump_desclist to feed  opt_desc 
 *  @param   struct option * 
 *  @param   int size  :!NOTE: you'd better  use GETOPT_SIZE() macro  to get the size of  options
 *  @param   char * const *  dl  when (void *) 0 or NULL the init function above is used by default   
 *  @return  struct  __getopt_usage_t  *
 */ 
USAGE struct __getopt_usage_t* usage_init_( struct option * __opt , int size  ,char * const * __description_list ) ; 

/**Macro shortcut*/
#define  init_no_desc    usage_init 
#define  init_with_desc  usage_init_ 

/** @fn  static int usage_get_sizeof_descriptions (char * const *  description_list)  
 *  @brief get size of description list  (array  of char) 
 *  @param char * const  * 
 *  @return  int (size of  description list)
 */ 

USAGE   static int usage_get_sizeof_descriptions(char* const  * __description_list)  ;

/** @fn  usage_free (void) 
 *  @brief  free alocated  memory used struct __getopt_usage_t at init function  
 *    When the  flag USAGE_AUTO_DEALOCATE  is set  no need  to call the function manualy 
 *    otherwise please call it to avoid memory leaks 
 */ 

USAGE  void  __destroy usage_free(void) ; 

/**  @fn void usage_register_descriptions ( struct __getopt_usage_t * , char *const *  )  
 *   @brief register  description list  in  getoptusage structure 
 *   @param  __getopt_usage_t * 
 *   @param  char * const *  
 */
USAGE  void  usage_register_descriptions( struct  __getopt_usage_t  * goptu  ,    char  * const * __description_list) ; 

/**  @fn  static int usage_sync_matched ( struct __getopt_usage_t * , int   )  
 *   @brief  check  if options list and description list   are the same length
 *      calculate  the distance between them ,When you use synopsis section or not  
 *   @param struct __getopt_usage_t  * 
 *   @param int 
 *   @return int 
 */ 
USAGE  static int   usage_sync_matched(struct __getopt_usage_t *  __restrict__ _goptu , int  __synopsis_stat) __nonullx(1) ; 


/** @fn usage_get_shortopt(struct  __getopt_usage_t  *) 
 *  @brief retrive  short option from  options list 
 *  @param   struct  __getopt_usage_t *  
 *  @return  char *    <short options  list> 
 */ 

USAGE char *  __nonull __must_check usage_get_shortopt(struct  __getopt_usage_t * goptu) ;  

/** @fn  usage_check(struct __getopt_usage_t * , char * const * )  
 *  @brief  check  the distance  between  options and description  
 *  @param struct __getopt_usage_t * 
 *  @param char * const * 
 *  @return int  
 */  

static int  usage_check  (struct __getopt_usage_t *  __goptu  ,  char  * const * __description_list)  ; 

/** @fn  show_usage (struct __getopt_usage_t * , char  *const * , int )  
 *  @brief print the usage 
 *  @param struct __getopt_usage_t  * 
 *  @param char * const *  __argv  ( to get the basename of the program ) 
 *  @param int synopsis_stat (if the usage show the synopsis  or not) 
 */ 
USAGE void __nonull usage_show (struct __getopt_usage_t *  __goptu ,  char * const *  __argv , int __synopsis_stat ) ; 

/** @fn switch_condition( int  , int * , int const  ) 
 *  @brief adapt the  condition  if  synopsis is used or not 
 *  @param   int 
 *  @param   int* 
 *  @param   int const
 *  @return  char
 *  @todo:   give a good name !
 */ 
static char __nonull switch_condition (  int __synopsis_status ,  int * index   , int const refcount) ; 


/** deferent  way to show  usage */
USAGE void __nonull usage_with_synopsis( struct __getopt_usage_t * __goptu  , char *const * __argv) ; 
USAGE void __nonull usage_no_synopsis(struct __getopt_usage_t * __goptu, char *const * __argv);
/** macro shortcut */
#define usage_ws  usage_with_synopsis  
#define usage_ns  usage_no_synopsis 


/** @brief basename program  manipulation to prettyfy */ 
USAGE static char *  __must_check  root_basename (char  *const *  __argv ,char *__restrict__   __dumper)  ; 

//! reformat basename  programme when it start  with './'
USAGE static char *  __must_check  fds_basename (char *basename) ; 


/** @fn usage_optional_argument_hdl(int ac  , char * const * av)  
 *  @brief handler  for optional_argument default behavior when an empty space
 *         between flag and optargs value is automatically set to NULL
 *          e.g. -e 12 : optargs (null)
 *          and you have to pass the argument like this -e12 and it's not very comfortable for the user 
 *          and doesn't respect program standars on GNU/Linux and that's why ...
 *         
 *  @param  int           - argument counter
 *  @param  char *const * - argument value  
 *  @return char * 
 *
 */ 
USAGE char *usage_optional_argument_hdl(int __ac , char * const* __av , void *  __default_value) ;  

__END_DECLS




#endif /** GETOPT_USAGE_H  */
