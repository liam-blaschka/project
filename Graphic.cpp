#include "Graphic.h"
#include <SFML/Graphics.hpp>

Graphic::Graphic() {}

Graphic::Graphic(Font& font) {
    this->font = font;
}

void Graphic::set_position(Vector2f position) {
    this->position = position;
}

Vector2f Graphic::get_postion() {
    return position;
}

bool Graphic::contains_point(Vector2f point) {
    if (hitbox.contains(point)) {
        return true;
    }
    return false;
}