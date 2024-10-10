#ifndef FILE_H
#define FILE_H

#define PATH_MAX 1024
#define SESSION_COOKIE_SIZE 129

#include <stdlib.h>

int read_file_to_buffer(const char *filename, char *buffer, size_t buffer_size);

int read_session_cookie(char *buffer);

#endif
