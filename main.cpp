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
    string mouse_cursor_type = "arrow";

    Font font;
    font.loadFromFile("calibri-regular.ttf");

    User user = User();
    string user_location_string = user.get_location_string();
    Coordinates user_coordinates = user.get_location_coordinates();

    Location user_location(font, Vector2f(10, 45), user_location_string, user_coordinates);

    Location active_location(font, Vector2f(10, 3), user_location_string, user_coordinates);
    bool is_user_location_active = true;

    active_location.set_style(Text::Bold);

    SavedLocations saved_locations(5, font);
    Text saved_locations_header;
    saved_locations_header.setFont(font);
    saved_locations_header.setCharacterSize(23);
    saved_locations_header.setPosition(12, 50);
    saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");

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
                bool is_location_activated = false;
                if (active_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    active_location.set_is_activated(true);
                    if (mouse_cursor_type != "hand") {
                        mouse_cursor.loadFromSystem(Cursor::Hand);
                        window.setMouseCursor(mouse_cursor);
                        mouse_cursor_type = "hand";
                    }
                    is_location_activated = true;
                } else {
                    active_location.set_is_activated(false);
                    if (mouse_cursor_type != "arrow") {
                        mouse_cursor.loadFromSystem(Cursor::Arrow);
                        window.setMouseCursor(mouse_cursor);
                        mouse_cursor_type = "arrow";
                    }
                }

                if (!is_location_activated && display_mode == "saved_locations") {
                    if (user_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        user_location.set_is_activated(true);
                        if (mouse_cursor_type != "hand") {
                            mouse_cursor.loadFromSystem(Cursor::Hand);
                            window.setMouseCursor(mouse_cursor);
                            mouse_cursor_type = "hand";
                        }
                        is_location_activated = true;
                    } else {
                        user_location.set_is_activated(false);
                        if (mouse_cursor_type != "arrow") {
                            mouse_cursor.loadFromSystem(Cursor::Arrow);
                            window.setMouseCursor(mouse_cursor);
                            mouse_cursor_type = "arrow";
                        }
                    }
                    if (!is_location_activated) {
                        for (int i = 0; i < saved_locations.get_count(); i++) {
                            if (saved_locations.contains_point(i, Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                                saved_locations.set_is_activated(i, true);
                                if (mouse_cursor_type != "hand") {
                                    mouse_cursor.loadFromSystem(Cursor::Hand);
                                    window.setMouseCursor(mouse_cursor);
                                    mouse_cursor_type = "hand";
                                }
                                is_location_activated = true;
                                break;
                            } else {
                                saved_locations.set_is_activated(i, false);
                                if (mouse_cursor_type != "arrow") {
                                    mouse_cursor.loadFromSystem(Cursor::Arrow);
                                    window.setMouseCursor(mouse_cursor);
                                    mouse_cursor_type = "arrow";
                                }
                            }
                        }
                    }
                }
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (active_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (display_mode == "main") {
                        display_mode = "saved_locations";
                    } else if (display_mode == "saved_locations") {
                        display_mode = "main";
                    }
                } else if (user_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    active_location.set_string(user_location_string);
                    active_location.set_coordinates(user_coordinates);
                    weather_data_set.set_location(user_coordinates);

                    result = weather_data_set.update_data();
                    if (result == -1) {
                        return -1;
                    }
                    start = time(0);

                    saved_locations_header.setPosition(12, 50);
                    saved_locations.set_position_mode(0);
                    is_user_location_active = true;

                    user_location.set_is_activated(false);
                    display_mode = "main";
                } else if (display_mode == "saved_locations") {
                    for (int i = 0; i < saved_locations.get_count(); i++) {
                        if (saved_locations.contains_point(i, Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            active_location.set_string(saved_locations.get_string(i));
                            if (active_location.get_string() == user_location_string) {
                                is_user_location_active = true;
                                active_location.set_coordinates(user_coordinates);
                            } else {
                                active_location.set_coordinates(saved_locations.get_coordinates(i));
                            }
                            weather_data_set.set_location(saved_locations.get_coordinates(i));

                            result = weather_data_set.update_data();
                            if (result == -1) {
                                return -1;
                            }
                            start = time(0);

                            if (is_user_location_active) {
                                saved_locations_header.setPosition(12, 85);
                                saved_locations.set_position_mode(1);
                                is_user_location_active = false;
                            }

                            saved_locations.set_is_activated(i, false);
                            display_mode = "main";
                            break;
                        }
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
                user_location.set_coordinates(user_coordinates);
                user_location.set_string(user_location_string);
                weather_data_set.set_location(user_coordinates);
                if (is_user_location_active) {
                    active_location.set_string(user_location_string);
                    active_location.set_coordinates(user_coordinates);
                }
            }
            // } else if ()
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
            window.draw(saved_locations_header);
            window.draw(saved_locations);
            if (!is_user_location_active) {
                window.draw(user_location);
            }
        } else if (display_mode == "locations") {
            window.draw(locations);
        }

        window.display();
    }

    return 0;
}