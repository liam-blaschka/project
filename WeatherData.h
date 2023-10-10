#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <string>

using namespace std;

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
        void update_data();

    
        
};

#endif