cmake_minimum_required(VERSION 3.22.1)

project(WeatherApp)
set(WeatherApp "WeatherApp")

set(Sources 
    CurrentWeatherGraphic.cpp
    ForecastWeatherGraphic.cpp
    ForecastWeatherData.cpp
    Graphic.cpp
    Location.cpp
    LocationList.cpp
    SavedLocations.cpp
    User.cpp
    WeatherData.cpp
    WeatherDataSet.cpp
    WeatherGraphic.cpp
)

add_executable(${WeatherApp}Test ${Sources})

target_link_libraries(${WeatherApp}Test PUBLIC
    gtest_main
    ${WeatherApp} # Linking with the library you defined in the main CMakeLists.txt
)

add_test(${WeatherApp}Test ${WeatherApp}Test)
