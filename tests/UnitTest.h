#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include "ForecastWeatherData.h"
#include "WeatherDataSet.h"
#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include "User.h"
#include "Graphic.h"
#include "WeatherGraphic.h"
#include "CurrentWeatherGraphic.h"
#include "ForecastWeatherGraphic.h"
#include "Coordinates.h"
#include "Button.h"

#include <iostream>
#include <string>

using namespace std;

class UnitTest {
    public:
        void runTests(){
            testCurrentWeatherData();
            testForecastWeatherData();
            testWeatherDataSet();
            testLocation();
            testLocationList();
            testSavedLocations();
            //testUser();
           // testGraphic();
           //testWeatherGraphic();
           // testCurrentWeatherGraphic();
           // testForecastWeatherGraphic();
            testCoordinates();
           // testButton();
            
        }
    private:
        void testCurrentWeatherData() {
            CurrentWeatherData current_weather_data;
            current_weather_data.set_temperature(33);

            if (current_weather_data.get_temperature() != 33) {
                cout << "Test 1 failed!" << endl;
            }
        }
        void testForecastWeatherData() {
            Font font;
            ForecastWeatherData forecast_weather_data(Coordinates(0, 0), "Wed", font, Vector2f(0, 0));

            forecast_weather_data.set_rain_chance(10);

            if (forecast_weather_data.get_rain_chance() != 10){
                cout << "Test 1 failed!" << endl;
            }
            
            forecast_weather_data.set_max_temperature(30);
            if (forecast_weather_data.get_max_temperature() != 30){
                cout << "Test 2 failed" << endl;
            }

            forecast_weather_data.set_min_temperature(5);
            if (forecast_weather_data.get_min_temperature() != 5){
                cout << "Test 3 failed" << endl;
            }

            forecast_weather_data.set_day("Sun");
            if (forecast_weather_data.get_day() != "Sun") {
                cout << "Test 4 failed" << endl;
            }
        }
        void testWeatherDataSet() {
            Font font;
            WeatherDataSet weather_data_set(Coordinates(0, 0), font);
            CurrentWeatherData* weather_data1 = new CurrentWeatherData;
            ForecastWeatherData* weather_data2 = new ForecastWeatherData;
            ForecastWeatherData* weather_data3 = new ForecastWeatherData;

            weather_data_set.add_weather_data(weather_data1);
            weather_data_set.add_weather_data(weather_data2);
            weather_data_set.add_weather_data(weather_data3);

            if (weather_data_set.get_count() != 3) {
                cout << "Test 1 failed!!" << endl;
            }
            
            weather_data_set.remove_weather_data(1);

            if (weather_data_set.get_count() != 2) {
                cout << "Test 2 failed!!" << endl;
            }
        }

        void testLocation() {
            Font font;
            Location location(font, Vector2f(0,0),"Adelaide", Coordinates(0,0));

            location.set_string("Adelaide");
            if (location.get_string() != "Adelaide"){
                cout << "Test 1 failed!!" << endl;
            }

            location.set_coordinates(Coordinates(-34.921230, 138.599503));
            if (location.get_coordinates().x != -34.921230 || location.get_coordinates().y != 138.599503) {
                cout << "Test 2 failed!!" << endl;
            }

            location.activate(Text::Regular);
            if (!location.get_is_activated()) {
                cout << "Test 3 failed!!" << endl;
            }
            
            location.deactivate();
            if (location.get_is_activated()) {
                cout << "Test 4 failed!!" << endl;
            }
            
            location.set_position(Vector2f(2, 4));
            if (location.get_position().x != 2 || location.get_position().y != 4) {
                cout << "Test 5 failed!!" << endl; 
            }
        }
        void testLocationList () {
            LocationList location_list(8);
            Font font;
            Location location(font, Vector2f(0,0), "Adelaide", Coordinates(0,0));
            

            location_list.add_location(location);
            if (location_list.get_count() != 1) {
                cout<< "Test 1 failed!!" << endl;
            }

            location_list.remove_location(0);
            if (location_list.get_count () != 0){
                cout << "Test 2 failed!!" << endl;
            }

            for (int i = 0; i < 5; i++) {
                location_list.add_location(Location(font, Vector2f(0, 0), to_string(i), Coordinates(0, 0)));
            }

            location_list.move_location(3, 1);

            for (int i = 0; i < 5; i++) {
                if (stoi(location_list.get_string(i)) != i) {
                    cout << "Test 3 failed!!" << endl;
                    break;
                }
            }

            if (location_list.get_location(2).get_string() != "2") {
                cout << "Test 4 failed!!" << endl;
            }

            if (location_list.get_coordinates(3).x != 53.35653 || location_list.get_coordinates(3).y != -33.45634) {
                cout << "Test 5 fail" << endl;
            } // add more if more time
        }
        void testSavedLocations() {
            Font font;
            SavedLocations saved_locations(6, font);

            Location locations[5] = {
                Location(font, Vector2f(0, 0), "0", Coordinates(0, 0)),
                Location(font, Vector2f(0, 0), "1", Coordinates(0, 0)),
                Location(font, Vector2f(0, 0), "2", Coordinates(0, 0)),
                Location(font, Vector2f(0, 0), "3", Coordinates(53.35653, -33.45634)),
                Location(font, Vector2f(0, 0), "4", Coordinates(0, 0))
            };

            saved_locations.add_location(Location(font, Vector2f(0, 0), "Sydney", Coordinates(0, 0)));
            if (saved_locations.get_count() != 6){
                cout << "Test 1 failed!!" << endl;
            }

            if (saved_locations.get_count() != 5){
                    cout << "Test 2 failed!!" << endl;
            }
        }
        void testCoordinates() {
            Coordinates coordinates(-54.45454, 32.35355);
            if (coordinates.x != -54.45454 || coordinates.y != 32.35355) {
                cout << "Test 1 failed!!" << endl;
            }
        }
            
};
