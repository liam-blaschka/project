#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class WeatherData {
    protected:
        int temperature;
        string conditions;
        string location;

    public:
        WeatherData(int temperature, string condition, string location);
        int get_temperature();
        void set_temperature(int temperature);
        string get_conditions();
        // virtual int update_data(json data);
        ~WeatherData() {}
};

#endif