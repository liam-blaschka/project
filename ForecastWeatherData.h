#ifndef FORECASTWEATHERDATA_H
#define FORECASTWEATHERDATA_H

#include "WeatherData.h"
#include <string>
#include <nlohmann/json.hpp>

#include "Coordinates.h"

using namespace std;

class ForecastWeatherData : public WeatherData {
    private:
        int max_temperature;
        int min_temperature;
        int rain_chance;
        string day;
    public:
        ForecastWeatherData(Coordinates location, string day);
        int get_rain_chance() override;
        void set_rain_chance(int rain_chance) override;
        int get_max_temperature() override;
        void set_max_temperature(int max_temperature) override;
        int get_min_temperature() override;
        void set_min_temperature(int min_temperature) override;
        string get_day() override;
        void set_day(string day) override;
        void update_data(json data) override;
        ~ForecastWeatherData() {}


        void display() override;
};

#endif