#ifndef FILE_H
#define FILE_H

#define PATH_MAX 1024
#define SESSION_COOKIE_VALUE_SIZE 129
#define SESSION_COOKIE_SIZE 129 + 9

#include <stdlib.h>

#include "cache.h"

int path_exists(const char *path);

int mkdir_recursive(const char *path);

int copy_file(const char *src, const char *dest);

int read_file_to_buffer(const char *filename, char *buffer, size_t buffer_size);

void read_session_cookie(char *cookie);

#endif
