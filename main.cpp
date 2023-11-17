#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>

using namespace std;

// // function to GET search artist
// void getSearchArtist(string artistName) {

//     CURL *curlReq = curl_easy_init();
//     CURLcode curlRes;
//     int urlLength = strlen("https://deezerdevs-deezer.p.rapidapi.com/search?q=") + strlen(artistName.c_str() + 1);
//     char *url = new char[urlLength];
//     strcpy(url,"https://deezerdevs-deezer.p.rapidapi.com/search?q=");
//     strcat(url, artistName.c_str());

//     //create array for url and artistName and contact them 


//     if (curlReq) { 
//         curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
//         curl_easy_setopt(curlReq, CURLOPT_URL, url);

//         struct curl_slist *headers = NULL;
        
//         headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
//         headers = curl_slist_append(headers, "X-RapidAPI-Host: deezerdevs-deezer.p.rapidapi.com");
//         curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);

//         curlRes = curl_easy_perform(curlReq);

//     } else {

//         fprintf(stderr, "HTTP request failed\n");
//     }

//     if(curlRes != CURLE_OK) {
//         fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
//     }

//     curl_easy_cleanup(curlReq);
//     delete[] url;
    
// }

void getSearchArtist(string artistName) {

    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;

    if (!curlReq) {
        fprintf(stderr, "Error initializing curl\n");
        return;
    }

    // Construct the URL
    int urlLength = strlen("https://deezerdevs-deezer.p.rapidapi.com/search?q=") + strlen(artistName.c_str()) + 1;
    char *url = new char[urlLength];
    strcpy(url, "https://deezerdevs-deezer.p.rapidapi.com/search?q=");
    strcat(url, artistName.c_str());

    // Set request options
    curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curlReq, CURLOPT_URL, url);

    // Set HTTP headers
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: deezerdevs-deezer.p.rapidapi.com");
    curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);

    // Perform the request
    curlRes = curl_easy_perform(curlReq);

    if (curlRes != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
    } else {
        // Process the response data (handle the response here)

        // Cleanup resources
        curl_easy_cleanup(curlReq);
        curl_slist_free_all(headers);
        delete[] url;
    }

    
}

// function to get albums by artist
void getArtistAlbum() {
    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;

    if(curlReq) {
        curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curlReq, CURLOPT_URL, "https://deezerdevs-deezer.p.rapidapi.com/album/1");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: deezerdevs-deezer.p.rapidapi.com");

        curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);

        curlRes = curl_easy_perform(curlReq);

    } else {
        fprintf(stderr, "HTTP request failed\n");
    }

    if(curlRes != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
    }

    curl_easy_cleanup(curlReq);
}


int main() {
    
    // // use this like a file handler when accessing files
    //     CURL *curl;
    
    // // use this variable to store return values from curl API functions
    //     CURLcode result;

        string artistName = "eminem";


    // // This funciton returns a curl handle and stored it in curl
    // // We use this to create and manage the request
    //     curl = curl_easy_init();

    // // curl can easily fail and return NULL, so check for it
    //     if (curl == NULL) {
            
    //         // "fprintf" outputs a formated standard error that the http request failed
    //         // If it fails you'll hit this block and return a -1 as an error status

    //             fprintf(stderr, "HTTP requeset failed\n");
    //             return -1;
    //     }
    
    // // this function is used to set all the options for the HTTP request
    // // needs 3 arguments, handle, constant(option we're setting), and the url for the request
    //     curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com" );

    // // this performs the request, function returns a curl code, then store it in variable
    // // the curl code returned should be CURLE_OK
    //     result = curl_easy_perform(curl);

    // // check if the request went wrong
    //     if (result != CURLE_OK) {

            
    //         // output a formatted standard error that the http request failed. "%s" is a format specifer and is subsituted by w
    //         // return -1 as an error status
    //             fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
    //             return -1;
    //     }

    // // this functions cleans up the curl sessionsn 
    //     curl_easy_cleanup(curl);




    // makes a get request to search
        getSearchArtist(artistName);

    
}