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
#include <ctime>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Coordinates.h"

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(375, 550), "Weather", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    User user = User();
    string user_location_string = user.get_location_string();
    Coordinates user_coordinates = user.get_location_coordinates();

    Font font;
    font.loadFromFile("calibri-regular.ttf");
    // Text text;
    // text.setFont(font);
    // text.setString ("Weather Application");
    // text.setFillColor(Color::White);
    // text.setCharacterSize(35);
    // text.setStyle(Text::Bold);


    CurrentWeatherGraphic current_weather_graphic(font, Vector2f(65, 20), "01d", 32);

    ForecastWeatherGraphic forecast_graphic(font, Vector2f(70, 200), "01d", 16, 18, 0, "Today");


    Location user_location(font, Vector2f(10, 3), user_location_string, user_coordinates);
    user_location.set_style(Text::Bold);

    SavedLocations saved_locations(5, font);

    LocationList locations(8);
    locations.add_location(Location(font, Vector2f(10, 3), "Adelaide", Coordinates(-34.921230, 138.599503)));
    locations.add_location(Location(font, Vector2f(10, 38), "Brisbane", Coordinates(-27.470125, 153.021072)));
    locations.add_location(Location(font, Vector2f(10, 73), "Canberra", Coordinates(-35.282001, 149.128998)));
    locations.add_location(Location(font, Vector2f(10, 108), "Darwin", Coordinates(-12.462827, 130.841782)));
    locations.add_location(Location(font, Vector2f(10, 143), "Hobart", Coordinates(-42.880554, 147.324997)));
    locations.add_location(Location(font, Vector2f(10, 178), "Melbourne", Coordinates(-37.840935, 144.946457)));
    locations.add_location(Location(font, Vector2f(10, 213), "Perth", Coordinates(-31.953512, 115.857048)));
    locations.add_location(Location(font, Vector2f(10, 248), "Sydney", Coordinates(-33.865143, 151.209900)));

    WeatherDataSet weather_data_set(user_coordinates);

    int result = weather_data_set.update_data();
    if (result == -1) {
        return -1;
    }

    string display_mode = "main";

    time_t start = time(0);
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
            }
        }
        
        if (difftime(time(0), start) >= 30) {
            cout << endl;
            user.update_location();
            if (user.get_location_string() != user_location_string) {
                user_location_string = user.get_location_string();
                user_coordinates = user.get_location_coordinates();
                weather_data_set.set_location(user_coordinates);
            }
            result = weather_data_set.update_data();
            if (result == -1) {
                return -1;
            }
            start = time(0);
        }

        window.clear(Color(135, 206, 235));
        // window.draw(text);

        if (display_mode == "main") {
            window.draw(user_location);
        } else if (display_mode == "locations") {
            window.draw(locations);
        }

        window.draw(current_weather_graphic);
        window.draw(forecast_graphic);

        window.display();
    }

    return 0;
}