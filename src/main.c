#include <curl/curl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file/file.h"
#include "net/curl.h"
#include "util/args.h"

int main(int argc, char *argv[]) {
    Args args;
    parse_args(argc, argv, &args);
    printf("Getting input for %i/%i", args.year, args.day);

    if (cached_input_exists(args.year, args.day)) {
        printf("Copying cached input...\n");
        copy_from_cache(args.year, args.day, "input");
        return EXIT_SUCCESS;
    }

    CURL *curl = init_curl();

    char cookie_buffer[SESSION_COOKIE_SIZE];
    int res = read_session_cookie(cookie_buffer);
    if (res != 0) {
        fprintf(stderr, "Error reading session cookie: %s (errno: %d)\n", strerror(res), res);
        return EXIT_FAILURE;
    }

    char url[URL_SIZE];
    snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%d/input", args.year, args.day);

    char cookie[SESSION_COOKIE_SIZE + 9];
    snprintf(cookie, sizeof(cookie), "session=%s", cookie_buffer);

    const char *filename = "input";

    res = curl_to_file(curl, url, cookie, filename);
    if (res != 0) {
        if (res == errno) {
            fprintf(stderr, "Error writing to '%s': %s (errno: %d)\n", filename, strerror(res), res);
        } else {
            fprintf(stderr, "Curl error: %s\n", curl_easy_strerror(res));
        }
        return EXIT_FAILURE;
    }

    res = copy_to_cache(args.year, args.day, filename);

    return EXIT_SUCCESS;
}
