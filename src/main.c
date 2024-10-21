#include <stdio.h>

#include <curl/curl.h>

#include "file/file.h"
#include "net/curl.h"
#include "util/args.h"
#include "util/color.h"

int main(int argc, char *argv[]) {
    Args args;
    parse_args(argc, argv, &args);
    printf("Getting input for " ANSI_COLOR_BLUE "%i" ANSI_COLOR_RESET "/" ANSI_COLOR_BLUE "%i" ANSI_COLOR_RESET "...\n", args.year, args.day);

    if (path_exists(get_cache_input_path(args.year, args.day))) {
        printf("Copying cached input...\n");
        copy_from_cache(args.year, args.day, "input");
        return EXIT_SUCCESS;
    }

    CURL *curl = init_curl();

    char cookie_buffer[SESSION_COOKIE_SIZE];
    read_session_cookie(cookie_buffer);

    char url[URL_SIZE];
    snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%d/input", args.year, args.day);

    char cookie[SESSION_COOKIE_SIZE + 9];
    snprintf(cookie, sizeof(cookie), "session=%s", cookie_buffer);

    const char *filename = "input";

    printf("Downloading input from https://adventofcode.com...\n");
    curl_to_file(curl, url, cookie, filename);

    copy_to_cache(args.year, args.day, filename);

    return EXIT_SUCCESS;
}
