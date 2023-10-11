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
        static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, string *str);
        int update_data();
        // void draw(RenderTarget& target, RenderStates states);
        ~WeatherDataSet();
};

#endif