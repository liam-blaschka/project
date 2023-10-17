#include "Location.h"
#include "Coordinates.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

Location::Location(Font& font, Vector2f position, string location, Coordinates coordinates) {
    this->location = location;
    this->coordinates = coordinates;
    this->position = position;
    is_hidden = false;
    text_style = Text::Regular;

    text.setFont(font);
    text.setString(location);
    text.setFillColor(Color::White);
    text.setPosition(position);

    hitbox = text.getGlobalBounds();
}

Location::Location() {}

string Location::get_string() {
    return location;
}

void Location::set_string(string location) {
    this->location = location;
    text.setString(location);
}

void Location::set_style(Uint32 style) {
    text_style = style;
    text.setStyle(style);
    hitbox = text.getGlobalBounds();
}

Coordinates Location::get_coordinates() {
    return coordinates;
}

void Location::set_coordinates(Coordinates coordinates) {
    this->coordinates = coordinates;
}

void Location::activate(Uint32 style) {
    this->is_activated = true;
    text.setStyle(text_style | style);
}

void Location::deactivate() {
    this->is_activated = false;
    text.setStyle(text_style);
}

void Location::set_position(Vector2f position) {
    this->position = position;
    text.setPosition(position);
    hitbox = text.getGlobalBounds();
}

Vector2f Location::get_position() {
    return position;
}

FloatRect Location::get_hitbox() {
    return hitbox;
}

bool Location::get_is_hidden() {
    return is_hidden;
}

void Location::set_is_hidden(bool is_hidden) {
    this->is_hidden = is_hidden;
}

void Location::draw(RenderTarget& target, RenderStates states) const {
    target.draw(text);
}