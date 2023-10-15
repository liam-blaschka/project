#ifndef CURRENTWEATHERGRAPHIC_H
#define CURRENTWEATHERGRAPHIC_H

#include "Graphic.h"
#include "WeatherGraphic.h"
#include <SFML/Graphics.hpp>

class CurrentWeatherGraphic : public WeatherGraphic {
    private:
        int temperature;
    public:
        CurrentWeatherGraphic(Font& font, Vector2f position, string icon_id, int temperature);
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif