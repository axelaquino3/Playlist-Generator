#include <iostream>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include <string>
#include <array>
#include <nlohmann/json.hpp>
#include <vector>

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

    string album_id;

    auto j3 = json::parse(readBuffer);
    json object = j3;

   for(auto& album : object["albums"]["items"]) {
    if( album.contains("data") && album["data"].contains("uri")) {
        cout << "Album uri: " << album["data"]["uri"] << endl;
    }
   }
 
}

void getAlbumsSongs(string album_id) {
    CURL *curlReq = curl_easy_init();
    CURLcode curlRes;
    string readBuffer;

    if(!curlReq) {
        fprintf(stderr, "Error initializing curl\n");
    }

    // Construct the URL
    int urlLength = strlen("https://spotify23.p.rapidapi.com/album_tracks/?id=") + strlen(album_id.c_str()) + strlen("&offset=0&limit=300");
    char *url = new char[urlLength +1];
    strcpy(url, "https://spotify23.p.rapidapi.com/album_tracks/?id=");
    strcat(url, album_id.c_str());
    strcat(url, "&offset=0&limit=300");

    // Set request options
    curl_easy_setopt(curlReq, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(curlReq, CURLOPT_URL, url);


    // Set up headers
    struct curl_slist *headers = NULL;

    headers = curl_slist_append(headers, "X-RapidAPI-Key: 205a1c3ca8msh470045bf2e42150p1e5c31jsn4c331c2321d6");
    headers = curl_slist_append(headers, "X-RapidAPI-Host: spotify23.p.rapidapi.com");
    curl_easy_setopt(curlReq, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curlReq, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curlReq, CURLOPT_WRITEDATA, &readBuffer);

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

    // parser(readBuffer);

    auto j3 = json::parse(readBuffer);
    json object = j3;

   for(auto& song : object["data"]["album"]["tracks"]["items"]) {
    if( song.contains("track") && song["track"].contains("name")) {
        cout << "Song name: " << song["track"]["name"] << endl;
    }
   }

}


int main() {

    // vector to store your playlist
    vector<string> playlistOfSongs = {};
    // string artistName = "eminem";
    string artistName;
    string artistalbum;


    cout << "Welcome to Playlist Generator" << endl;
    cout << "What artist's albums would you like to see?" << endl;
    cin >> artistName; 

    getArtistAlbums(artistName);

    cout << "What album would you like to pick?" << endl;
        // getAlbumsSongs("2cWBwpqMsDJC1ZUwz813lo");


    
    // makes a get request to search
        // getArtistAlbums(artistName);
        // getArtistAlbums("kanye");
        // getAlbumsSongs("2cWBwpqMsDJC1ZUwz813lo");

        // album = getArtistAlbum(artist)
        // song = getAlbumSong(album)

}