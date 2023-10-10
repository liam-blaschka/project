#include "Location.h"
#include "LocationList.h"
#include "SavedLocations.h"
#include <string>
#include <iostream>

using namespace std;

int main() {
    SavedLocations saved(5);

    for (int i = 0; i < saved.get_count(); i++) {
        cout << saved.get_string(i) << endl;
    }

    for (int i = 0; i < 4; i++) {
        string location;
        cout << "add location: ";
        cin >> location;

        saved.add_location(location);
    }

    return 0;
}