#ifndef FORECASTWEATHERDATA_H
#define FORECASTWEATHERDATA_H

#include "WeatherData.h"
#include <string>

using namespace std;

class ForecastWeatherData : public WeatherData {
    private:
        int rain_chance;
        string day;
    public:
        ForecastWeatherData(int temperature, string conditions, string location, int rain_chance, string day);
        int get_rain_chance();
        void set_rain_chance(int rain_chance);
        string get_day();
        // int update_data() override;
        ~ForecastWeatherData() {}
};

#endif