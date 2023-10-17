#ifndef CURRENTWEATHERDATA_H
#define CURRENTWEATHERDATA_H

#include "WeatherData.h"
#include "CurrentWeatherGraphic.h"
#include "Coordinates.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

// class represents the current weather data
class CurrentWeatherData : public WeatherData {
    private:
        int temperature;
        CurrentWeatherGraphic graphic;
    public:
        CurrentWeatherData();
        CurrentWeatherData(Coordinates location, Font& font, Vector2f position);
        int get_temperature() override;
        void set_temperature(int temperature) override;
        void update_data(json data) override;
        void draw(RenderTarget& target, RenderStates states) const override;
        ~CurrentWeatherData() {}
};

#endif