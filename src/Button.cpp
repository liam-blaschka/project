#include "Button.h"
#include "Graphic.h"
#include <SFML/Graphics.hpp>

Button::Button(Font& font, Vector2f position, Sprite icon):Graphic(font, position) {
    this->icon = icon;
    this->icon.setPosition(position);
    FloatRect icon_bounds = icon.getGlobalBounds();
    activated_background = RectangleShape(Vector2f(icon_bounds.width, icon_bounds.height));
    activated_background.setPosition(position);
    activated_background.setFillColor(Color(36, 152, 215));
}

void Button::set_is_activated(bool is_activated) {
    this->is_activated = is_activated;
}

bool Button::contains_point(Vector2f point) {
    return icon.getGlobalBounds().contains(point);
}

void Button::set_position(Vector2f position) {
    this->position = position;
    icon.setPosition(position);
    activated_background.setPosition(position);
}

void Button::draw(RenderTarget& target, RenderStates states) const {
    if (is_activated) {
        target.draw(activated_background);
    }
    target.draw(icon);
}
