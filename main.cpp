#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include "ForecastWeatherData.h"
#include "WeatherDataSet.h"
#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include "User.h"
#include <ctime>

#include <iostream>
#include "Coordinates.h"

using namespace std;

int main() {
    WeatherDataSet weather_data_set(Coordinates(-34.921230, 138.599503));

    int result = weather_data_set.update_data();
    if (result == -1) {
        return -1;
    }

    time_t start = time(0);
    bool running = true;
    while (running) {
        if (difftime(time(0), start) >= 30) {
            cout << endl;
            result = weather_data_set.update_data();
            if (result == -1) {
                return -1;
            }
            start = time(0);
        }
    }

    return 0;
}