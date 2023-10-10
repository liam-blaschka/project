#include "WeatherData.h"
#include  <string>

using namespace std;

WeatherData::WeatherData(int temperature, string conditions, string location) {
    this->temperature = temperature;
    this->conditions = conditions;
    this->location = location;
}

int WeatherData::get_temperature() {
    return temperature;
}

void WeatherData::set_temperature(int temperature) {
    this->temperature = temperature;
}

string WeatherData::get_conditions() {
    return conditions;
}

// void WeatherData::update_data(){
    // return
// }