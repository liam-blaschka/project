#include "WeatherData.h"
#include "ForecastWeatherData.h"
#include <string>
#include <math.h>
#include <nlohmann/json.hpp>

#include "Coordinates.h"
#include <iostream>

using namespace std;
using json = nlohmann::json;

ForecastWeatherData::ForecastWeatherData(Coordinates location, string day):WeatherData(location) {
    this->day = day;
}

int ForecastWeatherData::get_rain_chance() {
    return rain_chance;
}
void ForecastWeatherData::set_rain_chance(int rain_chance){
    this-> rain_chance = rain_chance;
}

int ForecastWeatherData::get_max_temperature() {
    return max_temperature;
}

void ForecastWeatherData::set_max_temperature(int max_temperature) {
    this->max_temperature = max_temperature;
}

int ForecastWeatherData::get_min_temperature() {
    return min_temperature;
}

void ForecastWeatherData::set_min_temperature(int min_temperature) {
    this->min_temperature = min_temperature;
}

string ForecastWeatherData::get_day() {
    return day;
}

void ForecastWeatherData::set_day(string day) {
    this->day = day;
}

void ForecastWeatherData::update_data(json data) {
    conditions = data["weather"][0]["main"];
    max_temperature = round(float(data["temp"]["max"]));
    min_temperature = round(float(data["temp"]["min"]));
    rain_chance = round(float(data["pop"]));
    // day
}



void ForecastWeatherData::display() {
    cout << day << " - " << conditions << ", " << "max: " << max_temperature << ", min: " << min_temperature << ", Rain Chance: " << rain_chance << "%" << endl;
}