mymake: main.cpp
		g++ --std=c++17 -o 2 main.cpp WeatherDataSet.cpp WeatherData.cpp CurrentWeatherData.cpp ForecastWeatherData.cpp User.cpp Location.cpp LocationList.cpp SavedLocations.cpp Graphic.cpp WeatherGraphic.cpp CurrentWeatherGraphic.cpp ForecastWeatherGraphic.cpp Button.cpp -lcurl -I//Users/liam/json-develop/include -I//opt/homebrew/Cellar/sfml/2.6.0/include -L//opt/homebrew/Cellar/sfml/2.6.0/lib -lsfml-graphics -lsfml-window -lsfml-system