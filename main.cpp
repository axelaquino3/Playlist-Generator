#include <iostream>
#include <stdio.h>
#include <curl/curl.h>


using namespace std;

int main() {
    
    // use this like a file handler when accessing files
    CURL *curl;
    
    // use this variable to store return values from curl API functions
    CURLcode result;


    // This funciton returns a curl handle and stored it in curl
    // We use this to create and manage the request
    curl = curl_easy_init();

    // curl can easily fail and return NULL, so check for it
    if (curl == NULL) {
        // If it fails you'll hit this block and return a -1 as an error status
        // output a standard error that the http request failed
        
        fprintf(stderr, "HTTP requeset failed\n");
        return -1;
    }
    // this function is used to set all the options for the HTTP request
    // needs 3 arguments, handle, constant(option we're setting), and the url for the request
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com" );

    // this carries out the request, function returns a curl code, then store it in variable
    // the curl code returned should be CURLE_OK
    result = curl_easy_perform(curl);

    // check if the request went wrong
    if (result != CURLE_OK) {

         
        // output a standard error that the http request failed
        // return -1 as an error status
        fprintf(stderr, "Error: %\n", curl_easy_strerror(result));
        return -1;
    }


    curl_easy_cleanup(curl);
}