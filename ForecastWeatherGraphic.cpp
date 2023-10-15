#include "WeatherGraphic.h"
#include "ForecastWeatherGraphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

ForecastWeatherGraphic::ForecastWeatherGraphic(Font& font, Vector2f position, string icon_id, int min_temperature, int max_temperature, int rain_chance, string day):WeatherGraphic(font, position, icon_id) {
    icon.setScale(Vector2f(0.5, 0.5));

    day_text.setFont(font);
    day_text.setString(day);
    day_text.setCharacterSize(25);
    day_text.setPosition(Vector2f(position.x - 10, position.y + 20));

    temperature_text.setFont(font);
    String degree_symbol(Uint32(176));
    temperature_text.setString("Min: " + to_string(min_temperature) + degree_symbol + ", Max: " + to_string(max_temperature) + degree_symbol);
    temperature_text.setCharacterSize(25);
    temperature_text.setPosition(Vector2f(position.x + 10, position.y + 20));
    
}

void ForecastWeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
    target.draw(day_text);
    target.draw(temperature_text);
}