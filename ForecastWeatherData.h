#ifndef FORECASTWEATHERDATA_H
#define FORECASTWEATHERDATA_H

#include "WeatherData.h"
#include <string>
#include <nlohmann/json.hpp>

using namespace std;

class ForecastWeatherData : public WeatherData {
    private:
        int max_temperature;
        int min_temperature;
        int rain_chance;
        string day;
    public:
        ForecastWeatherData(string location);
        int get_rain_chance();
        void set_rain_chance(int rain_chance);
        int get_max_temperature();
        void set_max_temperature(int max_temperature);
        int get_min_temperature();
        void set_min_temperature(int min_temperature);
        string get_day();
        void update_data(json data);
        ~ForecastWeatherData() {}


        void display();
};

#endif