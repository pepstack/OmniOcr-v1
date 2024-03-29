#ifndef __sd_domnode_xml_HEADER_H
#define __sd_domnode_xml_HEADER_H 1
#define __sd_domnode_xml_IN_HEADER 1

#define YY_REENTRANT 1
#define YY_BISON_BRIDGE 1
#ifndef YY_REENTRANT
#define yytext __sd_domnode_xml_text
#define yyleng __sd_domnode_xml_leng
#define yyin __sd_domnode_xml_in
#define yyout __sd_domnode_xml_out
#define yy_flex_debug __sd_domnode_xml__flex_debug
#endif
#define yy_create_buffer __sd_domnode_xml__create_buffer
#define yy_delete_buffer __sd_domnode_xml__delete_buffer
#define yy_scan_buffer __sd_domnode_xml__scan_buffer
#define yy_scan_string __sd_domnode_xml__scan_string
#define yy_scan_bytes __sd_domnode_xml__scan_bytes
#define yy_init_buffer __sd_domnode_xml__init_buffer
#define yy_flush_buffer __sd_domnode_xml__flush_buffer
#define yy_load_buffer_state __sd_domnode_xml__load_buffer_state
#define yy_switch_to_buffer __sd_domnode_xml__switch_to_buffer
#define yylex __sd_domnode_xml_lex
#define yyrestart __sd_domnode_xml_restart
#define yylex_init __sd_domnode_xml_lex_init
#define yylex_destroy __sd_domnode_xml_lex_destroy
#define yyget_debug __sd_domnode_xml_get_debug
#define yyset_debug __sd_domnode_xml_set_debug
#define yyget_extra __sd_domnode_xml_get_extra
#define yyset_extra __sd_domnode_xml_set_extra
#define yyget_in __sd_domnode_xml_get_in
#define yyset_in __sd_domnode_xml_set_in
#define yyget_out __sd_domnode_xml_get_out
#define yyset_out __sd_domnode_xml_set_out
#define yyget_leng __sd_domnode_xml_get_leng
#define yyget_text __sd_domnode_xml_get_text
#define yyget_lineno __sd_domnode_xml_get_lineno
#define yyset_lineno __sd_domnode_xml_set_lineno
#ifdef YY_BISON_BRIDGE
#define yyget_lval __sd_domnode_xml_get_lval
#define yyset_lval __sd_domnode_xml_set_lval
#define yyget_lloc __sd_domnode_xml_get_lloc
#define yyset_lloc __sd_domnode_xml_set_lloc
#endif
#define yyalloc __sd_domnode_xml_alloc
#define yyrealloc __sd_domnode_xml_realloc
#define yyfree __sd_domnode_xml_free

#line 50 "domnode-xml-scanner.h"
#define  YY_INT_ALIGNED short int


/* A lexical scanner generated by flex */

#define FLEX_SCANNER
#define YY_FLEX_MAJOR_VERSION 2
#define YY_FLEX_MINOR_VERSION 5
#define YY_FLEX_SUBMINOR_VERSION 27
#if YY_FLEX_SUBMINOR_VERSION > 0
#define FLEX_BETA
#endif

/* First, we deal with  platform-specific or compiler-specific issues. */

/* begin standard C headers. */
#include <stdio.h>
#include <string.h>
//#include <errno.h>
#include <stdlib.h>

/* end standard C headers. */

#include <xplatform/xplatform.h>

/* flex integer type definitions */

#ifndef FLEXINT_H
#define FLEXINT_H

/* C99 systems have <inttypes.h>. Non-C99 systems may or may not. */

#if defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
typedef int8_t flex_int8_t;
typedef uint8_t flex_uint8_t;
typedef int16_t flex_int16_t;
typedef uint16_t flex_uint16_t;
typedef int32_t flex_int32_t;
typedef uint32_t flex_uint32_t;
#else
typedef signed char flex_int8_t;
typedef short int flex_int16_t;
typedef int flex_int32_t;
typedef unsigned char flex_uint8_t; 
typedef unsigned short int flex_uint16_t;
typedef unsigned int flex_uint32_t;
#endif /* ! C99 */

/* Limits of integral types. */
#ifndef INT8_MIN
#define INT8_MIN               (-128)
#endif
#ifndef INT16_MIN
#define INT16_MIN              (-32767-1)
#endif
#ifndef INT32_MIN
#define INT32_MIN              (-2147483647-1)
#endif
#ifndef INT8_MAX
#define INT8_MAX               (127)
#endif
#ifndef INT16_MAX
#define INT16_MAX              (32767)
#endif
#ifndef INT32_MAX
#define INT32_MAX              (2147483647)
#endif
#ifndef UINT8_MAX
#define UINT8_MAX              (255U)
#endif
#ifndef UINT16_MAX
#define UINT16_MAX             (65535U)
#endif
#ifndef UINT32_MAX
#define UINT32_MAX             (4294967295U)
#endif


#endif /* ! FLEXINT_H */



#ifdef __cplusplus

/* C++ compilers don't understand traditional function definitions. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#undef YY_TRADITIONAL_FUNC_DEFS
#endif

/* The "const" storage-class-modifier is valid. */
#define YY_USE_CONST

#else	/* ! __cplusplus */

/* We're not in a C++ compiler, so by default,
   we generate C99 function defs, unless you explicitly ask
   for traditional defs by defining YY_TRADITIONAL_FUNC_DEFS */

#if __STDC__

#define YY_USE_CONST

#endif	/* __STDC__ */
#endif	/* ! __cplusplus */

#ifdef YY_USE_CONST
#define yyconst const
#else
#define yyconst
#endif

/* For compilers that can't handle prototypes.
 * e.g.,
 * The function prototype
 *    int foo(int x, char* y);
 *
 * ...should be written as
 *    int foo YY_PARAMS((int x, char* y));
 *
 * ...which could possibly generate
 *    int foo ();
 */
#ifdef YY_NO_PROTOS
#define YY_PARAMS(proto) ()
#else
#define YY_PARAMS(proto) proto
#endif


/* Returned upon end-of-file. */
#define YY_NULL 0

/* Promotes a possibly negative, possibly signed char to an unsigned
 * integer for use as an array index.  If the signed char is negative,
 * we want to instead treat it as an 8-bit unsigned char, hence the
 * double cast.
 */
#define YY_SC_TO_UI(c) ((unsigned int) (unsigned char) c)


/* An opaque pointer. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

/* For use wherever a Global is accessed or assigned. */
#define YY_G(var) (((struct yyguts_t*)yyscanner)->var)

/* For use in function prototypes to append the additional argument. */
#define YY_PROTO_LAST_ARG , yyscan_t yyscanner
#define YY_PROTO_ONLY_ARG    yyscan_t yyscanner

/* For use in function definitions to append the additional argument. */
#ifdef YY_TRADITIONAL_FUNC_DEFS
#define YY_DEF_LAST_ARG , yyscanner
#define YY_DEF_ONLY_ARG    yyscanner
#else
#define YY_DEF_LAST_ARG , yyscan_t yyscanner
#define YY_DEF_ONLY_ARG   yyscan_t yyscanner
#endif
#define YY_DECL_LAST_ARG yyscan_t yyscanner;

/* For use in function calls to pass the additional argument. */
#define YY_CALL_LAST_ARG  , yyscanner
#define YY_CALL_ONLY_ARG   yyscanner

/* For convenience, these vars (plus the bison vars far below)
   are macros in the reentrant scanner. */
#define yyin YY_G(yyin_r)
#define yyout YY_G(yyout_r)
#define yyextra YY_G(yyextra_r)
#define yyleng YY_G(yyleng_r)
#define yytext YY_G(yytext_r)
#define yylineno YY_G(yylineno_r)
#define yy_flex_debug YY_G(yy_flex_debug_r)

int yylex_init YY_PARAMS((yyscan_t* scanner));



/* For compilers that need traditional function definitions.
 * e.g.,
 * The function prototype taking 2 arguments
 *    int foo (int x, char* y)
 *
 * ...should be written as
 *    int foo YYFARGS2(int,x, char*,y)
 *
 * ...which could possibly generate
 *    int foo (x,y,yyscanner)
 *        int x;
 *        char * y;
 *        yyscan_t yyscanner;
 */
#ifdef YY_TRADITIONAL_FUNC_DEFS
/* Generate traditional function defs */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG) YY_DECL_LAST_ARG
#define YYFARGS1(t1,n1) (n1 YY_DEF_LAST_ARG) t1 n1; YY_DECL_LAST_ARG
#define YYFARGS2(t1,n1,t2,n2) (n1,n2 YY_DEF_LAST_ARG) t1 n1; t2 n2; YY_DECL_LAST_ARG
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (n1,n2,n3 YY_DEF_LAST_ARG) t1 n1; t2 n2; t3 n3; YY_DECL_LAST_ARG
#else
/* Generate C99 function defs. */
#define YYFARGS0(v) (YY_DEF_ONLY_ARG)
#define YYFARGS1(t1,n1) (t1 n1 YY_DEF_LAST_ARG)
#define YYFARGS2(t1,n1,t2,n2) (t1 n1,t2 n2 YY_DEF_LAST_ARG)
#define YYFARGS3(t1,n1,t2,n2,t3,n3) (t1 n1,t2 n2,t3 n3 YY_DEF_LAST_ARG)
#endif

/* Enter a start condition.  This macro really ought to take a parameter,
 * but we do it the disgusting crufty way forced on us by the ()-less
 * definition of BEGIN.
 */
#define BEGIN YY_G(yy_start) = 1 + 2 *

/* Translate the current start state into a value that can be later handed
 * to BEGIN to return to the state.  The YYSTATE alias is for lex
 * compatibility.
 */
#define YY_START ((YY_G(yy_start) - 1) / 2)
#define YYSTATE YY_START

/* Action number for EOF rule of a given start state. */
#define YY_STATE_EOF(state) (YY_END_OF_BUFFER + state + 1)

/* Special action meaning "start processing a new file". */
#define YY_NEW_FILE yyrestart( yyin YY_CALL_LAST_ARG )

#define YY_END_OF_BUFFER_CHAR 0

/* Size of default input buffer. */
#ifndef YY_BUF_SIZE
#define YY_BUF_SIZE 16384
#endif


#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif



#define EOB_ACT_CONTINUE_SCAN 0
#define EOB_ACT_END_OF_FILE 1
#define EOB_ACT_LAST_MATCH 2

#ifdef YY_USE_LINENO
/* Note: We specifically omit the test for yy_rule_can_match_eol because it requires
 *       access to the local variable yy_act. Since yyless() is a macro, it would break
 *       existing scanners that call yyless() from OUTSIDE yylex. 
 *       One obvious solution it to make yy_act a global. I tried that, and saw
 *       a 5% performance hit in a non-yylineno scanner, because yy_act is
 *       normally declared as a register variable-- so it's not worth it.
 */
#define  YY_LESS_LINENO(n) \
        do { \
			int yyl;\
			for ( yyl = n; yyl < yyleng; ++yyl )\
				if ( yytext[yyl] == '\n' )\
					--yylineno;\
        }while(0)
#else
#define YY_LESS_LINENO(n)
#endif

/* The funky do-while in the following #define is used to turn the definition
 * int a single C statement (which needs a semi-colon terminator).  This
 * avoids problems with code like:
 *
 * 	if ( condition_holds )
 *		yyless( 5 );
 *	else
 *		do_something_else();
 *
 * Prior to using the do-while the compiler would get upset at the
 * "else" because it interpreted the "if" statement as being all
 * done when it reached the ';' after the yyless() call.
 */

/* Return all but the first 'n' matched characters back to the input stream. */

#define yyless(n) \
	do \
		{ \
		/* Undo effects of setting up yytext. */ \
        int yyless_macro_arg = (n); \
        YY_LESS_LINENO(yyless_macro_arg);\
		*yy_cp = YY_G(yy_hold_char); \
		YY_RESTORE_YY_MORE_OFFSET \
		YY_G(yy_c_buf_p) = yy_cp = yy_bp + yyless_macro_arg - YY_MORE_ADJ; \
		YY_DO_BEFORE_ACTION; /* set up yytext again */ \
		} \
	while ( 0 )

#define unput(c) yyunput( c, YY_G(yytext_ptr) YY_CALL_LAST_ARG )

/* The following is because we cannot portably get our hands on size_t
 * (without autoconf's help, which isn't available because we want
 * flex-generated scanners to compile on their own).
 */

#ifndef YY_TYPEDEF_YY_SIZE_T
#define YY_TYPEDEF_YY_SIZE_T
typedef unsigned int yy_size_t;
#endif

#ifndef YY_STRUCT_YY_BUFFER_STATE
#define YY_STRUCT_YY_BUFFER_STATE
struct yy_buffer_state
	{
	FILE *yy_input_file;



	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

	/* Whether to try to fill the input buffer when we reach the
	 * end of it.
	 */
	int yy_fill_buffer;

	int yy_buffer_status;
#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
	 * shouldn't try reading from the input source any more.  We might
	 * still have a bunch of tokens to match, though, because of
	 * possible backing-up.
	 *
	 * When we actually see the EOF, we change the status to "new"
	 * (via yyrestart()), so that the user can continue scanning by
	 * just pointing yyin at a new input file.
	 */
#define YY_BUFFER_EOF_PENDING 2
	};
#endif /* !YY_STRUCT_YY_BUFFER_STATE */


/* We provide macros for accessing buffer states in case in the
 * future we want to put the buffer states in a more general
 * "scanner state".
 */
#define YY_CURRENT_BUFFER yy_current_buffer



void yyrestart YY_PARAMS(( FILE *input_file YY_PROTO_LAST_ARG ));


void yy_switch_to_buffer YY_PARAMS(( YY_BUFFER_STATE new_buffer YY_PROTO_LAST_ARG ));
void yy_load_buffer_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
YY_BUFFER_STATE yy_create_buffer YY_PARAMS(( FILE *file, int size YY_PROTO_LAST_ARG ));
void yy_delete_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));
void yy_init_buffer YY_PARAMS(( YY_BUFFER_STATE b, FILE *file YY_PROTO_LAST_ARG ));
void yy_flush_buffer YY_PARAMS(( YY_BUFFER_STATE b YY_PROTO_LAST_ARG ));

#define YY_FLUSH_BUFFER yy_flush_buffer( YY_G(yy_current_buffer) YY_CALL_LAST_ARG)

YY_BUFFER_STATE yy_scan_buffer YY_PARAMS(( char *base, yy_size_t size YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_string YY_PARAMS(( yyconst char *yy_str YY_PROTO_LAST_ARG ));
YY_BUFFER_STATE yy_scan_bytes YY_PARAMS(( yyconst char *bytes, int len YY_PROTO_LAST_ARG ));


void *yyalloc YY_PARAMS(( yy_size_t YY_PROTO_LAST_ARG ));
void *yyrealloc YY_PARAMS(( void *, yy_size_t YY_PROTO_LAST_ARG ));
void yyfree YY_PARAMS(( void * YY_PROTO_LAST_ARG ));

#define yy_new_buffer yy_create_buffer

#define yy_set_interactive(is_interactive) \
	{ \
	if ( ! YY_G(yy_current_buffer) ) \
		YY_G(yy_current_buffer) =    \
            yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_is_interactive = is_interactive; \
	}

#define yy_set_bol(at_bol) \
	{ \
	if ( ! YY_G(yy_current_buffer) ) \
		YY_G(yy_current_buffer) =    \
            yy_create_buffer( yyin, YY_BUF_SIZE YY_CALL_LAST_ARG); \
	YY_G(yy_current_buffer)->yy_at_bol = at_bol; \
	}

#define YY_AT_BOL() (YY_G(yy_current_buffer)->yy_at_bol)


#define yywrap(n) 1
#define YY_SKIP_YYWRAP
#define yytext_ptr yytext_r


/* Done after the current pattern has been matched and before the
 * corresponding action - sets up yytext.
 */
#define YY_DO_BEFORE_ACTION \
	YY_G(yytext_ptr) = yy_bp; \
	yyleng = (size_t) (yy_cp - yy_bp); \
	YY_G(yy_hold_char) = *yy_cp; \
	*yy_cp = '\0'; \
	YY_G(yy_c_buf_p) = yy_cp;


/* Special case for "unistd.h", since it is non-ANSI. We include it way
 * down here because we want the user's section 1 to have been scanned first.
 * The user has a chance to override it with an option.
 */
#ifndef YY_NO_UNISTD_H
#include <unistd.h>
#endif /* !YY_NO_UNISTD_H */

#ifndef YY_EXTRA_TYPE
#define YY_EXTRA_TYPE void *
#endif






/* Accessor methods to globals.
   These are made visible to non-reentrant scanners for convenience. */

#ifndef YY_NO_DESTROY
int yylex_destroy YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_DEBUG
int yyget_debug YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_DEBUG
void yyset_debug YY_PARAMS(( int debug_flag YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_EXTRA
YY_EXTRA_TYPE yyget_extra YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_EXTRA
void yyset_extra YY_PARAMS(( YY_EXTRA_TYPE user_defined YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_IN
FILE *yyget_in YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_IN
void yyset_in  YY_PARAMS(( FILE * in_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_OUT
FILE *yyget_out YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_OUT
void yyset_out  YY_PARAMS(( FILE * out_str YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LENG
int yyget_leng YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_TEXT
char *yyget_text YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_GET_LINENO
int yyget_lineno YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#ifndef YY_NO_SET_LINENO
void yyset_lineno YY_PARAMS(( int line_number YY_PROTO_LAST_ARG ));
#endif

#ifndef YY_NO_GET_LVAL
YYSTYPE * yyget_lval YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
void yyset_lval YY_PARAMS(( YYSTYPE * yylvalp YY_PROTO_LAST_ARG ));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YY_NO_GET_LLOC
   YYLTYPE *yyget_lloc YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_SET_LLOC
    void yyset_lloc YY_PARAMS(( YYLTYPE * yyllocp YY_PROTO_LAST_ARG ));
#endif
#endif /* YYLTYPE */

/* Macros after this point can all be overridden by user definitions in
 * section 1.
 */

#ifndef YY_SKIP_YYWRAP
#ifdef __cplusplus
extern "C" int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#else
extern int yywrap YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#endif


#ifndef yytext_ptr
static void yy_flex_strncpy YY_PARAMS(( char *, yyconst char *, int YY_PROTO_LAST_ARG));
#endif

#ifdef YY_NEED_STRLEN
static int yy_flex_strlen YY_PARAMS(( yyconst char * YY_PROTO_LAST_ARG));
#endif

#ifndef YY_NO_INPUT
#endif


#if YY_STACK_USED

#ifndef YY_NO_PUSH_STATE
static void yy_push_state YY_PARAMS(( int new_state YY_PROTO_LAST_ARG));
#endif
#ifndef YY_NO_POP_STATE
static void yy_pop_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif
#ifndef YY_NO_TOP_STATE
static int yy_top_state YY_PARAMS(( YY_PROTO_ONLY_ARG ));
#endif

#else
#define YY_NO_PUSH_STATE 1
#define YY_NO_POP_STATE 1
#define YY_NO_TOP_STATE 1
#endif

/* Amount of stuff to slurp up with each read. */
#ifndef YY_READ_BUF_SIZE
#define YY_READ_BUF_SIZE 8192
#endif

/* Copy whatever the last rule matched to the standard output. */

#ifndef ECHO
/* This used to be an fputs(), but since the string might contain NUL's,
 * we now use fwrite().
 */
#define ECHO (void) fwrite( yytext, yyleng, 1, yyout )
#endif

/* Gets input and stuffs it into "buf".  number of characters read, or YY_NULL,
 * is returned in "result".
 */
#ifndef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	errno=0; \
	while ( (result = read( fileno(yyin), (char *) buf, max_size )) < 0 ) \
	{ \
		if( errno != EINTR) \
		{ \
			YY_FATAL_ERROR( "input in flex scanner failed" ); \
			break; \
		} \
		errno=0; \
		clearerr(yyin); \
	}
\
#endif

/* No semi-colon after return; correct usage is to write "yyterminate();" -
 * we don't want an extra ';' after the "return" because that will cause
 * some compilers to complain about unreachable statements.
 */
#ifndef yyterminate
#define yyterminate() return YY_NULL
#endif

/* Number of entries by which start-condition stack grows. */
#ifndef YY_START_STACK_INCR
#define YY_START_STACK_INCR 25
#endif

/* Report a fatal error. */
#ifndef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) yy_fatal_error( msg YY_CALL_LAST_ARG)
#endif


/* Default declaration of generated scanner - a define so the user can
 * easily add parameters.
 */
#ifndef YY_DECL

/* If the bison pure parser is used, then bison will provide
   one or two additional arguments. */

#  if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp, YYLTYPE * yyllocp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS2(YYSTYPE *,yylvalp, YYLTYPE *,yyllocp)
#  else
#        define YY_LEX_PROTO YY_PARAMS((YYSTYPE * yylvalp YY_PROTO_LAST_ARG))
#        define YY_LEX_DECLARATION YYFARGS1(YYSTYPE *,yylvalp)
#  endif



extern int yylex YY_LEX_PROTO;

#define YY_DECL int yylex YY_LEX_DECLARATION
#endif


/* Code executed at the beginning of each rule, after yytext and yyleng
 * have been set up.
 */
#ifndef YY_USER_ACTION
#define YY_USER_ACTION
#endif

/* Code executed at the end of each rule. */
#ifndef YY_BREAK
#define YY_BREAK break;
#endif

#define YY_RULE_SETUP \
	YY_USER_ACTION



/* yy_get_next_buffer - try to read in a new buffer
 *
 * Returns a code representing an action:
 *	EOB_ACT_LAST_MATCH -
 *	EOB_ACT_CONTINUE_SCAN - continue scanning from current position
 *	EOB_ACT_END_OF_FILE - end of file
 */


/* yy_get_previous_state - get the state just before the EOB char was reached */

#line 135 "../../../src/sd/domnode-xml-scanner.l"
#line 719 "domnode-xml-scanner.h"
#ifdef YY_HEADER_EXPORT_START_CONDITIONS
/* Beware! Start conditions are not prefixed. */
#undef INITIAL
#define INITIAL 0
#define CONTENT 1
#endif /* YY_HEADER_EXPORT_START_CONDITIONS */

#ifndef YY_HEADER_NO_UNDEFS
/* Undefine all internal macros, etc., that do no belong in the header. */

#undef BEGIN
#undef ECHO
#undef EOB_ACT_CONTINUE_SCAN
#undef EOB_ACT_END_OF_FILE
#undef EOB_ACT_LAST_MATCH
#undef FLEX_SCANNER
#undef FLEX_STD
#undef REJECT
#undef YYLMAX
#undef YYSTATE
#undef YY_AT_BOL
#undef YY_BREAK
#undef YY_BUFFER_EOF_PENDING
#undef YY_BUFFER_NEW
#undef YY_BUFFER_NORMAL
#undef YY_BUF_SIZE
#undef YY_CALL_LAST_ARG
#undef YY_CALL_ONLY_ARG
#undef YY_CURRENT_BUFFER
#undef YY_DECL
#undef YY_DECL_LAST_ARG
#undef YY_DO_BEFORE_ACTION
#undef YY_END_OF_BUFFER
#undef YY_END_OF_BUFFER_CHAR
#undef YY_EXIT_FAILURE
#undef YY_EXTRA_TYPE
#undef YY_FATAL_ERROR
#undef YY_FLEX_DEFINED_ECHO
#undef YY_FLEX_LEX_COMPAT
#undef YY_FLEX_MAJOR_VERSION
#undef YY_FLEX_MINOR_VERSION
#undef YY_FLUSH_BUFFER
#undef YY_G
#undef YY_INPUT
#undef YY_INT_ALIGNED
#undef YY_INTERACTIVE
#undef YY_LAST_ARG
#undef YY_LEX_ARGS
#undef YY_MAIN
#undef YY_MORE_ADJ
#undef YY_NEED_STRLEN
#undef YY_NEW_FILE
#undef YY_NO_FLEX_ALLOC
#undef YY_NO_FLEX_REALLOC
#undef YY_NO_FLEX_FREE
#undef YY_NO_GET_DEBUG
#undef YY_NO_GET_EXTRA
#undef YY_NO_GET_IN
#undef YY_NO_GET_LENG
#undef YY_NO_GET_LINENO
#undef YY_NO_GET_LLOC
#undef YY_NO_GET_LVAL
#undef YY_NO_GET_OUT
#undef YY_NO_GET_TEXT
#undef YY_NO_INPUT
#undef YY_NO_POP_STATE
#undef YY_NO_PUSH_STATE
#undef YY_NO_SCAN_BUFFER
#undef YY_NO_SCAN_BYTES
#undef YY_NO_SCAN_STRING
#undef YY_NO_SET_DEBUG
#undef YY_NO_SET_EXTRA
#undef YY_NO_SET_IN
#undef YY_NO_SET_LINENO
#undef YY_NO_SET_LLOC
#undef YY_NO_SET_LVAL
#undef YY_NO_SET_OUT
#undef YY_NO_TOP_STATE
#undef YY_NO_UNISTD_H
#undef YY_NO_UNPUT
#undef YY_NULL
#undef YY_NUM_RULES
#undef YY_ONLY_ARG
#undef YY_PROTO
#undef YY_READ_BUF_SIZE
#undef YY_REENTRANT
#undef YY_BISON_BRIDGE
#undef YY_RESTORE_YY_MORE_OFFSET
#undef YY_RULE_SETUP
#undef YY_SC_TO_UI
#undef YY_SKIP_YYWRAP
#undef YY_STACK_USED
#undef YY_START
#undef YY_START_STACK_INCR
#undef YY_STATE_EOF
#undef YY_STDINIT
#undef YY_TEXT_IS_ARRAY
#undef YY_TRAILING_HEAD_MASK
#undef YY_TRAILING_MASK
#undef YY_USER_ACTION
#undef YY_USES_REJECT
#undef YY_USE_CONST
#undef YY_USE_LINENO
#undef YY_USE_PROTOS
#undef unput
#undef yy_create_buffer
#undef yy_delete_buffer
#undef yy_flex_debug
#undef yy_flush_buffer
#undef yy_init_buffer
#undef yy_load_buffer_state
#undef yy_new_buffer
#undef yy_scan_buffer
#undef yy_scan_bytes
#undef yy_scan_string
#undef yy_set_bol
#undef yy_set_interactive
#undef yy_switch_to_buffer
#undef yyconst
#undef yyextra
#undef yyget_debug
#undef yyset_debug
#undef yyget_extra
#undef yyget_in
#undef yyget_leng
#undef yyget_lineno
#undef yyget_lloc
#undef yyget_lval
#undef yyget_out
#undef yyget_text
#undef yyin
#undef yyleng
#undef yyless
#undef yylex
#undef yylex_destroy
#undef yylex_init
#undef yylineno
#undef yylloc
#undef yylval
#undef yymore
#undef yyout
#undef yyrestart
#undef yyset_extra
#undef yyset_in
#undef yyset_lineno
#undef yyset_lloc
#undef yyset_lval
#undef yyset_out
#undef yyterminate
#undef yytext
#undef yytext_ptr
#undef yywrap
#undef yyalloc
#undef yyrealloc
#undef yyfree
#undef YY_NEVER_INTERACTIVE
#undef YY_NO_UNPUT
#undef YY_TABLES_VERIFY
#endif /* !YY_HEADER_NO_UNDEFS */

#undef __sd_domnode_xml_IN_HEADER
#endif /* __sd_domnode_xml_HEADER_H */
