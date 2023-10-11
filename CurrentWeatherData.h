#ifndef CURRENTWEATHERDATA_H
#define CURRENTWEATHERDATA_H

#include "WeatherData.h"
#include <string>

#include "Coordinates.h"

using namespace std;

class CurrentWeatherData : public WeatherData {
    private:
        int temperature;
    public:
        CurrentWeatherData(Coordinates location);
        int get_temperature() override;
        void set_temperature(int temperature) override;
        void update_data(json data) override;
        // draw(RenderTarget& target, RenderStates states) override;
        ~CurrentWeatherData() {}


        void display() override;
};

#endif