#ifndef _LOG_H
#define _LOG_H

#include "types.h"

#define info(s, ...) _log(LOG_LEVEL_INFO, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define warn(s, ...) _log(LOG_LEVEL_WARN, __FILE__, __LINE__, s, ##__VA_ARGS__)
#define err(s, ...)  _log(LOG_LEVEL_ERR, __FILE__, __LINE__, s, ##__VA_ARGS__)

#define fred     "\x1b[1;31m"
#define fgreen   "\x1b[1;32m"
#define fyellow  "\x1b[1;33m"
#define fblue    "\x1b[1;34m"
#define fmagenta "\x1b[1;35m"
#define fcyan    "\x1b[1;36m"
#define creset   "\x1b[0m"

typedef enum {
	LOG_LEVEL_INFO,
	LOG_LEVEL_WARN,
	LOG_LEVEL_ERR,
} LogLevel;

void _log(LogLevel log_level, const char* file, u64 line, const char* fmt, ...);

#endif /* _LOG_H */
