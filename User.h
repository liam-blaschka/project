#ifndef USER_H
#define USER_H

#include "Location.h"
#include <string>

using namespace std;

class User {
    private:
        Location location;
    public:
        User(string location);
        string get_location();
};

#endif