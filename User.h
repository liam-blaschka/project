#ifndef USER_H
#define USER_H

using namespace std;

#include "Location.h"
#include <string>

class User {
    private:
        Location location;
    public:
        User();
        string get_location();
};

#endif