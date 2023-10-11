#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>
#include <nlohmann/json.hpp>

#include "Coordinates.h"

using namespace std;
using json = nlohmann::json;

class WeatherData {
    protected:
        string conditions;
        Coordinates location;

    public:
        WeatherData(Coordinates location);
        string get_conditions();
        virtual void update_data(json data) = 0;

        virtual int get_temperature() { return 0; }
        virtual void set_temperature(int temperature) {}
        virtual int get_rain_chance() { return 0; }
        virtual void set_rain_chance(int rain_chance) {}
        virtual int get_max_temperature() { return 0; }
        virtual void set_max_temperature(int max_temperature) {}
        virtual int get_min_temperature() { return 0; }
        virtual void set_min_temperature(int min_temperature) {}
        virtual string get_day() { return ""; }
        virtual void set_day(string day) {}

        virtual ~WeatherData() = 0;

        virtual void display() = 0;
};

#endif