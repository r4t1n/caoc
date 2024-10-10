#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "args.h"

void parse_args(int argc, char *argv[], Args *args) {
    int opt;

    while ((opt = getopt(argc, argv, "d:y:")) != -1) {
        switch (opt) {
            case 'd':
                args->day = atoi(optarg);
                break;
            case 'y':
                args->year = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-d <day>] [-y <year>]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}
