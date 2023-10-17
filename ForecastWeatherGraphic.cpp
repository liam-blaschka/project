#include "WeatherGraphic.h"
#include "ForecastWeatherGraphic.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

ForecastWeatherGraphic::ForecastWeatherGraphic():WeatherGraphic() {}

ForecastWeatherGraphic::ForecastWeatherGraphic(Font& font, Vector2f position, string day):WeatherGraphic(font, position) {
    day_text.setFont(font);
    day_text.setString(day);
    day_text.setCharacterSize(25);
    day_text.setPosition(position.x - 70, position.y + 10);

    temperature_text.setFont(font);
    String degree_symbol(Uint32(176));
    temperature_text.setCharacterSize(23);
    temperature_text.setPosition(position.x + 65, position.y + 11);

    rain_chance_text.setFont(font);
    rain_chance_text.setCharacterSize(23);
    rain_chance_text.setPosition(position.x + 280, position.y + 11);
    
    // modified image from source: https://www.flaticon.com/free-icon/raindrop_223476
    rain_drop_texture.loadFromFile("rain_drop_icon.png");
    rain_drop_texture.setSmooth(true);
}

void ForecastWeatherGraphic::set_icon(string icon_id) {
    WeatherGraphic::set_icon(icon_id);
    icon.setScale(Vector2f(0.3, 0.3));
    icon.setPosition(position);
}

int ForecastWeatherGraphic::get_min_temperature() {
    return min_temperature;
}

void ForecastWeatherGraphic::set_temperatures(int min_temperature, int max_temperature) {
    this->min_temperature = min_temperature;
    this->max_temperature = max_temperature;
    String degree_symbol(Uint32(176));
    temperature_text.setString("Min: " + to_string(min_temperature) + degree_symbol + "  Max: " + to_string(max_temperature) + degree_symbol);
}

int ForecastWeatherGraphic::get_rain_chance() {
    return rain_chance;
}

void ForecastWeatherGraphic::set_rain_chance(int rain_chance) {
    this->rain_chance = rain_chance;

    if (rain_chance > 0) {
        rain_chance_text.setString(to_string(rain_chance) + "%");
        rain_drop_icon = Sprite(rain_drop_texture);
        rain_drop_icon.setScale(Vector2f(0.6, 0.6));
        rain_drop_icon.setPosition(position.x + 255, position.y + 17);
    }
}

string ForecastWeatherGraphic::get_day() {
    return day;
}

void ForecastWeatherGraphic::set_day(string day) {
    this->day = day;
    day_text.setString(day);
}

void ForecastWeatherGraphic::draw(RenderTarget& target, RenderStates states) const {
    target.draw(icon);
    target.draw(day_text);
    target.draw(temperature_text);
    if (rain_chance > 0) {
        target.draw(rain_drop_icon);
        target.draw(rain_chance_text);
    }
}