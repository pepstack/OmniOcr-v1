/**
 * log4c-wrapper.h
 *
 *   WITH_LOG4C, LOG4C_ENABLED, LOG_CATEGORY_NAME
 *     should be defined before including this file.
 */
#ifndef _LOG4C_WRAPPER_H_
#define _LOG4C_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif


#if (LOG4C_ENABLED == 1)
    #undef LOG4C_DISABLED

	#include <log4c-api.h>
	#include <stdarg.h>


    #ifndef LOG_CATEGORY_NAME_DEFAULT
		#define LOG_CATEGORY_NAME_DEFAULT  "root"
	#endif

	#ifdef LOG_CATEGORY_NAME
		#define LOG_CATEGORY_NAME_REAL  LOG_CATEGORY_NAME
	#else
		#define LOG_CATEGORY_NAME_REAL  LOG_CATEGORY_NAME_DEFAULT
	#endif


	static void log_proxy(int a_priority, const char* a_format, ...)
	{
		va_list va;
		va_start(va,a_format);
		log4c_category_vlog_name(LOG_CATEGORY_NAME_REAL,a_priority,a_format,va);
		va_end(va);
	}

    static void log_trace (int priority, const char *file, int line, const char *fun, const char *a_format, ...)
    {
        char new_fmt[1000];
        const char *head_fmt = "[ %s(%d) : %s ] ";
        va_list ap;
        int n;
        const char *p, *q;

        p = strrchr(file, '\\');
        q = strrchr(file, '/');

        if (p > q) {
            n = sprintf(new_fmt, head_fmt , ++p, line , fun);
        } else if (q > p) {
            n = sprintf(new_fmt, head_fmt , ++q, line , fun);
        } else {
            n = sprintf(new_fmt, head_fmt , file, line , fun);
        }

        strcat(new_fmt + n , a_format);
        va_start(ap , a_format);
        log4c_category_vlog_name(LOG_CATEGORY_NAME_REAL, priority, new_fmt, ap);
        va_end(ap);
    }


    #define LOG_INIT                log4c_init
    #define LOG_FINI                log4c_fini
    #define LOG_MSG	                log_proxy

    #if !defined(_MSC_VER)
        #if (LOG4C_USING_TRACE == 1)
            #define LOG_CRITICAL(fmt, args...)  log_trace(LOG4C_PRIORITY_CRIT, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
            #define LOG_ERROR(fmt, args...)     log_trace(LOG4C_PRIORITY_ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
            #define LOG_WARN(fmt, args...)      log_trace(LOG4C_PRIORITY_WARN, __FILE__, __LINE__, __FUNCTION__, fmt , ##args)
            #define LOG_INFO(fmt, args...)      log_trace(LOG4C_PRIORITY_INFO, __FILE__, __LINE__, __FUNCTION__, fmt , ##args)
            #define LOG_DEBUG(fmt, args...)     log_trace(LOG4C_PRIORITY_DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt , ##args)
            #define LOG_TRACE(fmt, args...)     log_trace(LOG4C_PRIORITY_TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, ##args)
        #else
            #define LOG_CRITICAL(fmt, args...)  log_proxy(LOG4C_PRIORITY_CRIT, fmt, ##args)
            #define LOG_ERROR(fmt, args...)     log_proxy(LOG4C_PRIORITY_ERROR, fmt, ##args)
            #define LOG_WARN(fmt, args...)      log_proxy(LOG4C_PRIORITY_WARN, fmt , ##args)
            #define LOG_INFO(fmt, args...)      log_proxy(LOG4C_PRIORITY_INFO, fmt , ##args)
            #define LOG_DEBUG(fmt, args...)     log_proxy(LOG4C_PRIORITY_DEBUG, fmt , ##args)
            #define LOG_TRACE(fmt, args...)     log_proxy(LOG4C_PRIORITY_TRACE, fmt , ##args)
        #endif

        #define LOG_TRACE0(args...)  log_trace(LOG4C_PRIORITY_TRACE, __FILE__, __LINE__, __FUNCTION__, "", ##args)
    #elif _MSC_VER>=1400
        // VC80
        #if (LOG4C_USING_TRACE == 1)
            #define LOG_CRITICAL(fmt, ...)  log_trace(LOG4C_PRIORITY_CRIT, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
            #define LOG_ERROR(fmt, ...)     log_trace(LOG4C_PRIORITY_ERROR, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
            #define LOG_WARN(fmt, ...)      log_trace(LOG4C_PRIORITY_WARN, __FILE__, __LINE__, __FUNCTION__, fmt , __VA_ARGS__)
            #define LOG_INFO(fmt, ...)      log_trace(LOG4C_PRIORITY_INFO, __FILE__, __LINE__, __FUNCTION__, fmt , __VA_ARGS__)
            #define LOG_DEBUG(fmt, ...)     log_trace(LOG4C_PRIORITY_DEBUG, __FILE__, __LINE__, __FUNCTION__, fmt , __VA_ARGS__)
            #define LOG_TRACE(fmt, ...)     log_trace(LOG4C_PRIORITY_TRACE, __FILE__, __LINE__, __FUNCTION__, fmt, __VA_ARGS__)
        #else
            #define LOG_CRITICAL(fmt, ...)  log_proxy(LOG4C_PRIORITY_CRIT, fmt, __VA_ARGS__)
            #define LOG_ERROR(fmt, ...)     log_proxy(LOG4C_PRIORITY_ERROR, fmt, __VA_ARGS__)
            #define LOG_WARN(fmt, ...)      log_proxy(LOG4C_PRIORITY_WARN, fmt , __VA_ARGS__)
            #define LOG_INFO(fmt, ...)      log_proxy(LOG4C_PRIORITY_INFO, fmt , __VA_ARGS__)
            #define LOG_DEBUG(fmt, ...)     log_proxy(LOG4C_PRIORITY_DEBUG, fmt , __VA_ARGS__)
            #define LOG_TRACE(fmt, ...)     log_proxy(LOG4C_PRIORITY_TRACE, fmt, __VA_ARGS__)
        #endif

        #define LOG_TRACE0(...)  log_trace(LOG4C_PRIORITY_TRACE, __FILE__, __LINE__, __FUNCTION__, "-", __VA_ARGS__)
    #else
        #error "unsupport compiler"
    #endif
    
#else
    #ifndef LOG4C_DISABLED
        #define LOG4C_DISABLED
    #endif

    #define LOG_INIT()         1
	#define LOG_FINI()	       1

    #if !defined(_MSC_VER)
        #define LOG_MSG(argss...)	   1
        #define LOG_CRITICAL(args...)  1
        #define LOG_ERROR(args...)     1
        #define LOG_WARN(args...)      1
        #define LOG_INFO(args...)      1
        #define LOG_DEBUG(args...)     1
        #define LOG_TRACE(args...)     1
        #define LOG_TRACE0(args...)     1
    #elif _MSC_VER>=1400
        // VC80
        #define LOG_MSG(...)	   1
        #define LOG_CRITICAL(...)  1
        #define LOG_ERROR(...)     1
        #define LOG_WARN(...)      1
        #define LOG_INFO(...)      1
        #define LOG_DEBUG(...)     1
        #define LOG_TRACE(...)     1
        #define LOG_TRACE0(...)    1
    #else
        #error "unsupport compiler"
    #endif

#endif /* LOG4C_ENABLED */


#ifdef __cplusplus
};
#endif


#endif /* _LOG4C_WRAPPER_H_ */


