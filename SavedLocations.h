#ifndef SAVEDLOCATIONS_H
#define SAVEDLOCATIONS_H

#include "Location.h"
#include "LocationList.h"
#include <string>

using namespace std;

class SavedLocations : public LocationList {
    public:
        SavedLocations(int size);
        void add_location(Location location) override;
        void remove_location(int index) override;
        void move_location(int original_index, int new_index) override;
};

#endif