#ifndef CURRENTWEATHERGRAPHIC_H
#define CURRENTWEATHERGRAPHIC_H

#include "Graphic.h"
#include "WeatherGraphic.h"
#include <SFML/Graphics.hpp>

// represents the weather graphic for the current weather data
class CurrentWeatherGraphic : public WeatherGraphic {
    private:
        int temperature;
    public:
        // constructors
        CurrentWeatherGraphic();
        CurrentWeatherGraphic(Font& font, Vector2f position);

        // sets the icon of the current weather graphic according to the inputted icon_id
        void set_icon(string icon_id) override;

        // returns the temperature
        int get_temperature();

        // sets the temperature of the graphic to the paramater value
        void set_temperature(int temperature);
        
        // sets the position of the graphic in the window
        void set_position(Vector2f postion) override;

        // draws the graphic to the window
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif