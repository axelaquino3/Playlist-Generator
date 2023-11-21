#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include <string>
#include <array>
#include <nlohmann/json.hpp>

using namespace std;
using namespace nlohmann;


void parser(string input) {

    try {
        auto j3 = json::parse(input);
        json object = j3;
        // cout << object << endl;
        // for (int i = 0; i < sizeof(object); i++) {
        //     cout << object["albums"]["items"][i]["data"]["name"] << endl;
        // }

        for (const auto& album : object["albums"]["items"]) {
            if (album.contains("data") && album["data"].contains("name")) {
            cout << "Album name: " << album["data"]["name"] << endl;
        } else {
            cout << "Album missing name or data property" << endl;
  }
}
               

    } catch (json::exception& e) {
        cout << "Error parsing JSON: " << e.what() << endl;
    }

    
    
   
}

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void getArtistAlbums(string artistName) {
    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;
    string readBuffer;

    if(!curlReq) {
        fprintf(stderr, "Error initializing curl\n");
    }

    //  Construct the URL
    int urlLength = strlen("https://spotify23.p.rapidapi.com/search/?q=") + strlen(artistName.c_str()) + strlen("&type=albums&offset=0&limit=10&numberOfTopResults=5");
    char *url = new char[urlLength + 1];
    strcpy(url, "https://spotify23.p.rapidapi.com/search/?q=");
    strcat(url, artistName.c_str());
    strcat(url, "&type=albums&offset=0&limit=10&numberOfTopResults=5");

    // Set request options
    curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curlReq, CURLOPT_URL, url);

    // Set request headers
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: spotify23.p.rapidapi.com");
    curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curlReq, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlReq, CURLOPT_WRITEDATA, &readBuffer);

    // Perform the request
    curlRes = curl_easy_perform(curlReq);

    if(curlRes != CURLE_OK) {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(curlRes));
    } else {
         // Process the response data (handle the response here)

        // Cleanup resources
        curl_easy_cleanup(curlReq);
        curl_slist_free_all(headers);
        delete[] url;
    }

    parser(readBuffer);

}

void getAlbumsSongs() {

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
        getArtistAlbums(artistName);
        getArtistAlbums("Kanye");

}