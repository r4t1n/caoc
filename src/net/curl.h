#ifndef CURL_H
#define CURL_H

#define URL_SIZE 43

#include <curl/curl.h>
#include <stdlib.h>

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void *fptr);

int curl_to_file(CURL *curl, char *url, char *cookie, const char *filename);

#endif
