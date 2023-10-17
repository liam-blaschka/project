#ifndef USER_H
#define USER_H

#include "Coordinates.h"
#include <string>

using namespace std;

// represents the user, is used to determine and store the user's locaiton
class User {
    private:
        string location_string;
        Coordinates location_coordinates;
    public:
        // default and only constructor
        User();

        // returns the location string (name of location) of the user's locaiton
        string get_location_string();

        // returns the coordinates (latitude, longitude)
        Coordinates get_location_coordinates();

        // updates the user's current location using an API that returns information about user's IP
        int update_location();

        // used by the update locaiton function as part of storing the API data in a string
        static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, string *str);
};

#endif