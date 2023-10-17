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
#include <ctime>
#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(425, 550), "Weather", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);

    Cursor mouse_cursor;
    string mouse_cursor_type = "arrow";

    // macos included font
    Font font;
    font.loadFromFile("Arial.ttf");

    User user = User();
    string user_location_string = user.get_location_string();
    Coordinates user_coordinates = user.get_location_coordinates();

    Location user_location(font, Vector2f(10, 45), user_location_string, user_coordinates);

    Location active_location(font, Vector2f(10, 3), user_location_string, user_coordinates);
    bool is_user_location_active = true;

    // modified image from source: https://www.flaticon.com/free-icon/location_2838912
    Texture location_icon_texture;
    location_icon_texture.loadFromFile("location_icon.png");
    location_icon_texture.setSmooth(true);
    Sprite user_location_icon(location_icon_texture);
    user_location_icon.setScale(0.9, 0.9);
    user_location_icon.setPosition(active_location.get_hitbox().width + 25, 5);

    active_location.set_style(Text::Bold);

    SavedLocations saved_locations(5, font);
    Text saved_locations_header;
    saved_locations_header.setFont(font);
    saved_locations_header.setCharacterSize(23);
    saved_locations_header.setPosition(12, 50);
    saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");

    RectangleShape position_lines[6];
    FloatRect position_line_hitboxes[6];
    for (int i = 0; i < 6; i++) {
        position_lines[i] = RectangleShape(Vector2f(200, 4));
        position_lines[i].setPosition(0, 76 + (35 * i));
        position_lines[i].setFillColor(Color(36, 152, 215));

        position_line_hitboxes[i] = FloatRect(0, 76 + (35 * i), 200, 4);
    }
    int activated_line = -1;

    Texture add_location_icon_texture;
    add_location_icon_texture.loadFromFile("add_icon.png");
    add_location_icon_texture.setSmooth(true);
    Button add_location_button(font, Vector2f(8, 75 + saved_locations.get_count() * 36), Sprite(add_location_icon_texture));

    // image is modified from source: https://www.freepik.com/icon/garbage_246708
    Texture bin_icon_texture;
    bin_icon_texture.loadFromFile("bin_icon.png");
    bin_icon_texture.setSmooth(true);
    Button bin_button(font, Vector2f(0, 0), Sprite(bin_icon_texture));
    if (saved_locations.get_count() < 5) {
        bin_button.set_position(Vector2f(50, 75 + saved_locations.get_count() * 36));
    } else {
        bin_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
    }

    bool is_location_delete_mode = false;

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
        for (int j = 0; j < saved_locations.get_count(); j++) {
            if (locations.get_string(i) == saved_locations.get_string(j)) {
                locations.set_is_hidden(i, true);
                break;
            }
        }

        if (!locations.get_is_hidden(i)) {
            locations.set_position(i, Vector2f(10, 111 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
            unhidden_index++;
        }
    }

    RectangleShape locations_background(Vector2f(150, unhidden_index * 35));
    locations_background.setPosition(5, 115 + saved_locations.get_count() * 35);
    locations_background.setFillColor(Color::Black);

    WeatherDataSet weather_data_set(user_coordinates, font);

    int result = weather_data_set.update_data();
    if (result == -1) {
        return -1;
    }

    string display_mode = "main";

    time_t start = time(0);
    bool is_mouse_pressed = false;
    bool is_dragging = false;
    Vector2f initial_mouse_position(0, 0);
    Vector2f initial_location_position(0, 0);
    int dragged_location;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                window.close();
            } else if (event.type == Event::LostFocus || event.type == Event::MouseLeft) {
                if (is_dragging) {
                    saved_locations.set_position(dragged_location, initial_location_position);
                    activated_line = -1;
                    is_dragging = false;
                }
                is_mouse_pressed = false;
            } else if (event.type == Event::GainedFocus) {
                if (mouse_cursor_type != "arrow") {
                    mouse_cursor.loadFromSystem(Cursor::Arrow);
                    window.setMouseCursor(mouse_cursor);
                    mouse_cursor_type = "arrow";
                }
            } else if (event.type == Event::MouseMoved) {
                bool is_graphic_activated = false;

                if (display_mode != "main" && is_mouse_pressed && !is_dragging) {
                    for (int i = 0; i < saved_locations.get_count(); i++) {
                        if (saved_locations.contains_point(i, initial_mouse_position) && (abs(event.mouseMove.x - initial_mouse_position.x) > 3 || abs(event.mouseMove.y - initial_mouse_position.y))) {
                            mouse_cursor.loadFromSystem(Cursor::Arrow);
                            window.setMouseCursor(mouse_cursor);
                            mouse_cursor_type = "arrow";

                            initial_location_position = saved_locations.get_position(i);
                            saved_locations.deactivate(i);
                            dragged_location = i;
                            is_dragging = true;
                        }
                    }
                } else if (!is_dragging) {
                    // checks if mouse is over the active location
                    if (active_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                        active_location.activate(Text::Underlined);
                        is_graphic_activated = true;
                    } else {
                        active_location.deactivate();
                    }

                    if (display_mode == "saved_locations" || display_mode == "locations") {
                        // checks if the mouse is over the user location
                        if (!is_user_location_active && user_location.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            user_location.activate(Text::Underlined);
                            is_graphic_activated = true;
                        } else {
                            user_location.deactivate();
                        }

                        // checks if mouse is over any saved_locations
                        for (int i = 0; i < saved_locations.get_count(); i++) {
                            if (saved_locations.contains_point(i, Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                                if (is_location_delete_mode) {
                                    saved_locations.activate(i, Text::StrikeThrough);
                                } else {
                                    saved_locations.activate(i, Text::Underlined);
                                }
                                is_graphic_activated = true;
                            } else {
                                saved_locations.deactivate(i);
                            }
                        }

                        // checks if mouse is over the add location button
                        if (saved_locations.get_count() < 5 && add_location_button.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            add_location_button.set_is_activated(true);
                            is_graphic_activated = true;
                        } else if (display_mode != "locations") {
                            add_location_button.set_is_activated(false);
                        }

                        // checks if the mouse is over the bin button
                        if (saved_locations.get_count() > 0 && bin_button.contains_point(Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                            bin_button.set_is_activated(true);
                            is_graphic_activated = true;
                        } else if (!is_location_delete_mode) {
                            bin_button.set_is_activated(false);
                        }

                        if (display_mode == "locations") {
                            // checks if the mouse is over any locations
                            for (int i = 0; i < 8; i++) {
                                if (!locations.get_is_hidden(i) && locations.contains_point(i, Vector2f(event.mouseMove.x, event.mouseMove.y))) {
                                    locations.activate(i, Text::Underlined);

                                    is_graphic_activated = true;
                                    break;
                                } else {
                                    locations.deactivate(i);
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
                }

                if (is_dragging) {
                    // move saved location with mouse
                    saved_locations.set_position(dragged_location, Vector2f(initial_location_position.x + event.mouseMove.x - initial_mouse_position.x,
                                                                            initial_location_position.y + event.mouseMove.y - initial_mouse_position.y));
                    // check if saved location is over position guide line
                    activated_line = -1;
                    for (int i = 0; i < 6; i++) {
                        if (position_line_hitboxes[i].intersects(saved_locations.get_hitbox(dragged_location))) {
                            if (i <= saved_locations.get_count() && i != dragged_location && i != dragged_location + 1) {
                                activated_line = i;
                            }
                        }
                    }
                }
            } else if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                is_mouse_pressed = true;
                initial_mouse_position = Vector2f(event.mouseButton.x, event.mouseButton.y);
            } else if (event.type == Event::MouseButtonReleased) {
                if (is_dragging) {
                    if (activated_line > -1 && activated_line <= saved_locations.get_count()) {
                        if (activated_line > dragged_location) {
                            saved_locations.move_location(dragged_location, activated_line - 1);
                        } else {
                            saved_locations.move_location(dragged_location, activated_line);
                        }
                        // adjust graphical position
                        if (is_user_location_active) {
                            saved_locations.set_position_mode(0);
                        } else {
                            saved_locations.set_position_mode(1);
                        }
                    } else {
                        saved_locations.set_position(dragged_location, initial_location_position);
                    }

                    is_dragging = false;
                } else {
                    bool is_graphic_clicked = false;

                    // checks if the active location was clicked
                    if (active_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        if (display_mode == "main") {
                            display_mode = "saved_locations";
                        } else {
                            display_mode = "main";
                            add_location_button.set_is_activated(false);
                            bin_button.set_is_activated(false);
                        }
                        is_graphic_clicked = true;

                    // checks if the user location was clicked
                    } else if (!is_graphic_clicked && !is_user_location_active && user_location.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        active_location.set_string(user_location_string);
                        active_location.set_coordinates(user_coordinates);
                        weather_data_set.set_location(user_coordinates);

                        result = weather_data_set.update_data();
                        if (result == -1) {
                            return -1;
                        }
                        start = time(0);

                        saved_locations_header.setPosition(12, 50);
                        user_location_icon.setPosition(active_location.get_hitbox().width + 25, 5);
                        saved_locations.set_position_mode(0);
                        add_location_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                        if (saved_locations.get_count() < 5) {
                            bin_button.set_position(Vector2f(50, 75 + saved_locations.get_count() * 36));
                        } else {
                            bin_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                        }
                        locations_background.setPosition(5, 115 + saved_locations.get_count() * 35);
                        int unhidden_index = 0;
                        for (int i = 0; i < 8; i++) {
                            if (!locations.get_is_hidden(i)) {
                                locations.set_position(i, Vector2f(10, 111 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                unhidden_index++;
                            }
                        }
                        // adjust position line positions
                        for (int i = 0; i < 6; i++) {
                            position_lines[i].setPosition(0, 76 + (35 * i));
                            position_line_hitboxes[i] = FloatRect(0, 76 + (35 * i), 200, 4);
                        }

                        is_user_location_active = true;

                        user_location.deactivate();
                        display_mode = "main";
                        add_location_button.set_is_activated(false);
                        bin_button.set_is_activated(false);
                        is_graphic_clicked = true;
                    } else if (!is_graphic_clicked && (display_mode == "saved_locations" || display_mode == "locations")) {
                        // checks if any of the saved locations were clicked
                        for (int i = 0; i < saved_locations.get_count(); i++) {
                            if (saved_locations.contains_point(i, Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                                // if location is being removed
                                if (is_location_delete_mode) {
                                    string removed_location = saved_locations.get_string(i);
                                    saved_locations.remove_location(i);
                                    saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");
                                    int unhidden_index = 0;
                                    for (int j = 0; j < 8; j++) {
                                        for (int k = 0; k < saved_locations.get_count(); k++) {
                                            if (locations.get_string(j) == removed_location) {
                                                locations.set_is_hidden(j, false);
                                            }
                                        }
                                        // adjust locations positions
                                        if (!locations.get_is_hidden(j)) {
                                            if (is_user_location_active) {
                                                locations.set_position(j, Vector2f(10, 111 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                            } else {
                                                locations.set_position(j, Vector2f(10, 146 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                            }
                                            unhidden_index++;
                                        }
                                    }

                                    // adjust positions
                                    locations_background.setSize(Vector2f(150, unhidden_index * 35));
                                    if (is_user_location_active) {
                                        locations_background.setPosition(5, 115 + saved_locations.get_count() * 35);
                                        add_location_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                                        bin_button.set_position(Vector2f(50, 75 + saved_locations.get_count() * 36));
                                        saved_locations.set_position_mode(0);
                                    }  else {
                                        locations_background.setPosition(5, 150 + saved_locations.get_count() * 35);
                                        add_location_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                        bin_button.set_position(Vector2f(50, 110 + saved_locations.get_count() * 36));
                                        saved_locations.set_position_mode(1);
                                    }

                                // if location is being selected
                                } else {
                                    active_location.set_string(saved_locations.get_string(i));
                                    active_location.set_coordinates(saved_locations.get_coordinates(i));
                                    weather_data_set.set_location(saved_locations.get_coordinates(i));

                                    result = weather_data_set.update_data();
                                    if (result == -1) {
                                        return -1;
                                    }
                                    start = time(0);

                                    if (is_user_location_active) {
                                        // adjust the saved locations and buttons positions
                                        saved_locations_header.setPosition(12, 85);
                                        user_location_icon.setPosition(user_location.get_hitbox().width + 15, 50);
                                        saved_locations.set_position_mode(1);
                                        add_location_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                        if (saved_locations.get_count() < 5) {
                                            bin_button.set_position(Vector2f(50, 110 + saved_locations.get_count() * 36));
                                        } else {
                                            bin_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                        }
                                        locations_background.setPosition(5, 150 + saved_locations.get_count() * 35);
                                        // adjust the locations position
                                        int unhidden_index = 0;
                                        for (int j = 0; j < 8; j++) {
                                            if (!locations.get_is_hidden(j)) {
                                                locations.set_position(j, Vector2f(10, 146 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                                unhidden_index++;
                                            }
                                        }
                                        // adjust the position line guides positions
                                        for (int i = 0; i < 6; i++) {
                                            position_lines[i].setPosition(0, 111 + (35 * i));
                                            position_line_hitboxes[i] = FloatRect(0, 111 + (35 * i), 200, 4);
                                        }

                                        is_user_location_active = false;
                                    }

                                    saved_locations.deactivate(i);
                                    display_mode = "main";
                                    break;
                                }
                                is_graphic_clicked = true;
                            }
                        }

                        // checks if add location button was clicked
                        if (!is_graphic_clicked && saved_locations.get_count() < 5 && add_location_button.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            if (display_mode == "saved_locations") {
                                display_mode = "locations";
                            } else {
                                display_mode = "saved_locations";
                            }
                            is_location_delete_mode = false;
                            bin_button.set_is_activated(false);
                            is_graphic_clicked = true;
                        }

                        // checks if bin button was clicked
                        if (!is_graphic_clicked && saved_locations.get_count() > 0) {
                            if (bin_button.contains_point(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                                if (is_location_delete_mode) {
                                    is_location_delete_mode = false;
                                } else {
                                    is_location_delete_mode = true;
                                }

                                if (display_mode == "locations") {
                                    display_mode = "saved_locations";
                                }
                                add_location_button.set_is_activated(false);
                                is_graphic_clicked = true;
                            }
                        }

                        if (!is_graphic_clicked && display_mode == "locations") {
                            // checks if any of the locations were clicked
                            for (int i = 0; i < 8; i++) {
                                if (!locations.get_is_hidden(i) && locations.contains_point(i, Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                                    locations.deactivate(i);
                                    saved_locations.add_location(locations.get_location(i));
                                    saved_locations_header.setString("Saved locations " + to_string(saved_locations.get_count()) + "/5:");

                                    if (saved_locations.get_count() == 5) {
                                        display_mode = "saved_locations";
                                    }

                                    locations.set_is_hidden(i, true);

                                    // adjust positions
                                    int unhidden_index = 0;
                                    if (is_user_location_active) {
                                        // adjust the location positions
                                        for (int j = 0; j < 8; j++) {
                                            if (!locations.get_is_hidden(j)) {
                                                locations.set_position(j, Vector2f(10, 111 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                                unhidden_index++;
                                            }
                                        }
                                        locations_background.setPosition(5, 115 + saved_locations.get_count() * 35);
                                        add_location_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                                        // adjust button positions
                                        if (saved_locations.get_count() < 5) {
                                            bin_button.set_position(Vector2f(50, 75 + saved_locations.get_count() * 36));
                                        } else {
                                            bin_button.set_position(Vector2f(8, 75 + saved_locations.get_count() * 36));
                                        }
                                    } else {
                                        // adjust the locations positions
                                        for (int j = 0; j < 8; j++) {
                                            if (!locations.get_is_hidden(j)) {
                                                locations.set_position(j, Vector2f(10, 146 + (saved_locations.get_count() * 35) + (unhidden_index * 35)));
                                                unhidden_index++;
                                            }
                                        }
                                        locations_background.setPosition(5, 150 + saved_locations.get_count() * 35);
                                        add_location_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                        // adjust the button positions
                                        if (saved_locations.get_count() < 5) {
                                            bin_button.set_position(Vector2f(50, 110 + saved_locations.get_count() * 36));
                                        } else {
                                            bin_button.set_position(Vector2f(8, 110 + saved_locations.get_count() * 36));
                                        }
                                    }
                                    locations_background.setSize(Vector2f(150, unhidden_index * 35));
                                    
                                    is_graphic_clicked = true;
                                    break;
                                }
                            }
                        }
                    }
                }
                is_mouse_pressed = false;
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
            if (is_user_location_active) {
                window.draw(user_location_icon);
            }
        } else if (display_mode == "saved_locations" || "locations") {
            window.draw(saved_locations_header);
            window.draw(saved_locations);
            window.draw(user_location_icon);

            if (!is_user_location_active) {
                window.draw(user_location);
            }
            if (saved_locations.get_count() < 5) {
                window.draw(add_location_button);
            }
            if (saved_locations.get_count() > 0) {
                window.draw(bin_button);
            }
            if (display_mode == "locations") {
                window.draw(locations_background);
                window.draw(locations);
            }
        }

        if (is_dragging && activated_line > -1) {
            window.draw(position_lines[activated_line]);
        }

        window.display();
    }

    return 0;
}