mymake: main.cpp
		g++ --std=c++17 -lcurl -o 2 main.cpp WeatherDataSet.cpp WeatherData.cpp CurrentWeatherData.cpp ForecastWeatherData.cpp -I//Users/liam/json-develop/include