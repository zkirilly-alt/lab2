CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude -Irepositories -Wno-reorder
GTKMM = `pkg-config --cflags --libs gtkmm-3.0`

all: lab2_gtk

lab2_gtk: src/*.cpp repositories/*.cpp
	$(CXX) $(CXXFLAGS) src/*.cpp repositories/*.cpp $(GTKMM) -o lab2_gtk

gtk: lab2_gtk
	./lab2_gtk

build-tests:
	mkdir -p build
	cd build && cmake .. && make

test: build-tests
	./build/tests/run_tests

clean:
	rm -f lab2_gtk
	rm -rf build

.PHONY: all gtk build-tests test clean