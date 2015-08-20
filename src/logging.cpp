//
// Created by Wizmann on 15/7/26.
//

#include "logging.h"

static log4c_category_t *log_category = NULL;

int log_open(const char *category)
{
    if (log4c_init() == 1)
    {
        return -1;
    }
    log_category = log4c_category_get(category);
    return 0 ;
}

void log_message(int priority , const char *fmt , ...)
{
    // vlog doesn't check the log level, just print them out
    // and we can pass the variable prams to another function as variable prams
    // so I check the log4c source codes and add the priority checking into this function
    // 4 hours with this tiny problem
    // shame on the irresponsible answer on the internet!
    if (!log_category) {
        fprintf(stderr, "WARNING: log4c should be initialized first!");
        return;
    }

    if (!log4c_category_is_priority_enabled(log_category, priority)) {
        return;
    }

    va_list ap;
    va_start(ap, fmt);
    log4c_category_vlog(log_category , priority , fmt , ap);
    va_end(ap);
}

int log_close()
{
    return (log4c_fini());
}