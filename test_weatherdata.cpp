#include "WeatherDataSet.h"
#include  <string>
#include <iostream>

int main() {
    WeatherDataSet data_set("");

    int result = data_set.update_data();

    return result;
}