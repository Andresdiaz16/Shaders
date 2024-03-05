CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

Shaders: main.cpp
	g++ $(CFLAGS) -o Shaders main.cpp $(LDFLAGS)

.PHONY: test clean

test: Shaders
	./Shaders

clean:
	rm -f Shaders
