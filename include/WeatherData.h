#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include "Coordinates.h"
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
using json = nlohmann::json;

// abstract class to represent a common interface for related classes
class WeatherData : public Drawable {
    protected:
        string icon_id;
        Coordinates location;

    public:
        WeatherData();
        WeatherData(Coordinates location);
        string get_icon_id();

        // pure virtual function
        virtual void update_data(json data) = 0;
        // virtual functions
        virtual int get_temperature() { return 0; }
        virtual void set_temperature(int temperature) {}
        virtual int get_rain_chance() { return 0; }
        virtual void set_rain_chance(int rain_chance) {}
        virtual int get_max_temperature() { return 0; }
        virtual void set_max_temperature(int max_temperature) {}
        virtual int get_min_temperature() { return 0; }
        virtual void set_min_temperature(int min_temperature) {}
        virtual string get_day() { return ""; }
        virtual void set_day(string day) {}
        virtual void draw(RenderTarget& target, RenderStates states) const = 0;

        // virtual destructor
        virtual ~WeatherData() = 0;
};

#endif