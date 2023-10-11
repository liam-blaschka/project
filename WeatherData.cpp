#include "WeatherData.h"
#include  <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

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

// int WeatherData::update_data(json data){
//     return 0;
// }