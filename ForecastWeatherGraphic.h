#ifndef FORECASTWEATHEGRAPHIC_H
#define FORECASTWEATHEGRAPHIC_H

#include "Graphic.h"
#include "WeatherGraphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class ForecastWeatherGraphic : public WeatherGraphic {
    private:
        Sprite rain_chance_text;
        Text day_text;
    public:
        ForecastWeatherGraphic(Font& font, Vector2f position, string icon_id, int min_temperature,int max_temperature, int rain_chance, string day);
        void draw(RenderTarget&, RenderStates states) const override;
};

#endif