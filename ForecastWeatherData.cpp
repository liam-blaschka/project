#include "WeatherData.h"
#include "ForecastWeatherData.h"
#include "Coordinates.h"
#include <string>
#include <math.h>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using json = nlohmann::json;

ForecastWeatherData::ForecastWeatherData(Coordinates location, string day, Font& font, Vector2f position):WeatherData(location) {
    this->day = day;
    graphic = ForecastWeatherGraphic(font, position, day);
}

int ForecastWeatherData::get_rain_chance() {
    return rain_chance;
}

void ForecastWeatherData::set_rain_chance(int rain_chance){
    this->rain_chance = rain_chance;
    graphic.set_rain_chance(rain_chance);
}

int ForecastWeatherData::get_max_temperature() {
    return max_temperature;
}

void ForecastWeatherData::set_max_temperature(int max_temperature) {
    this->max_temperature = max_temperature;
    graphic.set_temperatures(min_temperature, max_temperature);
}

int ForecastWeatherData::get_min_temperature() {
    return min_temperature;
}

void ForecastWeatherData::set_min_temperature(int min_temperature) {
    this->min_temperature = min_temperature;
    graphic.set_temperatures(min_temperature, max_temperature);
}

string ForecastWeatherData::get_day() {
    return day;
}

void ForecastWeatherData::set_day(string day) {
    this->day = day;
    graphic.set_day(day);
}

void ForecastWeatherData::update_data(json data) {
    icon_id = data["weather"][0]["icon"];
    max_temperature = round(float(data["temp"]["max"]));
    min_temperature = round(float(data["temp"]["min"]));
    rain_chance = float(data["pop"]) * 100;

    graphic.set_icon(icon_id);
    graphic.set_temperatures(min_temperature, max_temperature);
    graphic.set_rain_chance(rain_chance);
}

void ForecastWeatherData::draw(RenderTarget& target, RenderStates states) const {
    target.draw(graphic);
}