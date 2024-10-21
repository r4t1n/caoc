#include <stdio.h>
#include <stdlib.h>

#include "cache.h"
#include "file.h"

char* get_cache_path(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        perror("Failed to get HOME environment variable");
        exit(EXIT_FAILURE);
    }

    char *cache_path = malloc(PATH_MAX);
    if (cache_path == NULL) {
        perror("Failed to allocate memory for cache path");
        exit(EXIT_FAILURE);
    }

    snprintf(cache_path, PATH_MAX, "%s/.cache/caoc", home_dir);
    mkdir_recursive(cache_path);

    return cache_path;
}

char* get_cache_dir_path(int year, int day) {
    char *cache_path = get_cache_path();

    char *cached_input_path = malloc(PATH_MAX);
    snprintf(cached_input_path, PATH_MAX, "%s/%i/%i", cache_path, year, day);
    free(cache_path);

    return cached_input_path;
}

char* get_cache_input_path(int year, int day) {
    char *cache_dir = get_cache_dir_path(year, day);
    snprintf(cache_dir, PATH_MAX, "%s/input", cache_dir);
    return cache_dir;
}

void copy_from_cache(int year, int day, const char *dest) {
    char *src = get_cache_input_path(year, day);
    copy_file(src, dest);
    free(src);
}

void copy_to_cache(int year, int day, const char *src) {
    char *cache_dir = get_cache_dir_path(year, day);
    mkdir_recursive(cache_dir);
    free(cache_dir);

    char *dest = get_cache_input_path(year, day);
    copy_file(src, dest);
    free(dest);
}
