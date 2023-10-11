#ifndef CURRENTWEATHERDATA_H
#define CURRENTWEATHERDATA_H

#include "WeatherData.h"
#include <string>

using namespace std;

class CurrentWeatherData : public WeatherData {
    private:
        int temperature;
    public:
        CurrentWeatherData(string location);
        int get_temperature();
        void set_temperature(int temperature);
        void update_data(json data);
        // draw(RenderTarget& target, RenderStates states) override;
        ~CurrentWeatherData() {}


        void display();
};

#endif