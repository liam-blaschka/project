#ifndef LOCATION_H
#define LOCATION_H

#include <string>

using namespace std;

class Location {
    private:
        string location;
        // Text text;
        bool is_activated;
    public:
        Location();
        Location(string location);
        string get_string();
        void set_string(string location);
        void set_is_activated(bool is_activated);
        // draw(RenderTarget& target, RenderStates states);

};

#endif