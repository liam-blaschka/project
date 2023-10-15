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

    Cursor mouse_cursor;

    User user = User();
    string user_location_string = user.get_location_string();
    Coordinates user_coordinates = user.get_location_coordinates();

    Font font;
    font.loadFromFile("calibri-regular.ttf");

    Location active_location(font, Vector2f(10, 3), user_location_string, user_coordinates);
    active_location.set_style(Text::Bold);

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

    WeatherDataSet weather_data_set(user_coordinates, font);

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
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            } else if (event.type == Event::MouseMoved) {
                if (active_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    active_location.set_is_activated(true);
                    mouse_cursor.loadFromSystem(Cursor::Hand);
                    window.setMouseCursor(mouse_cursor);
                } else {
                    active_location.set_is_activated(false);
                    mouse_cursor.loadFromSystem(Cursor::Arrow);
                    window.setMouseCursor(mouse_cursor);
                }
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (active_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (display_mode == "main") {
                        display_mode = "saved_locations";
                    } else if (display_mode == "saved_locations") {
                        display_mode = "main";
                    }
                }
            }
        }

        if (display_mode == "main" && difftime(time(0), start) >= 30) {
            cout << "refreshed" << endl;
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

        window.clear(Color(66, 182, 245));

        window.draw(active_location);
        if (display_mode == "main") {
            window.draw(weather_data_set);
        } else if (display_mode == "saved_locations") {
            window.draw(saved_locations);
        } else if (display_mode == "locations") {
            window.draw(locations);
        }

        window.display();
    }

    return 0;
}