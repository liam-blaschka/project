#include "Graphic.h"
#include "WeatherGraphic.h"
#include "CurrentWeatherGraphic.h"
#include <SFML/Graphics.hpp>

CurrentWeatherGraphic::CurrentWeatherGraphic(Font& font, Vector2f position, string icon_id, int temperature):WeatherGraphic(font, position, icon_id) {
    this->temperature = temperature;
    temperature_text.setFont(font);
    temperature_text.setString(to_string(temperature) + String(Uint32(176)));
    temperature_text.setCharacterSize(45);
    // temperature_text.setStyle(Text::Bold);
    temperature_text.setPosition(Vector2f(position.x + 170, position.y + 60));
}

void CurrentWeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    // target.draw(rectangle);

    target.draw(icon);
    target.draw(temperature_text);
}