#ifndef WEATHERGRAPHIC_H
#define WEATHERGRAPHIC_H

#include "Graphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// represents the graphic for weather data, inherits from the graphic class,
// is an abstract class
class WeatherGraphic : public Graphic {
    protected:
        Vector2f position;
        Font font;
        string icon_id;
        Texture weather_icons;
        Sprite icon;
        Text temperature_text;
     public:
        // constructors
        WeatherGraphic();
        WeatherGraphic(Font& font, Vector2f position);

        // returns the position of the weather graphic within the window
        Vector2f get_position();

        // sets the postion of the weather graphic in the window
        virtual void set_position(Vector2f position);

        // returns the icon id of the weather graphic, the different graphic icons are identified by this id which is
        // given in the data returned by the API
        string get_icon_id();

        // sets the icon of the weather graphic associated with the paramater icon id
        virtual void set_icon(string icon_id);

        // draws the weahter graphic onto the window (pure virtual)
        virtual void draw(RenderTarget& target, RenderStates states) const = 0;
};

#endif
