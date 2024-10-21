#ifndef CACHE_H
#define CACHE_H

char* get_cache_path(void);

char* get_cache_dir_path(int year, int day);

char* get_cache_input_path(int year, int day);

void copy_from_cache(int year, int day, const char *dest);

void copy_to_cache(int year, int day, const char *src);

#endif
