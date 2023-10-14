#ifndef LOCATIONLIST_H
#define LOCATIONLIST_H

#include "Location.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class LocationList : public Drawable {
    protected:
        Location* locations;
        int size;
        int count;
    public:
        LocationList(int size);
        int get_size();
        int get_count();
        virtual void add_location(Location location);
        virtual void remove_location(int index);
        virtual void move_location(int original_index, int new_index);
        string get_string(int index);
        Coordinates get_coordinates(int index);
        void set_is_activated(int index, bool is_activated);
        ~LocationList();
        
        // int get_position(int index);
        // void set_position(int index, Vector2f position);
        void draw(RenderTarget& target, RenderStates states) const override;
};

#endif