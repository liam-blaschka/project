#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

class WeatherData {
    protected:
        string conditions;
        string location;

    public:
        WeatherData(string location);
        int get_temperature();
        void set_temperature(int temperature);
        string get_conditions();
        virtual void update_data(json data) = 0;
        


        virtual void display() = 0;
        

        virtual ~WeatherData() = 0;
};

#endif