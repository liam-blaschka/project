#include "User.h"
#include "Coordinates.h"
#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

User::User() {
    update_location();
}

string User::get_location_string() {
    return location_string;
}

Coordinates User::get_location_coordinates() {
    return location_coordinates;
}

// https://www.youtube.com/watch?v=mJVchgjkgL8
// https://www.youtube.com/watch?v=mJVchgjkgL8&t=321s
// https://www.appsloveworld.com/c/100/2/c-libcurl-get-output-into-a-string
size_t User::write_memory_callback(void *contents, size_t size, size_t nmemb, string *str) {
    size_t real_size = size * nmemb;
    try {
        str->append((char*)contents, real_size);
    } catch (bad_alloc &e) {
        cout << "Memory allocation error." << endl;
        return -1;
    }
    return real_size;
}

int User::update_location() {
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        cout << "HTTP request failed" << endl;
        return -1;
    }
    CURLcode result;
    string data_literal;

    curl_easy_setopt(curl, CURLOPT_URL, "https://ipinfo.io/json");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data_literal);

    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cout << "Error: " << curl_easy_strerror(result) << endl;
        return -1;
    }

    curl_easy_cleanup(curl);

    json data = json::parse(data_literal);

    location_string = data["city"];

    string combined_coords = data["loc"];
    stringstream combined_coords_stream(combined_coords);
    string coordinate;
    int i = 0;
    while (getline(combined_coords_stream, coordinate, ',')) {
        if (i == 0) {
            location_coordinates.x = stod(coordinate);
        } else {
            location_coordinates.y = stod(coordinate);
        }
        i++;
    }

    return 0;
}