#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include <string>
#include <math.h>
#include <nlohmann/json.hpp>
#include "Coordinates.h"
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;
using json = nlohmann::json;

CurrentWeatherData::CurrentWeatherData():WeatherData() {}

CurrentWeatherData::CurrentWeatherData(Coordinates location, Font& font, Vector2f position):WeatherData(location) {
    graphic = CurrentWeatherGraphic(font, position);
}

int CurrentWeatherData::get_temperature() {
    return temperature;
}

void CurrentWeatherData::set_temperature(int temperature) {
    this->temperature = temperature;
}

// updates the weather data and graphic using relevant data returned by the API
void CurrentWeatherData::update_data(json data) {
    icon_id = data["weather"][0]["icon"];
    temperature = round(float(data["temp"]));
    graphic.set_icon(icon_id);
    graphic.set_temperature(temperature);
}

void CurrentWeatherData::draw(RenderTarget& target, RenderStates states) const {
    target.draw(graphic);
}