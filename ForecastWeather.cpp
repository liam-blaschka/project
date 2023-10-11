#include "WeatherData.h"
#include "ForecastWeatherData.h"
#include  <string>

using namespace std;

ForecastWeatherData::ForecastWeatherData(int temperature, string conditions, string location, int rain_chance, string day):WeatherData(temperature, conditions, location) {
    this->rain_chance = rain_chance;
    this->day = day;
}

int ForecastWeatherData::get_rain_chance() {
    return rain_chance;
}
void ForecastWeatherData::set_rain_chance(int rain_chance){
    this-> rain_chance = rain_chance;
}
string ForecastWeatherData::get_day(){
    return day;
}

//// int ForecastWeatherData::update_data(){

/// }