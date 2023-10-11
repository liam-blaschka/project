#include "WeatherData.h"
#include  <string>
#include <iostream>

int main() {
    WeatherData weather_data(0, "", "");

    int result = weather_data.update_data();

    return result;
}