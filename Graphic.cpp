#include "Graphic.h"
#include <SFML/Graphics.hpp>

Graphic::Graphic() {}

Graphic::Graphic(Font& font, Vector2f position) {
    this->font = font;
    this->position = position;
}

void Graphic::set_position(Vector2f position) {
    this->position = position;
}

Vector2f Graphic::get_postion() {
    return position;
}

bool Graphic::contains_point(Vector2f point) {
    return hitbox.contains(point);
}