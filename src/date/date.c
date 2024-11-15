#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../util/color.h"

void check_date(const int year, const int day) {
    const time_t t = time(NULL);
    const struct tm tm = *localtime(&t);
    const int current_year = tm.tm_year + 1900;
    const int current_month = tm.tm_mon + 1;

    const int is_year_invalid = (year < 2015 || year > current_year);
    const int is_current_year_not_december = (year == current_year && current_month != 12);
    const int is_day_invalid = (day == 0 || day > 25);

    if (is_year_invalid) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Invalid year given (under 2015 or over %d)\n", current_year);
        exit(EXIT_FAILURE);
    } else if (is_current_year_not_december) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Invalid year given (Advent of Code %d has not started yet)\n", current_year);
        exit(EXIT_FAILURE);
    } else if (is_day_invalid) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Invalid day given (0 or over 25)\n");
        exit(EXIT_FAILURE);
    }
}
