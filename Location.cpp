#include "Location.h"
#include "Coordinates.h"
#include <string>

using namespace std;

Location::Location(string location, Coordinates coordinates) {
    // make text graphic

    this->location = location;
    this->coordinates = coordinates;
}

Location::Location():Location("", Coordinates()) {}

string Location::get_string() {
    return location;
}

void Location::set_string(string location) {
    this->location = location;
}

Coordinates Location::get_coordinates() {
    return coordinates;
}

void Location::set_coordinates(Coordinates coordinates) {
    this->coordinates = coordinates;
}

void Location::set_is_activated(bool is_activated) {
    this->is_activated = is_activated;
}