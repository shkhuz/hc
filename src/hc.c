#include "hc.h"

void hc_init(void) {
	atexit(_check_mem_errors);
}
