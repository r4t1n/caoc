#include <stdio.h>
#include <curl/curl.h>

int main() {
    CURL *handle;
    CURLcode success;

    handle = curl_easy_init();
    if (handle == NULL) {
        fprintf(stderr, "HTTP request failed/n");
        return 1;
    }

    curl_easy_setopt(handle, CURLOPT_URL, "https://www.google.com");
    success = curl_easy_perform(handle);

    if (success != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(success));
        return 1;
    }

    curl_easy_cleanup(handle);

    return 0;
}