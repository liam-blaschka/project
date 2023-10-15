#ifndef WEATHERGRAPHIC_H
#define WEATHERGRAPHIC_H

#include "Graphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class WeatherGraphic : public Graphic {
    protected:
        Vector2f position;
        Font font;
        string icon_id;
        Texture weather_icons;
        Sprite icon;
        Text temperature_text;
     public:
        WeatherGraphic();
        WeatherGraphic(Font& font, Vector2f position);
        void update_icon();
        Vector2f get_position();
        virtual void set_position(Vector2f position);
        string get_icon_id();
        virtual void set_icon(string icon_id);
        virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif
