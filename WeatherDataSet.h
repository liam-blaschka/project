#ifndef WEATHERDATASET_H
#define WEATHERDATASET_H

#include "WeatherData.h"

using namespace std;

class WeatherDataSet {
    private:
        WeatherData** weather_data_list;
        int count;
        string location;
    public:
        WeatherDataSet(string location);
        void add_weather_data(WeatherData* data);
        void remove_weather_data(int index);
        int get_count();
        void update_data();
        // void draw(RenderTarget& target, RenderStates states);
        ~WeatherDataSet();
};

#endif