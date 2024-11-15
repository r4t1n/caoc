#include <stdio.h>

#include <curl/curl.h>

#include "date/date.h"
#include "file/file.h"
#include "net/curl.h"
#include "util/args.h"
#include "util/color.h"

int main(int argc, char *argv[]) {
    Args args;
    parse_args(argc, argv, &args);
    check_date(args.year, args.day);
    printf("Getting input for " COLOR_BLUE "%i" COLOR_RESET "/" COLOR_CYAN "%i" COLOR_RESET "...\n", args.year, args.day);

    if (path_exists(get_cache_input_path(args.year, args.day))) {
        printf("Copying input from cache...\n");
        copy_from_cache(args.year, args.day, "input");
        return EXIT_SUCCESS;
    } else {
        printf("Downloading input from https://adventofcode.com...\n");
    }

    CURL *curl = init_curl();

    char cookie[SESSION_COOKIE_SIZE];
    read_session_cookie(cookie);

    char url[URL_SIZE];
    snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%d/input", args.year, args.day);

    const char *filename = "input";

    curl_to_file(curl, url, cookie, filename);
    copy_to_cache(args.year, args.day, filename);
}
