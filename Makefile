CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude
GTKMM = `pkg-config --cflags --libs gtkmm-3.0`

all: lab2_ui lab2_gtk

lab2_ui: src/*.cpp
	$(CXX) $(CXXFLAGS) src/*.cpp -o lab2_ui

lab2_gtk: src/*.cpp
	$(CXX) $(CXXFLAGS) src/*.cpp $(GTKMM) -o lab2_gtk


clean:
	rm -f lab2_ui lab2_gtk

.PHONY: all run gtk clean