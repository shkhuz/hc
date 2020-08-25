#include "log.h"
#include "hc_internal.h"

void _log(LogLevel log_level, const char* file, u64 line, const char* fmt, ...) {
	char log_level_char;
	char* color;
	switch (log_level) {
		case LOG_LEVEL_INFO: log_level_char = 'I'; color = fcyan;  break;
		case LOG_LEVEL_WARN: log_level_char = 'W'; color = fyellow; break;
		case LOG_LEVEL_ERR:  log_level_char = 'X'; color = fred;   break;
		default: assert(0);
	}
	fprintf(stderr, "[%s%s%s:%s%lu%s][%s%c%s] ", color, file, creset,
											 color, line, creset,
											 color, log_level_char, creset);

	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
	fputs("\n", stderr);
}
