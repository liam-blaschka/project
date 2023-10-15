cmake_minimum_required(VERSION 3.22.1)

set(Weather App)

project(${Weather App}CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Coordinates.h 
    CurrentWeahter.h
    CurrentWeatherGraphic.h
    ForecastWeatherGraphic.h 
    ForecastWeatherData.h
    Graphic.h
    Location.h
    LocationList.h
    SavedLocations.h
    User.h
    WeatherData.h
    WeatherDataSet.h
    WeatherGraphic.h
)
set(Sources 
    Coordinates.cpp
    CurrentWeahter.cpp
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

add_library(${Weather App} STATIC ${  Coordinates.cpp CurrentWeahter.cpp CurrentWeatherGraphic.cpp ForecastWeatherGraphic.cpp ForecastWeatherData.cpp Graphic.cpp Location.cpp LocationList.cpp SavedLocations.cpp User.cpp WeatherData.cpp WeatherDataSet.cpp WeatherGraphic.cpp} 
${Coordinates.h CurrentWeahter.h CurrentWeatherGraphic.h ForecastWeatherGraphic.h ForecastWeatherData.h Graphic.h Location.h LocationList.h SavedLocations.h User.h WeatherData.h WeatherDataSet.h WeatherGraphic.h})

add_subdirectory(test)


/// https://www.youtube.com/watch?v=Lp1ifh9TuFI
