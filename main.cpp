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
#include "Button.h"
#include <ctime>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Coordinates.h"

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(425, 550), "Weather", Style::Titlebar | Style::Close);
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

    // Texture location_icon_texture;
    // location_icon_texture.loadFromFile("location3.png");
    // location_icon_texture.setSmooth(true);
    // Sprite user_location_icon(location_icon_texture, IntRect(0, 0, 40, 40));
    // FloatRect active_user_location_bounds  = active_location.get_text_bounds();
    // // user_location_icon.setScale(1.5, 1.5);
    // user_location_icon.setPosition(active_user_location_bounds.width + 25, active_user_location_bounds.height);

    active_location.set_style(Text::Bold);

    SavedLocations saved_locations(5, font);
    Text saved_locations_header;
    saved_locations_header.setFont(font);
    saved_locations_header.setCharacterSize(23);
    saved_locations_header.setPosition(12, 50);
    saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");

    Texture add_location_icon_texture;
    add_location_icon_texture.loadFromFile("add_icon2.png");
    add_location_icon_texture.setSmooth(true);
    Button add_location_button(font, Vector2f(8, 75 + saved_locations.get_count() * 36), Sprite(add_location_icon_texture));

    int saved_locations_count = saved_locations.get_count();
    LocationList locations(8);

    locations.add_location(Location(font, Vector2f(0, 0), "Adelaide", Coordinates(-34.921230, 138.599503)));
    locations.add_location(Location(font, Vector2f(0, 0), "Brisbane", Coordinates(-27.470125, 153.021072)));
    locations.add_location(Location(font, Vector2f(0, 0), "Canberra", Coordinates(-35.282001, 149.128998)));
    locations.add_location(Location(font, Vector2f(0, 0), "Darwin", Coordinates(-12.462827, 130.841782)));
    locations.add_location(Location(font, Vector2f(0, 0), "Hobart", Coordinates(-42.880554, 147.324997)));
    locations.add_location(Location(font, Vector2f(0, 0), "Melbourne", Coordinates(-37.840935, 144.946457)));
    locations.add_location(Location(font, Vector2f(0, 0), "Perth", Coordinates(-31.953512, 115.857048)));
    locations.add_location(Location(font, Vector2f(0, 0), "Sydney", Coordinates(-33.865143, 151.209900)));
    // loops through locations
    int unhidden_index = 0;
    for (int i = 0; i < 8; i++) {
        // loops through saved_locations
        for (int j = 0; j < saved_locations_count; j++) {
            if (locations.get_string(i) == saved_locations.get_string(j)) {
                locations.set_is_hidden(i, true);
                break;
            }
        }

        if (!locations.get_is_hidden(i)) {
            locations.set_position(i, Vector2f(10, 111 + (saved_locations_count * 35) + (unhidden_index * 35)));
            unhidden_index++;
        }
    }

    RectangleShape locations_background(Vector2f(150, unhidden_index * 35));
    locations_background.setPosition(5, 75 + saved_locations_count * 35 + 40);
    locations_background.setFillColor(Color::Black);

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
                bool is_graphic_activated = false;

                // checks if mouse is over the active location
                if (active_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                    active_location.set_is_activated(true);
                    is_graphic_activated = true;
                } else {
                    active_location.set_is_activated(false);
                }

                if (display_mode == "saved_locations" || display_mode == "locations") {
                    // checks if the mouse is over the user location
                    if (user_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        user_location.set_is_activated(true);
                        is_graphic_activated = true;
                    } else {
                        user_location.set_is_activated(false);
                    }

                    // checks if mouse is over any saved_locations
                    for (int i = 0; i < saved_locations.get_count(); i++) {
                        if (saved_locations.contains_point(i, Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            saved_locations.set_is_activated(i, true);
                            is_graphic_activated = true;
                        } else {
                            saved_locations.set_is_activated(i, false);
                        }
                    }

                    // checks if mouse is over the add location button
                    if (add_location_button.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        add_location_button.set_is_activated(true);
                        is_graphic_activated = true;
                    } else {
                        add_location_button.set_is_activated(false);
                    }

                    if (display_mode == "locations") {
                        // checks if the mouse is over any locations
                        for (int i = 0; i < 8; i++) {
                            if (!locations.get_is_hidden(i) && locations.contains_point(i, Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                                locations.set_is_activated(i, true);

                                is_graphic_activated = true;
                                break;
                            } else {
                                locations.set_is_activated(i, false);
                            }
                        }
                    }
                }

                if (is_graphic_activated) {
                    if (mouse_cursor_type != "hand") {
                        mouse_cursor.loadFromSystem(Cursor::Hand);
                        window.setMouseCursor(mouse_cursor);
                        mouse_cursor_type = "hand";
                    }
                } else if (mouse_cursor_type != "arrow") {
                    mouse_cursor.loadFromSystem(Cursor::Arrow);
                    window.setMouseCursor(mouse_cursor);
                    mouse_cursor_type = "arrow";
                }
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                bool is_graphic_clicked = false;

                // checks if the active location was clicked
                if (active_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (display_mode == "main") {
                        display_mode = "saved_locations";
                    } else if (display_mode == "saved_locations") {
                        display_mode = "main";
                    }
                    is_graphic_clicked = true;

                // checks if the user location was clicked
                } else if (!is_graphic_clicked && user_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
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
                    add_location_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                    is_user_location_active = true;

                    user_location.set_is_activated(false);
                    display_mode = "main";
                    is_graphic_clicked = true;
                } else if (!is_graphic_clicked && (display_mode == "saved_locations" || display_mode == "locations")) {
                    // checks if any of the saved locations were clicked
                    for (int i = 0; i < saved_locations.get_count(); i++) {
                        if (saved_locations.contains_point(i, Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            active_location.set_string(saved_locations.get_string(i));
                            active_location.set_coordinates(saved_locations.get_coordinates(i));
                            weather_data_set.set_location(saved_locations.get_coordinates(i));

                            result = weather_data_set.update_data();
                            if (result == -1) {
                                return -1;
                            }
                            start = time(0);

                            if (is_user_location_active) {
                                saved_locations_header.setPosition(12, 85);
                                saved_locations.set_position_mode(1);
                                add_location_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                is_user_location_active = false;
                            }

                            saved_locations.set_is_activated(i, false);
                            display_mode = "main";
                            is_graphic_clicked = true;
                            break;
                        }
                    }

                    // checks if add location button was clicked
                    if (!is_graphic_clicked && add_location_button.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (display_mode == "saved_locations") {
                            display_mode = "locations";
                        } else {
                            display_mode = "saved_locations";
                        }
                        is_graphic_clicked = true;
                    }

                    if (!is_graphic_clicked && display_mode == "locations") {
                        // checks if any of the locations were clicked
                        for (int i = 0; i < 8; i++) {
                            if (!locations.get_is_hidden(i) && locations.contains_point(i, Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                                locations.set_is_activated(i, false);
                                saved_locations.add_location(locations.get_location(i));
                                saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");

                                if (saved_locations.get_count() == 5) {
                                    display_mode = "saved_locations";
                                }

                                locations.set_is_hidden(i, true);
                                // adjust positions of other locations
                                int unhidden_index = 0;
                                for (int j = 0; j < 8; j++) {
                                    if (!locations.get_is_hidden(j)) {
                                        locations.set_position(j, Vector2f(10, 111 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                        unhidden_index++;
                                    }
                                }
                                locations_background.setSize(Vector2f(150, unhidden_index * 35));
                                locations_background.setPosition(5, 75 + saved_locations.get_count() * 35 + 40);

                                add_location_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));

                                is_graphic_clicked = true;
                                break;
                            }
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
            // if (is_user_location_active) {
            //     window.draw(user_location_icon);
            // }
        } else if (display_mode == "saved_locations" || "locations") {
            window.draw(saved_locations_header);
            window.draw(saved_locations);
            if (!is_user_location_active) {
                window.draw(user_location);
            }
            if (saved_locations.get_count() < 5) {
                window.draw(add_location_button);
            }
            if (display_mode == "locations") {
                window.draw(locations_background);
                window.draw(locations);
            }
        }

        window.display();
    }

    return 0;
}