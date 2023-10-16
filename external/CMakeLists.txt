cmake_minimum_required(VERSION 3.22.1)

project(WeatherApp)

set(WeatherApp "WeatherApp")

project(${WeatherApp} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers
    Coordinates.h 
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

add_library(${WeatherApp} STATIC 
    ${Headers} 
    ${Sources}
)

include(CTest)
add_subdirectory(external)
add_subdirectory(project)


target_include_directories(${WeatherApp} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add the path to nlohmann/json.hpp to the include directories
target_include_directories(${WeatherApp}Test PRIVATE "//wsl.localhost/Ubuntu/root/json-develop/include")



add_subdirectory(test)
