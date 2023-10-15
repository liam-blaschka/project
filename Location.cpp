#include "Location.h"
#include "Coordinates.h"
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

Location::Location(Font& font, Vector2f position, string location, Coordinates coordinates) {
    this->location = location;
    this->coordinates = coordinates;
    this->position = position;

    text.setFont(font);
    text.setString(location);
    text.setFillColor(Color::White);
    text.setPosition(position);

    hitbox = FloatRect(Vector2f(position.x, position.y + 10), text.getGlobalBounds().getSize());

    // hitbox_outline = RectangleShape(text.getGlobalBounds().getSize());
    // hitbox_outline.setPosition(position.x, position.y + 10);
    // hitbox_outline.setFillColor(Color::Black);
}

Location::Location() {}

string Location::get_string() {
    return location;
}

void Location::set_string(string location) {
    this->location = location;
}

void Location::set_style(Uint32 style) {
    text.setStyle(style);
    hitbox = FloatRect(Vector2f(position.x, position.y + 10), text.getGlobalBounds().getSize());

    // hitbox_outline = RectangleShape(text.getGlobalBounds().getSize());
    // hitbox_outline.setPosition(position.x, position.y + 10);
    // hitbox_outline.setFillColor(Color::Black);
}

Coordinates Location::get_coordinates() {
    return coordinates;
}

void Location::set_coordinates(Coordinates coordinates) {
    this->coordinates = coordinates;
}

void Location::set_is_activated(bool is_activated) {
    this->is_activated = is_activated;
}

void Location::set_position(Vector2f position) {
    this->position = position;
    text.setPosition(position);
}

Vector2f Location::get_position() {
    return position;
}

void Location::draw(RenderTarget& target, RenderStates states) const {
    // target.draw(hitbox_outline);
    target.draw(text);
}