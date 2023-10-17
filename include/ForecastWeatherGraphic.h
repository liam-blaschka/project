#ifndef FORECASTWEATHEGRAPHIC_H
#define FORECASTWEATHEGRAPHIC_H

#include "Graphic.h"
#include "WeatherGraphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// represents the graphic of the forecast weather data
class ForecastWeatherGraphic : public WeatherGraphic {
    private:
        int min_temperature;
        int max_temperature;
        int rain_chance;
        string day;
        Text rain_chance_text;
        Texture rain_drop_texture;
        Sprite rain_drop_icon;
        Text day_text;
    public:
        // constructors
        ForecastWeatherGraphic();
        ForecastWeatherGraphic(Font& font, Vector2f position, string day);

        // sets the icon according to the paramater icon_id
        void set_icon(string icon_id) override;

        // returns the minimum temperature
        int get_min_temperature();

        // sets the minimum and maximum temperatures of the graphic to those in the paramaters
        void set_temperatures(int min_temperature, int max_temperature);

        // returns the rain chance
        int get_rain_chance();

        // sets the rain chance of the graphic to the inputted paramater
        void set_rain_chance(int rain_chance);

        // returns the day the forecast weather graphic is displaying
        string get_day();

        // sets the day of the graphic with the paramater
        void set_day(string day);

        // draws the graphic onto the window
        void draw(RenderTarget&, RenderStates states) const override;
};

#endif