#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

#include "file.h"

int path_exists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

int mkdir_recursive(const char *path) {
    char tmp[PATH_MAX];
    char *p = NULL;

    snprintf(tmp, sizeof(tmp), "%s", path);

    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, S_IRWXU);
            *p = '/';
        }
    }

    return mkdir(tmp, S_IRWXU);
}

int copy_file(const char *src, const char *dest) {
    FILE *src_file = fopen(src, "rb");
    if (!src_file) {
        perror("Error opening source file");
        return -1;
    }

    FILE *dest_file = fopen(dest, "wb");
    if (!dest_file) {
        perror("Error opening destination file");
        return -2;
    }

    char buffer[BUFSIZ];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        if (fwrite(buffer, 1, bytes, dest_file) != bytes) {
            perror("Error writing to destination file");
            fclose(src_file);
            fclose(dest_file);
            return -3;
        }
    }

    if (ferror(src_file)) {
        perror("Error reading from source file");
        fclose(src_file);
        fclose(dest_file);
        return -4;
    }

    fclose(src_file);
    fclose(dest_file);

    return 0;
}

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

void read_session_cookie(char *buffer) {
    char filename[PATH_MAX];
    const char *home_dir = getenv("HOME");

    if (home_dir == NULL) {
        perror("Failed to get HOME environment variable");
        exit(EXIT_FAILURE);
    }

    snprintf(filename, PATH_MAX, "%s/.config/adventofcode.session", home_dir);

    read_file_to_buffer(filename, buffer, SESSION_COOKIE_SIZE);
}
