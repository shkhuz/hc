#ifndef _MEM_H
#define _MEM_H

#include "types.h"

#if defined(HC_MEM_DEBUG) && !defined(HC_MEM_NO_DEBUG)
#define malloc(sz) _malloc_dbg(__FILE__, __LINE__, sz)
#define free(p) _free_dbg(__FILE__, __LINE__, p)
#endif

void* _malloc_dbg(const char* file, u64 line, u64 sz);
void _free_dbg(const char* file, u64 line, void* p);

void _check_mem_errors(void);

#endif /* _MEM_H */
