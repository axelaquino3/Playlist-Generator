#include <iostream>
#include <fstream>
#include <stdio.h>
#include <curl/curl.h>
#include <cstring>
#include <string>
#include <array>
#include <nlohmann/json.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace nlohmann;

map<string, string> albumCache;
vector<string> playlistOfSongs;


json parser(string input) {

    json object; 
    
    try {
        auto j3 = json::parse(input);
        object = j3;
    } catch (json::exception& e) {
        cout << "Error parsing JSON: " << e.what() << endl;
    }

    return object;

}

string extractAlbumID(const string &fullID) {
    size_t pos = fullID.rfind(':');

    if (pos != string::npos){
        return fullID.substr(pos + 1);
    } else {
        return  ""; // Return an empty string if ":" is not found
    }
}

string findAlbumID(string& userInputAlbumName) {
   for (auto it = albumCache.begin(); it != albumCache.end(); it++) {
            if (it-> first == userInputAlbumName) {
                return it-> second;
            }
            // cout << "key:" << it-> first << "value: " << it-> second << endl;
        }
    return "";
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


    // if (albumCache.find(artistName) != albumCache.end()) {
    //     cout << "Retrieving album for " << artistName << " from cache..." << endl;
    //     parser(albumCache[artistName].to_string());
    //     return;
    // }

    json object = parser(readBuffer);    

    for (const auto& album : object["albums"]["items"]) {

        if (album.contains("data")) {

            cout << "Album name: " << album["data"]["name"] << endl;
            // cout << "Album uri: " << extractAlbumID(album["data"]["uri"]) << endl;

            albumCache[album["data"]["name"]] = extractAlbumID(album["data"]["uri"]);
            
            //mutable array where you store it into an object
        
            /*
            // this would be outside the for loop
            
            let array = []
            //this part is inside the loop
            let object = {
                id: album[data][id],
                name: album[data][name],
            }

            array.push(object)
            */

            //loop through the array and find which name user input and check that user input matches the name of the object and get id

            //outside of loop initialize variable ex: let id;
            // loop throguh make if statement (if array[i][name] == userinput) set id = array[i][id] 
        
        } else {

        cout << "Album missing name or data property" << endl;
        
        }


        // for (auto it = albumCache.begin(); it != albumCache.end(); it++) {
        //     cout << "key:" << it-> first << "value: " << it-> second << endl;
        // }

    }
    

    string album_id;

    // findAlbumID(album_id, readBuffer);

//     auto j3 = json::parse(readBuffer);
//     json object = j3;

//    for(auto& album : object["albums"]["items"]) {
//     if( album.contains("data") && album["data"].contains("uri")) {
//         cout << "Album uri: " << album["data"]["uri"] << endl;
//     }
//    }
 
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

void addToPlaylist(string songTitle) {
    playlistOfSongs.push_back(songTitle);
}


int main() {

    // vector to store your playlist
    string artistName;
    string chosenAlbum;

    cout << "*** Welcome to Playlist Generator ***" << endl;

    while(true) {
        cout << "What artist's albums would you like to see?" << endl;
        cin >> artistName; 
        
        if(artistName == "exit") {
            cout << "Creating your playlist!" << endl;
            break;
        }
        
        // Fetch album of the artist
        getArtistAlbums(artistName);
        // system("clear");

        cout << "Enter the name of the album you want to pick (Type 'back' to choose another artist):" << endl;
        string chosenAlbum;
        cin.ignore(); // handles input buffer issues
        getline(cin, chosenAlbum);

        if(chosenAlbum == "back") {
            // Go back to inputting artist name
            continue;
        }

        string chosenAlbumID = findAlbumID(chosenAlbum); // = findAlbumID(chosenAlbum, )

        // cout << chosenAlbumID << endl;

        if(!chosenAlbumID.empty()) {
            getAlbumsSongs(chosenAlbumID);
        } else {
            cout << "Album not found." << endl;
        }


        cout << "Enter the song you would you like to add to your playlist" << endl;
        string chosenSong;
        // cin.ignore();
        getline(cin, chosenSong);

        addToPlaylist(chosenSong);


        cout << "Would you like to see the songs in your playlist?" << endl;
        cout << "Select y/n" << endl;
        string answer;

        getline(cin, answer);

        if (answer == "y") {
            for (const auto& song : playlistOfSongs) {
                cout << song << endl;
            }
        }

        if (answer == "n") {
            continue;
        }

    }

    

   

    

    
    // makes a get request to search
        // getArtistAlbums(artistName);
        // getArtistAlbums("kanye");
        
        // getAlbumsSongs("2cWBwpqMsDJC1ZUwz813lo");

        // album = getArtistAlbum(artist)
        // song = getAlbumSong(album)

}