#include "User.h"
#include "Location.h"
#include <string>

using namespace std;

User::User(string location) {
    this->location = location;
}

string User::get_location(){
    return location.get_string();
}

// not complete