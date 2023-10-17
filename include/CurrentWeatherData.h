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
        // constructors
        CurrentWeatherData();
        CurrentWeatherData(Coordinates location, Font& font, Vector2f position);

        // returns the temperature
        int get_temperature() override;

        // sets the temperature
        void set_temperature(int temperature) override;

        // updates the weather data from the relevant json data inputted into paramater
        void update_data(json data) override;

        // draws the graphic for the current weather data to the window
        void draw(RenderTarget& target, RenderStates states) const override;

        // virtual destrcutor as is used with polymorphism
        ~CurrentWeatherData() {}
};

#endif