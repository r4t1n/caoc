#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>

#include "curl.h"

CURL *init_curl(void) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error: curl init failed\n");
        exit(EXIT_FAILURE);
    }

    return curl;
}

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void *fptr) {
    size_t written = fwrite(buffer, itemsize, nitems, fptr);
    return written * itemsize;
}

int curl_to_file(CURL *curl, char *url, char *cookie, const char *filename) {
    CURLcode res;
    FILE *fptr;

    fptr = fopen(filename, "wb");
    if (!fptr) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "CURL error: %s\n", curl_easy_strerror(res));
        fclose(fptr);
        exit(EXIT_FAILURE);
    }

    curl_easy_cleanup(curl);
    fclose(fptr);

    return 0;
}
