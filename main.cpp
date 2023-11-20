#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;

// // function to GET search artist
void getSearchArtist(string artistName) {

    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;
    
    int urlLength = strlen("https://api.deezer.com/search/artist?q=") + strlen(artistName.c_str() + 1);
    char *url = new char[urlLength];
    strcpy(url, "https://api.deezer.com/search/artist?q=");
    strcat(url, artistName.c_str());

    if (curlReq) { 
        curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curlReq, CURLOPT_URL, url);

        struct curl_slist *headers = NULL;
        
        headers = curl_slist_append(headers, "Cookie: dzr_uniq_id=dzr_uniq_id_fr8a84354f807fb9f48dec7812c73016f1fcd3c1; _abck=2099D2B99BEB7417D619A85A9B26BDCF~-1~YAAQBoXYF4Wird6LAQAAaC1A6QrWbdYJjwgev0JpvnbVOjMS9NRN1e6fcbGq3tVQAbE6aocLqlxRqpRqMztY+CUPv0ZylNkgEPrbcYGEYwUfbqkSuHzeLpjCrzcKzxDQjpB5O5R28Yh+7hYrbFkp4nPAMI2jfvaWMfGN0NefdF//KHTGEWLTzVuFtt6M9TK2CU51m9AX5Fh45daDxspXnWO9FyxHD6Rqqzds5hbcD2L/iqRgjt71hYhSffjdON/Evy6ajFYYW252V7weS/UiKyd4DyhCcrZWhonErC/ucZWSzJoijFF69NroTZodl0XkDiYM9JC9E9KKOIwhimDfRRdsyZKQEWZfGnitzFeKfv99dVK91uVgQoM=~-1~-1~-1; ak_bmsc=77046CBD5FB23B5C39519BFB2D4BC989~000000000000000000000000000000~YAAQBoXYF4aird6LAQAAaC1A6RW6HbMTqJqGbROLT82SCmJqTSP0+a3CRGKqDdtf/h4gk9Rs9WN+Nn7pfXT48348qN2pZIzIvqbZk2LZrZEg1iBpQhHdrOBelnaXzhUIp8oO8E1GreZHxwwoL0E95klQbtI27kc6CfjHQ41o1oulWWf3jzIIaYDn5Yzu22BxL+5eIWrVtApltOQ9yD6ebov17fQYvhx5yUGdOk8xFc9P9TR/D77GdKNNMA0fGdM4p6Ud+/YreizkLRJafYXuQ4TK+y9wULgUKYmUshsNLcNpetG3EqFs1mzQ8FLUW7EAkgPpjPsQPEch8eNZJqDxfiUxR050ZY5Z6IVjlZ9ymDam0hSpHQPraLeigg==; bm_sz=5C41BF191E0A81B92D85C4DC2AB250D6~YAAQBoXYF4eird6LAQAAaC1A6RXUe5FNuUWLReO7D+Zmkji3ubf3PFCcNjyEXB2lZiG+bW1PMNzS9QRso8Ty/tT5XiOCP3EijdFyraMVVPKk5gUygsOu0jTSplTaatIv+Ok7Sl7e2iVWaG9N1chlDrZgxXkHtsp3ig6p7UPswSdqbVaX3blhRSfb72BOv5xZid7oPJS59IrrsMCmDFBGII4Jhr2Fy8GwvlYvtn1NHusgrVZj6lL/IreHbPRLc0nnbqYsq04yyiBnY+TjLpfbT5PtVjr/J7uz2tmUQ9anRjvn9mw=~3162422~4337721; bm_sv=D9B825DED1F87FF4AB5691A9012178A5~YAAQBoXYF5+vrd6LAQAAz3RA6RWmT4VP5mrYxn0dfGn8bsOBBbTf+JXgRbw4TozJrKyOQ0YP9fjiji+hFyPGaw3iz8fmkVEXzcj5D43D9pY21Gpbvye+7ysfr6u0t5JQtQPqVL0CQc6l7iFR43yB8Pajl+V4xzml9EMPEgYZLSLyLE2RQTmDKCtEnw/bhqRNixy5UQ2oOrk6TYJlLzUttMk+a2iQheLsdr1MFcYJSUeGQHAd4xIl6PMYLT8/GFIm~1");
        curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);

        curlRes = curl_easy_perform(curlReq);

    } else {

        fprintf(stderr, "HTTP request failed\n");
    }

    if(curlRes != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
    }

    curl_easy_cleanup(curlReq);
    delete[] url;
    
}

// void getSearchArtist(string artistName) {

//     CURL *curlReq = curl_easy_init();
//     CURLcode curlRes;

//     if (!curlReq) {
//         fprintf(stderr, "Error initializing curl\n");
//         return;
//     }

//     // Construct the URL
//     int urlLength = strlen("https://deezerdevs-deezer.p.rapidapi.com/search?q=") + strlen(artistName.c_str()) + 1;
//     char *url = new char[urlLength];
//     strcpy(url, "https://deezerdevs-deezer.p.rapidapi.com/search?q=");
//     strcat(url, artistName.c_str());

//     // Set request options
//     curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
//     curl_easy_setopt(curlReq, CURLOPT_URL, url);

//     // Set HTTP headers
//     struct curl_slist *headers = NULL;

//     headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
//     headers = curl_slist_append(headers, "X-RapidAPI-Host: deezerdevs-deezer.p.rapidapi.com");
//     curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);

//     // Perform the request
//     curlRes = curl_easy_perform(curlReq);

//     if (curlRes != CURLE_OK) {
//         fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
//     } else {
//         // Process the response data (handle the response here)

//         // Cleanup resources
//         curl_easy_cleanup(curlReq);
//         curl_slist_free_all(headers);
//         delete[] url;
//     }

    
// }

// function to get albums by artist
void getArtistAlbums(string artist_id) {
    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;
    
    int urlLength = strlen("https://api.deezer.com/artist/") + strlen(artist_id.c_str()) + strlen("/albums");
    char *url = new char[urlLength];
    strcpy(url, "https://api.deezer.com/artist/");
    strcat(url, artist_id.c_str());
    strcat(url, "/albums");
    
    if(curlReq) {
        curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curlReq, CURLOPT_URL, url);

        struct curl_slist *headers = NULL;
        
        headers = curl_slist_append(headers, "Cookie: dzr_uniq_id=dzr_uniq_id_fr8a84354f807fb9f48dec7812c73016f1fcd3c1; _abck=2099D2B99BEB7417D619A85A9B26BDCF~-1~YAAQBoXYF4Wird6LAQAAaC1A6QrWbdYJjwgev0JpvnbVOjMS9NRN1e6fcbGq3tVQAbE6aocLqlxRqpRqMztY+CUPv0ZylNkgEPrbcYGEYwUfbqkSuHzeLpjCrzcKzxDQjpB5O5R28Yh+7hYrbFkp4nPAMI2jfvaWMfGN0NefdF//KHTGEWLTzVuFtt6M9TK2CU51m9AX5Fh45daDxspXnWO9FyxHD6Rqqzds5hbcD2L/iqRgjt71hYhSffjdON/Evy6ajFYYW252V7weS/UiKyd4DyhCcrZWhonErC/ucZWSzJoijFF69NroTZodl0XkDiYM9JC9E9KKOIwhimDfRRdsyZKQEWZfGnitzFeKfv99dVK91uVgQoM=~-1~-1~-1; ak_bmsc=77046CBD5FB23B5C39519BFB2D4BC989~000000000000000000000000000000~YAAQBoXYF4aird6LAQAAaC1A6RW6HbMTqJqGbROLT82SCmJqTSP0+a3CRGKqDdtf/h4gk9Rs9WN+Nn7pfXT48348qN2pZIzIvqbZk2LZrZEg1iBpQhHdrOBelnaXzhUIp8oO8E1GreZHxwwoL0E95klQbtI27kc6CfjHQ41o1oulWWf3jzIIaYDn5Yzu22BxL+5eIWrVtApltOQ9yD6ebov17fQYvhx5yUGdOk8xFc9P9TR/D77GdKNNMA0fGdM4p6Ud+/YreizkLRJafYXuQ4TK+y9wULgUKYmUshsNLcNpetG3EqFs1mzQ8FLUW7EAkgPpjPsQPEch8eNZJqDxfiUxR050ZY5Z6IVjlZ9ymDam0hSpHQPraLeigg==; bm_sz=5C41BF191E0A81B92D85C4DC2AB250D6~YAAQBoXYF4eird6LAQAAaC1A6RXUe5FNuUWLReO7D+Zmkji3ubf3PFCcNjyEXB2lZiG+bW1PMNzS9QRso8Ty/tT5XiOCP3EijdFyraMVVPKk5gUygsOu0jTSplTaatIv+Ok7Sl7e2iVWaG9N1chlDrZgxXkHtsp3ig6p7UPswSdqbVaX3blhRSfb72BOv5xZid7oPJS59IrrsMCmDFBGII4Jhr2Fy8GwvlYvtn1NHusgrVZj6lL/IreHbPRLc0nnbqYsq04yyiBnY+TjLpfbT5PtVjr/J7uz2tmUQ9anRjvn9mw=~3162422~4337721; bm_sv=D9B825DED1F87FF4AB5691A9012178A5~YAAQEYXYF+TVuNGLAQAAd6VS6RUjnVtHIJsCK24wem0hHUlnaL5rhu0y9OC5pNz9FGus+tzRlVQu3/VBMVbExi7lWCpPZUxaGUYtJeTrPPuHzMOQUpMLcDM7IFdq0F/xDZz+LPHreExUG00p6thCaKCbgLoXHZX1+qbnWZFkWOyD9Tfj8h1/0lCC9hi8Y0oFU9vGf39SXDssfVZHB7XT5cPcRbHkYcbVOnPBe7wXK3qg/HBXeYUiiTjQLSdasnis~1");
        
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
        // getSearchArtist(artistName);
        getArtistAlbums("13");

}