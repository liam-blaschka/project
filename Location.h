#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include "Coordinates.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Location {
    private:
        Coordinates coordinates;
        string location;
        Text text;
        bool is_activated;
    public:
        Location();
        Location(string location, Coordinates coordinates, Font& font);
        string get_string();
        void set_string(string location);
        Coordinates get_coordinates();
        void set_coordinates(Coordinates coordinates);
        void set_is_activated(bool is_activated);
        // draw(RenderTarget& target, RenderStates states);

};

#endif