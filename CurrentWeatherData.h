#ifndef CURRENTWEATHERDATA_H
#define CURRENTWEATHERDATA_H

#include "WeatherData.h"
#include <string>

using namespace std;

class CurrentWeatherData : public WeatherData {
    public:
        CurrentWeatherData(int temperature, string conditions, string location);
        // draw(RenderTarget& target, RenderStates states) override;
};

#endif