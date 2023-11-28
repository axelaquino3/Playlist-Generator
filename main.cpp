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
#include <unistd.h>
// #include <cstdlib>

using namespace std;
using namespace nlohmann;

map<string, string> albumCache;
map<string, string> songCache;
vector<string> playlistOfSongs;
string albumTitle;



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

   

    int index = 1;
    for (const auto& album : object["albums"]["items"]) {

        if (album.contains("data")) {


            //// Get Album Data using Album Name as keys
            // cout << "Album name: " << album["data"]["name"] << endl;
            // albumCache[album["data"]["name"]] = extractAlbumID(album["data"]["uri"]);
            

            // Get Album Data using Numbers as keys
            cout << index << ") " << album["data"]["name"] << endl;
            albumTitle = album["data"]["name"];
            string indexStr = to_string(index);
            albumCache[indexStr] = extractAlbumID(album["data"]["uri"]);
            index++;

            // cout << "Album uri: " << extractAlbumID(album["data"]["uri"]) << endl;

            
        
        } else {

            cout << "Album missing name or data property" << endl;
        
        }


        // for (auto it = albumCache.begin(); it != albumCache.end(); it++) {
        //     cout << "key: " << it-> first << "\n" << "value: " << it-> second << endl;
        // }

    }

    // for(int i = 0; i < object["albums"]["items"].size(); i++) {
    //     albumCache[i + 1] = extractAlbumID(object["data"]["uri"]) << endl;
    // }

     if (object["albums"]["items"].contains("data")){
     albumTitle = object["albums"]["items"]["data"]["name"];
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
         // Process the response data (handle the response here
        // Cleanup resources
        curl_easy_cleanup(curlReq);
        curl_slist_free_all(headers);
        delete[] url;
    }

    auto j3 = json::parse(readBuffer);
    json object = j3;

   int index = 1; 

   
   for (auto& song : object["data"]["album"]["tracks"]["items"]) {
    
    
    // if ((song.contains("track") && song["track"].contains("name")) && (song.contains("track") && song["track"]["artists"]["items"]["profile"].contains("name"))) {
    //     string songName = song["track"]["name"];
    //     string songArtist = song["track"]["artists"]["items"]["profile"]["name"];
        
    //     cout << index << ") " << songArtist  << songName << endl;
    //     index + 1;
    //     string indexStr = to_string(index);
    //     songCache[indexStr] = song["track"]["name"];
    //     index++;
    // }

        if (song.contains("track") && song["track"].contains("name")) {
            string songName;
            string songArtist = "";
            
            songName = song["track"]["name"];  
            
            if (song["track"]["artists"].contains("items") && !song["track"]["artists"]["items"].empty()) {
            
                songArtist = song["track"]["artists"]["items"][0]["profile"]["name"];
            
            }
        
            cout << index << ") " << songArtist << " - " << songName << endl;
            index + 1;
            string indexStr = to_string(index);
            songCache[indexStr] = "Artist: " + songArtist + "\n" + "Song: " + songName + "\n" + "Album: " + albumTitle + "\n";
            index++;
    
        }
   }

 
}

void addToPlaylist(string songTitle) {

    playlistOfSongs.push_back(songCache[songTitle]);
      
}


int main() {

    string artistName;
    string chosenAlbum;
    string chosenAlbumID;

    cout << "\033[1m *** 🎶 Welcome to Playlist Generator 🎶 *** \033[0m" << endl; // bolds the text

    while(true) {
        // system("clear");
        cout << "What artist's albums would you like to see? (Type 'exit' to exit and create your playlist)" << endl;
        cout << "Enter Artist Name: ";
        getline(cin, artistName); 

        if (artistName == "" || artistName.empty()) {
            system("clear");
            cout << "\033[33;1m ⚠ Please Input Artist Name!!! ⚠ \033[0m" << endl; // bolds and adds yellow color to text
            continue;
        } 
        
        if (artistName == "exit") {
            
            cout << "✨ Creating Your Playlist! ✨\n" << endl;
            
            sleep(1);
            
            for (const auto& song : playlistOfSongs) {
                    cout << song << endl;
                }

            break;
        }  
        

        // Fetch album of the artist
        system("clear");
        cout << "💿 \033[1;4m  Album Titles \033[0m 💿\n" << endl; 
        getArtistAlbums(artistName);

        // for (auto it = albumCache.begin(); it != albumCache.end(); it++) {
        //     cout << "key: " << it-> first << "\n" << "value: " << it-> second << endl;
        // }


        cout << "Enter the name of the album you want to pick (Type 'back' to choose another artist):" << endl;
        getline(cin, chosenAlbum);

        if(chosenAlbum == "back") {
            // Go back to inputting artist name
            system("clear");
            continue;
        }

        chosenAlbumID = findAlbumID(chosenAlbum); 

        
        if(!chosenAlbumID.empty()) {
            system("clear");
            getAlbumsSongs(chosenAlbumID);
        } else {
            system("clear");
            cout << "Album not found." << endl;
            continue;
        }


        cout << "Enter the song you would you like to add to your playlist: ";
        string chosenSong;
        // cin.ignore();
        getline(cin, chosenSong);

        addToPlaylist(chosenSong);

        // for (auto it = songCache.begin(); it != songCache.end(); it++) {
        //     cout << "key: " << it-> first << "\n" << "value: " << it-> second << endl;
        // }

        cout << "Do you want to add more songs from this album?" << endl;
        cout << "Select y/n" << endl;
        string answer2;
        getline(cin, answer2);
        
        if(answer2 == "y") {
            
            
            while (true) {

                // system("clear");
                // getAlbumsSongs(chosenAlbumID);

                cout << "Enter the song you would you like to add to your playlist" << endl;
                string chosenSong;
                
                getline(cin, chosenSong);
                addToPlaylist(chosenSong);

                system("clear");
                getAlbumsSongs(chosenAlbumID);

                cout << "Do you want to add more songs from this album?" << endl;
                cout << "Select y/n" << endl;
                string answer3;
                getline(cin, answer3);

                if (answer3 == "y") {
                
                    continue;

                } else if (answer3 == "n") {
                    system("clear");
                    break;
                    
                }

                
            }
            
        }

        if (answer2 == "n") {
            system("clear");
            cout << "Would you like to see the songs in your playlist?" << endl;
            cout << "Select y/n" << endl;
            string answer;

            getline(cin, answer);

            if (answer == "y") {
                system("clear");

                cout << "\033[1m 🎵 Playlist  \033[0m" << endl;

                for (const auto& song : playlistOfSongs) {
                
                    cout << song << endl;

                }

            }

            if (answer == "n") {
                system("clear");
                continue;
            }
        }


    }


}