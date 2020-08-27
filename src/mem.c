#include "mem.h"
#include "log.h"
#include "buf.h"
#include "hc_internal.h"

#define HC_MEM_NO_DEBUG

typedef struct {
	const char* file;
	u64 line;
	void* pointer;
} AllocationInfo;

static AllocationInfo* allocations = null;

void* _malloc_dbg(const char* file, u64 line, u64 sz) {
	if (sz == 0) {
		_log(
			LOG_LEVEL_WARN,
			file,
			line,
			"zero-size allocation (sz = 0); skipping..."
		);
		return null;
	}

	void* p = malloc(sz);
	if (!p) {
		_log(
			LOG_LEVEL_WARN,
			file,
			line,
			"cannot allocate memory: available memory < %lu; skipping...",
			sz
		);
		return null;
	}

	buf_push(allocations, (AllocationInfo){ file, line, p });
	return p;
}

void _free_dbg(const char* file, u64 line, void* p) {
	buf_loop(allocations, a) {
		if (allocations[a].pointer == p) {
			buf_remove(allocations, a);
			free(p);
			return;
		}
	}

	_log(
		LOG_LEVEL_WARN,
		file,
		line,
		"pointer (%p) isn't allocated using malloc();",
		p
		);
}

void _check_mem_errors(void) {
	buf_loop(allocations, a) {
		_log(
			LOG_LEVEL_WARN,
			allocations[a].file,
			allocations[a].line,
			"allocated memory not freed (p = %p);",
			allocations[a].pointer
		);
	}
}
