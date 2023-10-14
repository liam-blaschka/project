#include "WeatherGraphic.h"
#include "Graphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

WeatherGraphic::WeatherGraphic(Font& font, Vector2f position, string icon_id):Graphic(font, position) {
    this->icon_id = icon_id;

    weather_icons.loadFromFile("weather_icons.png");
    weather_icons.setSmooth(true);

    if (icon_id == "01d" || icon_id == "01n") {
        // sunny
        icon = Sprite(weather_icons, IntRect(0, 128, 128, 128));
    } else if (icon_id == "02d" || icon_id == "02n") {
        // partly cloudy
        icon = Sprite(weather_icons, IntRect(0, 256, 128, 128));
    } else if (icon_id == "03d" || icon_id == "03n" || icon_id == "04d" || icon_id == "04n") {
        // cloudy
        icon = Sprite(weather_icons, IntRect(128, 128, 128, 128));
    } else if (icon_id == "09d" || icon_id == "09n") {
        // shower rain
        icon = Sprite(weather_icons, IntRect(128, 0, 128, 128));
    } else if (icon_id == "10d" || icon_id == "10n") {
        // rain
        icon = Sprite(weather_icons, IntRect(512, 256, 128, 128));
    } else if (icon_id == "11d" || icon_id == "11n") {
        // thunderstorm
        icon = Sprite(weather_icons, IntRect(512, 0, 128, 128));
    } else if (icon_id == "13d" || icon_id == "13n") {
        // snow
        icon = Sprite(weather_icons, IntRect(128, 384, 128, 128));
    } else if (icon_id == "50d" || icon_id == "50n") {
        // mist
        icon = Sprite(weather_icons, IntRect(512, 128, 128, 128));
    } else {
        // unknown
        icon = Sprite(weather_icons, IntRect(512, 384, 128, 128));
    }

    icon.setPosition(position);
}

// for testing
void WeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
}