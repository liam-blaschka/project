#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include "Coordinates.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

SavedLocations::SavedLocations(int size, Font& font):LocationList(size) {
    ifstream file("saved_locations.csv");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            string location_string;
            Coordinates location_coordinates;
            stringstream line_stream(line);
            string column;
            int i = 0;
            while (getline(line_stream, column, ',')) {
                switch (i) {
                    case 0:
                        location_string = column;
                        break;
                    case 1:
                        location_coordinates.x = stod(column);
                        break;
                    case 2:
                        location_coordinates.y = stod(column);
                        break;
                }
                i++;
            }
            locations[count] = Location(font, Vector2f(10, 75 + (35 * count)), location_string, location_coordinates);
            count++;
        }
    } else {
        ofstream file("saved_locations.csv");
        count = 0;
    }
    file.close();

    position_mode = 0;
}

void SavedLocations::add_location(Location location) {
    if (count < size) {
        ofstream file("saved_locations.csv", std::ios::app);
        file << location.get_string() << "," << location.get_coordinates().x << "," << location.get_coordinates().y << "\n";
        file.close();
        if (position_mode == 0) {
            location.set_position(Vector2f(10, 75 + (35 * count)));
        } else {
            location.set_position(Vector2f(10, 110 + (35 * count)));
        }

        LocationList::add_location(location);
    }
}

void SavedLocations::remove_location(int index) {
    ifstream file_old("saved_locations.csv");
    ofstream file_new("new_saved_locations.csv", std::ios::app);

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

    remove("saved_locations.csv");
    rename("new_saved_locations.csv", "saved_locations.csv");

    LocationList::remove_location(index);
}

void SavedLocations::move_location(int original_index, int new_index) {
    LocationList::move_location(original_index, new_index);

    remove("saved_locations.csv");

    ofstream file("saved_locations.csv", std::ios::app);
    for (int i = 0; i < count; i++) {
        file << locations[i].get_string() << "," << locations[i].get_coordinates().x << "," << locations[i].get_coordinates().y << "\n";
    }

    file.close();
}

int SavedLocations::get_position_mode() {
    return position_mode;
}

void SavedLocations::set_position_mode(int position_mode) {
    if (this->position_mode != position_mode) {
        this->position_mode = position_mode;
        if (position_mode == 0) {
            for (int i = 0 ; i < count; i++) {
                locations[i].set_position(Vector2f(10, 75 + (35 * i)));
            }
        } else if (position_mode == 1) {
            for (int i = 0 ; i < count; i++) {
                locations[i].set_position(Vector2f(10, 110 + (35 * i)));
            }
        }
    }
}