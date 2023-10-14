#ifndef LOCATION_H
#define LOCATION_H

#include "Graphic.h"
#include "Coordinates.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Location : public Graphic {
    private:
        Coordinates coordinates;
        string location;
        Text text;
        bool is_activated;
    public:
        Location();
        Location(Font& font, string location, Coordinates coordinates);
        string get_string();
        void set_string(string location);
        Coordinates get_coordinates();
        void set_coordinates(Coordinates coordinates);
        void set_is_activated(bool is_activated);
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif