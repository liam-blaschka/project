#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

// common framework base class for all graphically represented classes (abstract class)
class Graphic : public Drawable {
    protected:
        Font font;
        Vector2f position;
        FloatRect hitbox;
        RectangleShape hitbox_outline;
    public:
        // constructors
        Graphic();
        Graphic(Font& font, Vector2f position);

        // returns the graphic's position in the window
        Vector2f get_postion();

        // sets the position of the graphic in the window
        virtual void set_position(Vector2f position);

        // returns bool of whether a point of the window is in the graphic, point could be mouse position
        bool contains_point(Vector2f point);

        // draws the graphic onto the window (pure virtual function)
        virtual void draw(RenderTarget&, RenderStates states) const = 0;
};

#endif