#ifndef WEATHERGRAPHIC_H
#define WEATHERGRAPHIC_H

#include "Graphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class WeatherGraphic : public Graphic {
    protected:
        string icon_id;
        Texture weather_icons;
        Sprite icon;
        Text temperature_text;
     public:
        WeatherGraphic(Font& font, Vector2f position, string icon_id);
        virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif
