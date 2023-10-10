#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include <string>
#include <fstream>

using namespace std;

SavedLocations::SavedLocations(int size):LocationList(size) {
    ifstream file("saved_locations.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            locations[count] = Location(line);
            count++;
        }
    } else {
        ofstream file("saved_locations.txt");
        count = 0;
    }
    file.close();
}

void SavedLocations::add_location(Location location) {
    if (count < size) {
        ofstream file("saved_locations.txt", std::ios::app);
        file << location.get_string() << "\n";
        file.close();

        LocationList::add_location(location);
    }
}

void SavedLocations::remove_location(int index) {
    ifstream file_old("saved_locations.txt");
    ofstream file_new("new_saved_locations.txt", std::ios::app);

    string line;
    int i = 0;
    while (getline(file_old, line)) {
        if (i != index) {
            file_new << line << "\n";
        }

        i++;
    }

    file_old.close();
    file_new.close();

    remove("saved_locations.txt");
    rename("new_saved_locations.txt", "saved_locations.txt");

    LocationList::remove_location(index);
}

void SavedLocations::move_location(int original_index, int new_index) {
    LocationList::move_location(original_index, new_index);

    remove("saved_locations.txt");

    ofstream file("saved_locations.txt", std::ios::app);
    for (int i = 0; i < count; i++) {
        file << locations[i].get_string() << "\n";
    }

    file.close();
}