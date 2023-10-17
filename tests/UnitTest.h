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
using namespace std;
#include <string>


class UnitTest {
    public:
        void runTests(){
            testCurrentWeatherData();
            testForecastWeatherData();
            testWeatherDataSet();
            testLocation();
            testLocationList();
            testSavedLocations();
            testUser();
            testGraphic();
            testWeatherGraphic();
            testCurrentWeatherGraphic();
            testForecastWeatherGraphic();
            testCoordinates();
            testButton();
            
        }
    private:
        void testCurrentWeatherData() {
            CurrentWeatherData current_weather_data;
            current_weather_data.set_temperature(33);

            if (current_weather_data.get_temperature() != 33) {
                cout << "Test 1 failed!" << endl;
            }
        }
        void testForecastWeatherData(){
            Font font;
            ForecastWeatherData forecast_weather_data(Vector2f(0, 0), "Wed", font, Vector2f(0, 0));
            forecast_weather_data;
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

            forecast_weather_data.set_day(Sun);
            if (forecast_weather_data.get_day() != Sun) {
                count << "Test 4 failed" << endl;
            }
        }
        void testWeatherDataSet(){
            Font font;
            WeatherDataSet weather_data_set;
            CurrentWeatherData weather_data1;
            ForecastWeatherData weather_data2;
            ForecastWeatherData weather_data3;


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
            
            weather_data_set.set_location(Vector2f(-34.921230, 138.599503));

            if (weather_data_set.get_location() != -34.921230, 138.599503) {
                cout << "Test 3 failed!!" << endl;
            }
        }

        void testLocation() {
            Font font 
            Location location ((Vector2f(0, 0), "Wed", font, Vector2f(0, 0)));
            location;
            location.set_string("Adelaide")
            if (location.get_string() != "Adelaide"){
                cout << "Test 1 failed!!" << endl;
            }

            location.set_coordinates(Vector2f(-34.921230, 138.599503));
            if (location.get_coordinates() != -34.921230, 138.599503) {
                cout << "Test 4 failed!" << endl;
            }

        }



       // Location(Font& font, Vector2f position, string location, Coordinates coordinates);
        //void set_string(string location);
       //void set_style(Uint32 style);
       // Coordinates get_coordinates();
       // void set_coordinates(Coordinates coordinates);
       // void activate(Uint32 style);
       // void deactivate();
       // void set_position(Vector2f position) override;
       // Vector2f get_position();
        //FloatRect get_hitbox();
        //bool get_is_hidden();
       // void set_is_hidden(bool is_hidden);
       // void draw(RenderTarget& target, RenderStates states) const override;

}