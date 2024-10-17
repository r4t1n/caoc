#ifndef CACHE_H
#define CACHE_H

char* get_cache_path(void);

int cached_input_exists(int year, int day);

int copy_from_cache(int year, int day, const char *dest);

int copy_to_cache(int year, int day, const char *src);

#endif
