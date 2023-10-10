#include "Location.h"
#include <string>

using namespace std;

Location::Location(string location) {
    // make text graphic

    this->location = location;
}

Location::Location():Location("") {}

string Location::get_string() {
    return location;
}

void Location::set_string(string location) {
    this->location = location;
}

void Location::set_is_activated(bool is_activated) {
    this->is_activated = is_activated;
}