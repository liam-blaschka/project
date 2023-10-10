#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include <string>

using namespace std;

CurrentWeatherData::CurrentWeatherData(int temperature, string conditions, string location):WeatherData(temperature, conditions, location) {}