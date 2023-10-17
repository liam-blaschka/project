#include "WeatherData.h"
#include "Coordinates.h"
#include  <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;

WeatherData::WeatherData() {}

WeatherData::WeatherData(Coordinates location) {
    this->location = location;
}

string WeatherData::get_icon_id() {
    return icon_id;
}

WeatherData::~WeatherData() {}