CXX = g++
LDFLAGS = lSDL2
CXXFLAGS = -g -Wall -std=c++11 -lGL `sdl2-config --cflags --libs`

%:%.cpp
	${CXX} -${LDFLAGS} $^ ${CXXFLAGS} -o $@
