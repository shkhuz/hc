#ifndef _FILE_H
#define _FILE_H

#include "types.h"

typedef struct File File;

File* file_read(const char* fpath);
bool file_exists(const char* fpath);

#endif /* _FILE_H */
