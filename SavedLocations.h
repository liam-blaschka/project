#ifndef SAVEDLOCATIONS_H
#define SAVEDLOCATIONS_H

#include "Location.h"
#include "LocationList.h"
#include <string>

#include <iostream>

using namespace std;

class SavedLocations : public LocationList {
    private:
        Font font;
        int position_mode;
    public:
        SavedLocations(int size, Font& font);
        void add_location(Location location) override;
        void remove_location(int index) override;
        void move_location(int original_index, int new_index) override;
        void set_position_mode(int position_mode);
};

#endif