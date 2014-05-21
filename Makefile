CXX = g++
LDFLAGS = lSDL2
CXXFLAGS = -g -Wall -lGL -lGLU `sdl2-config --cflags --libs`

%:%.cpp
	${CXX} -${LDFLAGS} $^ ${CXXFLAGS} -o $@
