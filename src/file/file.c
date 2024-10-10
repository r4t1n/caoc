#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

int read_file_to_buffer(const char *filename, char *buffer, size_t buffer_size) {
    FILE *fptr;

    fptr = fopen(filename, "r");
    if (!fptr) {
        return errno;
    }

    if (fgets(buffer, buffer_size, fptr) == NULL) {
        fclose(fptr);
        return errno;
    }

    fclose(fptr);
    return 0;
}

int read_session_cookie(char *buffer) {
    char filename[PATH_MAX];
    const char *home_dir = getenv("HOME");

    if (home_dir == NULL) {
        return errno;
    }

    snprintf(filename, PATH_MAX, "%s/.config/adventofcode.session", home_dir);

    int res = read_file_to_buffer(filename, buffer, SESSION_COOKIE_SIZE);
    if (res != 0) {
        return res;
    }

    return 0;
}
