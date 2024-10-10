#include <curl/curl.h>
#include <errno.h>

size_t got_data(char *buffer, size_t itemsize, size_t nitems, void *fptr) {
    size_t written = fwrite(buffer, itemsize, nitems, fptr);
    return written * itemsize;
}

int curl_to_file(CURL *curl, char *url, char *cookie, const char *filename) {
    CURLcode res;
    FILE *fptr;

    fptr = fopen(filename, "wb");
    if (!fptr) {
        return errno;
    }

    const char *user_agent = "github.com/r4t1n/caoc by ratin";

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, user_agent);
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
