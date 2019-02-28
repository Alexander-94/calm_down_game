all: Release/calm_down

Release/calm_down: calm_down/main.cpp
	g++ -g -std=c++11 calm_down/main.cpp -o Release/calm_down -I/usr/include/irrlicht -lIrrlicht

clean:
	rm -f Release/calm_down
