#ifndef USER_H
#define USER_H

#include "Coordinates.h"
#include <string>

using namespace std;

class User {
    private:
        string location_string;
        Coordinates location_coordinates;
    public:
        User();
        string get_location_string();
        Coordinates get_location_coordinates();
        int update_location();
        static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, string *str);
};

#endif