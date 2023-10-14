#include "WeatherData.h"
#include "CurrentWeatherData.h"
#include "ForecastWeatherData.h"
#include "WeatherDataSet.h"
#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include "User.h"
#include <ctime>
#include <SFML/Graphics.hpp>

#include <iostream>
#include "Coordinates.h"

using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(550, 325), "Weather", Style::Titlebar | Style::Close);
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
    // text.setStyle(Text::Bold)

    Location location(font, user_location_string, user_coordinates);

    WeatherDataSet weather_data_set(user_coordinates);

    int result = weather_data_set.update_data();
    if (result == -1) {
        return -1;
    }

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
        window.draw(location);
        // window.draw(text);
        window.display();
    }

    return 0;
}