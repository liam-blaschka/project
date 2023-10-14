#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include "Coordinates.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    Font font;
    font.loadFromFile("calibri-regular.ttf");
    SavedLocations saved(5, font);

    for (int i = 0; i < saved.get_count(); i++) {
        cout << saved.get_string(i) << " " << saved.get_coordinates(i).x << " " << saved.get_coordinates(i).y << endl;
    }

    for (int i = 0; i < 4; i++) {
        string location_string;
        Coordinates coordinates;
        cout << "add location: ";
        cin >> location_string;
        cout << "lat coordinate: ";
        cin >> coordinates.x;
        cout << "long coordinate: ";
        cin >> coordinates.y;

        Location location(font, Vector2f(0, 0), location_string, coordinates);
        saved.add_location(location);
    }

    return 0;
}