#ifndef CURRENTWEATHERGRAPHIC_H
#define CURRENTWEATHERGRAPHIC_H

#include "Graphic.h"
#include "WeatherGraphic.h"
#include <SFML/Graphics.hpp>

// represents the weather graphic for the current weather data
class CurrentWeatherGraphic : public WeatherGraphic {
    private:
        int temperature;
    public:
        CurrentWeatherGraphic();
        CurrentWeatherGraphic(Font& font, Vector2f position);
        void set_icon(string icon_id) override;
        int get_temperature();
        void set_temperature(int temperature);
        void set_position(Vector2f postion) override;
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif