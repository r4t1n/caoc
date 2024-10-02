#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

const int SESSION_COOKIE_SIZE = 129;

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void *fptr) {
    size_t written = fwrite(buffer, itemsize, nitems, fptr);
    return written * itemsize;
}

int get_session_cookie(char *cookie) {
    FILE *fptr;

    fptr = fopen("session", "r");
    if (!fptr) {
        return -1;
    }

    if (fgets(cookie, SESSION_COOKIE_SIZE, fptr) == NULL) {
        fclose(fptr);
        return -2;
    }

    fclose(fptr);

    return 0;
}

int write_input(CURL *curl, char *url, char *cookie) {
    CURLcode res;
    FILE *fptr;

    fptr = fopen("input", "wb");
    if (!fptr) {
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fptr);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        return res;
    }

    curl_easy_cleanup(curl);
    fclose(fptr);

    return 0;
}

int main() {
    CURL *curl = curl_easy_init();

    if (!curl) {
        fprintf(stderr, "Error: curl init failed\n");
        return EXIT_FAILURE;
    }

    char cookie[SESSION_COOKIE_SIZE];
    int res = get_session_cookie(cookie);
    if (res != 0) {
        fprintf(stderr, "Error: failed to get session cookie\n");
        return EXIT_FAILURE;
    }

    // Format session cookie to have a name, equal sign and value
    char formatted_cookie[SESSION_COOKIE_SIZE + 9];
    snprintf(formatted_cookie, sizeof(formatted_cookie), "session=%s", cookie);

    res = write_input(curl, "https://adventofcode.com/2015/day/1/input", formatted_cookie);
    if (res != 0) {
        fprintf(stderr, "Error: failed to write input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}