#include "LocationList.h"
#include "Location.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

LocationList::LocationList(int size) {
    this-> size = size;
    locations = new Location[size];
    count = 0;
}

int LocationList::get_size() {
    return size;
}

int LocationList::get_count() {
    return count;
}

void LocationList::add_location(Location location) {
    if (count < size){
        locations[count] = location;
        count++;
    }
}

void LocationList::remove_location(int index) {
    if (count > index) {
        locations[index] = Location();
        count--;

        for (int i = index; i < count; i++) {
            locations[i] = locations[i + 1];
        }
    }
}

void LocationList::move_location(int original_index, int new_index) {
    if (new_index < count) {
        Location location = locations[original_index];
        
        if (new_index > original_index) {
            // list shifts down
            for (int i = original_index; i < count - 1; i++) {
                locations[i] = locations[i + 1];
            }
        } else {
            // list shifts up
            for (int i = original_index; i < new_index; i++) {
                locations[i] = locations[i - 1];
            }
        }
        locations[new_index] = location;
    }
}

string LocationList::get_string(int index) {
    return locations[index].get_string();
}

Coordinates LocationList::get_coordinates(int index) {
    return locations[index].get_coordinates();
}

void LocationList::set_is_activated(int index, bool is_activated) {
    locations[index].set_is_activated(is_activated);
}

void LocationList::draw(RenderTarget& target, RenderStates states) const {
    for (int i = 0; i < count; i++) {
        target.draw(locations[i]);
    }
}

LocationList::~LocationList() {
    delete[] locations;
}

// not complete