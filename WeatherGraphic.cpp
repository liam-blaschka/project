#include "WeatherGraphic.h"
#include "Graphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

WeatherGraphic::WeatherGraphic(Font& font, Vector2f position, string icon_id):Graphic(font, position) {
    this->icon_id = icon_id;

    weather_icons.loadFromFile("Untitled.png");
    weather_icons.setSmooth(true);

    if (icon_id == "01d" || icon_id == "01n") {
        // sunny
        icon = Sprite(weather_icons, IntRect(0, 196, 196, 196));
    } else if (icon_id == "02d" || icon_id == "02n") {
        // partly cloudy
        icon = Sprite(weather_icons, IntRect(0, 384, 196, 196));
    } else if (icon_id == "03d" || icon_id == "03n" || icon_id == "04d" || icon_id == "04n") {
        // cloudy
        icon = Sprite(weather_icons, IntRect(196, 196, 196, 196));
    } else if (icon_id == "09d" || icon_id == "09n") {
        // shower rain
        icon = Sprite(weather_icons, IntRect(196, 0, 196, 196));
    } else if (icon_id == "10d" || icon_id == "10n") {
        // rain
        icon = Sprite(weather_icons, IntRect(512, 384, 196, 196));
    } else if (icon_id == "11d" || icon_id == "11n") {
        // thunderstorm
        icon = Sprite(weather_icons, IntRect(512, 0, 196, 196));
    } else if (icon_id == "13d" || icon_id == "13n") {
        // snow
        icon = Sprite(weather_icons, IntRect(196, 576, 196, 196));
    } else if (icon_id == "50d" || icon_id == "50n") {
        // mist
        icon = Sprite(weather_icons, IntRect(576, 196, 196, 196));
    } else {
        // unknown
        icon = Sprite(weather_icons, IntRect(512, 576, 196, 196));
    }

    icon.setPosition(position);
}

// for testing
void WeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
}