CXX = g++
CXXFLAGS = -g -Wall `sdl2-config --cflags` `pkg-config --cflags bullet`
LIBS = -lGL -lGLU `sdl2-config --libs` `pkg-config --libs bullet`
OUT = claw

OBJ = claw.o \
      formas.o \
      junta.o \
      braco.o \
      Load.o \
      camera.o \
      fisica.o \
      timing.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(OUT) $(LIBS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(OUT)
