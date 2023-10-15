#include "Graphic.h"
#include "WeatherGraphic.h"
#include "CurrentWeatherGraphic.h"
#include <SFML/Graphics.hpp>

CurrentWeatherGraphic::CurrentWeatherGraphic():WeatherGraphic() {}

CurrentWeatherGraphic::CurrentWeatherGraphic(Font& font, Vector2f position):WeatherGraphic(font, position) {
    temperature_text.setFont(font);
    temperature_text.setCharacterSize(45);
    temperature_text.setPosition(Vector2f(position.x + 180, position.y + 60));
}

void CurrentWeatherGraphic::set_icon(string icon_id) {
    WeatherGraphic::set_icon(icon_id);
    icon.setPosition(position);
}

int CurrentWeatherGraphic::get_temperature() {
    return temperature;
}

void CurrentWeatherGraphic::set_temperature(int temperature) {
    this->temperature = temperature;
    temperature_text.setString(to_string(temperature) + String(Uint32(176)));
}

void CurrentWeatherGraphic::set_position(Vector2f position) {
    this->position = position;
    icon.setPosition(position);
    temperature_text.setPosition(Vector2f(position.x + 180, position.y + 60));
}

void CurrentWeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
    target.draw(temperature_text);
}