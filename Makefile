CXX = g++
LDFLAGS = -lSDL2
CXXFLAGS = -g -Wall -lGL `sdl2-config --cflags --libs`
OUT = claw

OBJ = claw.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $(OUT) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(OBJ)
	rm -f $(OUT)
