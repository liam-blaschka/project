#ifndef BUTTON_H
#define BUTTON_H

#include "Graphic.h"
#include <SFML/Graphics.hpp>

// class for button graphic
class Button : public Graphic {
    private:
        Sprite icon;
        RectangleShape activated_background;
        bool is_activated;
    public:
        Button(Font& font, Vector2f position, Sprite icon);
        void set_is_activated(bool is_activated);
        bool contains_point(Vector2f point);
        void set_position(Vector2f position) override;
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif