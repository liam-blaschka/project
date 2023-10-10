#include "WeatherData.h"
#include "WeatherDataSet.h"
#include <string>

using namespace std;

WeatherDataSet::WeatherDataSet(string location) {
    this->location = location;
    weather_data_list = new WeatherData*[8];


    count = 8;

    // set list to the 8 weather data objects
}

void WeatherDataSet::add_weather_data(WeatherData* data) {
    if (count < 8) {
        weather_data_list[count] = data;
    }
}

void WeatherDataSet::remove_weather_data(int index) {
    if (count > index) {
        delete weather_data_list[index];
        count--;

        for (int i = index; i < count; i++) {
            weather_data_list[i] = weather_data_list[i + 1];
        }
    }
}

int WeatherDataSet::get_count() {
    return count;
}

// void update_data() {
    
// }

WeatherDataSet::~WeatherDataSet() {
    for (int i = 0; i < count; i++) {
        delete weather_data_list[i];
    }
    delete[] weather_data_list;
}