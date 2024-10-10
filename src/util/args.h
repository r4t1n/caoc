#ifndef ARGS_H
#define ARGS_H

typedef struct {
    int day;
    int year;
} Args;

void parse_args(int argc, char *argv[], Args *args);

#endif
