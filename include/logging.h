//
// Created by Wizmann on 15/7/26.
//

#ifndef SNAPPYTABLE_LOGGING_H
#define SNAPPYTABLE_LOGGING_H

#include "log4c.h"

#define LOG_PRI_ERROR       LOG4C_PRIORITY_ERROR
#define LOG_PRI_WARN        LOG4C_PRIORITY_WARN
#define LOG_PRI_NOTICE      LOG4C_PRIORITY_NOTICE
#define LOG_PRI_DEBUG       LOG4C_PRIORITY_DEBUG
#define LOG_PRI_TRACE       LOG4C_PRIORITY_TRACE

extern int log_open(const char *category);
extern void log_message(int priority ,const char* fmt, ...);
extern void log_trace(const char *file , int line , const char *func, const char *fmt ,...);
extern int log_close();

#define LOG_ERROR(fmt , args...)    \
    log_message(LOG_PRI_ERROR, fmt, ##args)
#define LOG_WARN(fmt, args...)      \
    log_message(LOG_PRI_WARN, fmt , ##args)
#define LOG_NOTICE(fmt , args...)   \
    log_message(LOG_PRI_NOTICE, fmt , ##args)
#define LOG_DEBUG(fmt , args...)    \
    log_message(LOG_PRI_DEBUG, fmt , ##args)
#define LOG_TRACE(fmt,args...)      \
    log_message(LOG_PRI_TRACE, fmt , ##args)

#endif //SNAPPYTABLE_LOGGING_H
