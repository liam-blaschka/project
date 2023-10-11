#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include "ForecastWeatherData.h"
#include "WeatherDataSet.h"
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <ctime>

#include "Coordinates.h"
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

WeatherDataSet::WeatherDataSet(Coordinates location) {
    this->location = location;

    time_t current_time = time(0);
    struct tm* local_time = localtime(&current_time);
    int current_day_index = local_time->tm_wday;

    count = 8;
    weather_data_list = new WeatherData*[count];

    weather_data_list[0] = new CurrentWeatherData(location);
    weather_data_list[1] = new ForecastWeatherData(location, "Today");
    for (int i = 2; i < 8; i++) {
        weather_data_list[i] = new ForecastWeatherData(location, week_days[(current_day_index + i - 1) % 7]);
    }

    // set list to the 8 weather data objects
}

void WeatherDataSet::add_weather_data(WeatherData* data) {
    if (count < 8) {
        weather_data_list[count] = data;
    }
}

void WeatherDataSet::remove_weather_data(int index) {
    if (count > index) {
        delete weather_data_list[index];
        count--;

        for (int i = index; i < count; i++) {
            weather_data_list[i] = weather_data_list[i + 1];
        }
    }
}

int WeatherDataSet::get_count() {
    return count;
}

// https://www.youtube.com/watch?v=mJVchgjkgL8
// https://www.youtube.com/watch?v=mJVchgjkgL8&t=321s
// https://www.appsloveworld.com/c/100/2/c-libcurl-get-output-into-a-string
size_t WeatherDataSet::write_memory_callback(void *contents, size_t size, size_t nmemb, string *str) {
    size_t real_size = size * nmemb;
    try {
        str->append((char*)contents, real_size);
    } catch (bad_alloc &e) {
        cout << "Memory allocation error." << endl;
        return -1;
    }
    return real_size;
}

int WeatherDataSet::update_data() {
    time_t current_time = time(0);
    struct tm* local_time = localtime(&current_time);
    int current_day_index = local_time->tm_wday;

    if (local_time->tm_wday != current_day_index) {
        for (int i = 2; i < 8; i++) {
            weather_data_list[i]->set_day(week_days[(current_day_index + i - 1) % 7]);
        }
    }

    CURL* curl = curl_easy_init();
    if (curl == NULL) {
        cout << "HTTP request failed" << endl;
        return -1;
    }
    CURLcode result;
    string data_literal;

    string url = "api.openweathermap.org/data/2.5/onecall?lat=" + to_string(location.x) + "&lon="
                    + to_string(location.y) + "&exclude=hourly&units=metric&appid=103423645f4a2cd6fd178dc0d3da0097";
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data_literal);


    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        cout << "Error: " << curl_easy_strerror(result) << endl;
        return -1;
    }

    curl_easy_cleanup(curl);

    json data = json::parse(data_literal);

    weather_data_list[0]->update_data(data["current"]);

    for (int i = 1; i < count; i++) {
        weather_data_list[i]->update_data(data["daily"][i - 1]);
    }


    for (int i = 0; i < count; i++) {
        weather_data_list[i]->display();
    }
    

    // write prettified JSON to another file
    std::ofstream o("pretty.json");
    o << std::setw(4) << data << std::endl;
    o.close();

    return 0;
}

WeatherDataSet::~WeatherDataSet() {
    for (int i = 0; i < count; i++) {
        delete weather_data_list[i];
    }
    delete[] weather_data_list;
}