#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Graphic : public Drawable {
    protected:
        Font font;
        Vector2f position;
        FloatRect hitbox;
    public:
        Graphic();
        Graphic(Font& font);
        Vector2f get_postion();
        void set_position(Vector2f position);
        bool contains_point(Vector2f point);
        virtual void draw(RenderTarget&, RenderStates states) const = 0;
};

#endif