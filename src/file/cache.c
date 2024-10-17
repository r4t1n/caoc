#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

char* get_cache_path(void) {
    const char *home_dir = getenv("HOME");
    if (home_dir == NULL) {
        perror("Failed to get HOME environment variable");
        return NULL;
    }

    char *cache_path = malloc(PATH_MAX);
    if (cache_path == NULL) {
        perror("Failed to allocate memory for cache path");
        return NULL;
    }

    snprintf(cache_path, PATH_MAX, "%s/.cache/caoc", home_dir);

    if (!path_exists(cache_path)) {
        int res = mkdir_recursive(cache_path);
        if (res != 0) {
            return NULL;
        }
    }

    return cache_path;
}

int cached_input_exists(int year, int day) {
    char *cache_path = get_cache_path();
    if (cache_path == NULL) {
        free(cache_path);
        return -1;
    }

    char cached_input_path[PATH_MAX];
    snprintf(cached_input_path, sizeof(cached_input_path), "%s/%i/%i/input", cache_path, year, day);
    free(cache_path);

    return (path_exists(cached_input_path));
}

int copy_from_cache(int year, int day, const char *dest) {
    char *cache_path = get_cache_path();
    if (cache_path == NULL) {
        free(cache_path);
        return -1;
    }

    char src[PATH_MAX];
    snprintf(src, sizeof(src), "%s/%i/%i/input", cache_path, year, day);
    free(cache_path);

    int res = copy_file(src, dest);
    if (res != 0) {
        return res;
    }

    return 0;
}

int copy_to_cache(int year, int day, const char *src) {
    char *cache_path = get_cache_path();
    if (cache_path == NULL) {
        free(cache_path);
        return -1;
    }

    char dest[PATH_MAX];
    snprintf(dest, sizeof(dest), "%s/%i/%i", cache_path, year, day);
    free(cache_path);

    int res = mkdir_recursive(dest);
    if (res != 0) {
        return res;
    }

    snprintf(dest, sizeof(dest), "%s/input", dest);

    res = copy_file(src, dest);
    if (res != 0) {
        return res;
    }

    return 0;
}
