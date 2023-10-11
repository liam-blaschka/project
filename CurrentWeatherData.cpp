#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include <string>
#include <math.h>
#include <nlohmann/json.hpp>

#include <iostream>

using namespace std;
using json = nlohmann::json;

CurrentWeatherData::CurrentWeatherData(string location):WeatherData(location) {}

int CurrentWeatherData::get_temperature() {
    return temperature;
}

void CurrentWeatherData::set_temperature(int temperature) {
    this->temperature = temperature;
}

void CurrentWeatherData::update_data(json data) {
    conditions = data["weather"][0]["main"];
    temperature = round(float(data["temp"]));
}



void CurrentWeatherData::display() {
    cout << conditions << " " << temperature << endl;
}