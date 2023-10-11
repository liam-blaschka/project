#include "WeatherData.h"
#include  <string>
#include <curl/curl.h>
#include <iostream>

using namespace std;

WeatherData::WeatherData(int temperature, string conditions, string location) {
    this->temperature = temperature;
    this->conditions = conditions;
    this->location = location;
}

int WeatherData::get_temperature() {
    return temperature;
}

void WeatherData::set_temperature(int temperature) {
    this->temperature = temperature;
}

string WeatherData::get_conditions() {
    return conditions;
}

// https://www.youtube.com/watch?v=mJVchgjkgL8
int WeatherData::update_data(){
    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        cout << "HTTP request failed" << endl;
        return -1;
    }
    CURLcode result;

    curl_easy_setopt(curl, CURLOPT_URL, "api.openweathermap.org/data/2.5/forecast?lat=34.9285&lon=138.6007&appid=98c29b086524d353c31d3cdd5269bc8f");

    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cout << "Error: " << curl_easy_strerror(result) << endl;
        return -1;
    }

    curl_easy_cleanup(curl);

    return 0;
}