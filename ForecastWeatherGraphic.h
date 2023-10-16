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
        int min_temperature;
        int max_temperature;
        int rain_chance;
        string day;
        Text rain_chance_text;
        Sprite rain_drop_icon;
        Text day_text;
    public:
        ForecastWeatherGraphic();
        ForecastWeatherGraphic(Font& font, Vector2f position, string day);
        void set_icon(string icon_id) override;
        int get_min_temperature();
        void set_temperatures(int min_temperature, int max_temperature);
        int get_rain_chance();
        void set_rain_chance(int rain_chance);
        string get_day();
        void set_day(string day);
        void draw(RenderTarget&, RenderStates states) const override;
};

#endif