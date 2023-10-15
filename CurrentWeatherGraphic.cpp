#include "Graphic.h"
#include "WeatherGraphic.h"
#include "CurrentWeatherGraphic.h"
#include <SFML/Graphics.hpp>

CurrentWeatherGraphic::CurrentWeatherGraphic(Font& font, Vector2f position, string icon_id, int temperature):WeatherGraphic(font, position, icon_id) {
    this->temperature = temperature;
    temperature_text.setFont(font);
    String degree_symbol = String::fromUtf32(176, 176);
    temperature_text.setString(to_string(temperature) + degree_symbol);
    temperature_text.setPosition(Vector2f(position.x + 130, position.y));
}

void CurrentWeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
    target.draw(temperature_text);
}