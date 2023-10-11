#include "WeatherData.h"
#include  <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

WeatherData::WeatherData(string location) {
    this->location = location;
}

string WeatherData::get_conditions() {
    return conditions;
}

WeatherData::~WeatherData() {}