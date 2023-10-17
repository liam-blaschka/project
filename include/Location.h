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
        Uint32 text_style;
        bool is_activated;
        Vector2f position;
        bool is_hidden;
    public:
        Location();
        Location(Font& font, Vector2f position, string location, Coordinates coordinates);
        string get_string();
        void set_string(string location);
        void set_style(Uint32 style);
        Coordinates get_coordinates();
        void set_coordinates(Coordinates coordinates);
        void activate(Uint32 style);
        void deactivate();
        void set_position(Vector2f position) override;
        Vector2f get_position();
        FloatRect get_hitbox();
        bool get_is_hidden();
        void set_is_hidden(bool is_hidden);
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif