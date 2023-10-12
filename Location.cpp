#include "Location.h"
#include "Coordinates.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

Location::Location(string location, Coordinates coordinates, Font& font) {
    // make text graphic

    this->location = location;
    this->coordinates = coordinates;
    // text
}

Location::Location() {}

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